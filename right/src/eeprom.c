#include "eeprom.h"

#ifndef __ZEPHYR__
#include "fsl_common.h"
#include "config_parser/config_globals.h"
#include "i2c_addresses.h"
#include "i2c.h"
#include "config_parser/config_globals.h"
#include "buffer.h"

static storage_operation_t CurrentEepromOperation;
static config_buffer_id_t CurrentConfigBufferId;
static status_t LastEepromTransferStatus;
void (*SuccessCallback)(void);

static i2c_master_handle_t i2cHandle;
static i2c_master_transfer_t i2cTransfer;

static uint8_t *sourceBuffer;
static uint16_t sourceOffset;
static uint16_t eepromStartAddress;
static uint16_t sourceLength;
static uint8_t writeLength;
static bool isReadSent;

static status_t i2cAsyncWrite(uint8_t *data, size_t dataSize)
{
    i2cTransfer.slaveAddress = I2C_ADDRESS_EEPROM;
    i2cTransfer.direction = kI2C_Write;
    i2cTransfer.data = data;
    i2cTransfer.dataSize = dataSize;
    return I2C_MasterTransferNonBlocking(I2C_EEPROM_BUS_BASEADDR, &i2cHandle, &i2cTransfer);
}

static status_t i2cAsyncRead(uint8_t *data, size_t dataSize)
{
    i2cTransfer.slaveAddress = I2C_ADDRESS_EEPROM;
    i2cTransfer.direction = kI2C_Read;
    i2cTransfer.data = data;
    i2cTransfer.dataSize = dataSize;
    return I2C_MasterTransferNonBlocking(I2C_EEPROM_BUS_BASEADDR, &i2cHandle, &i2cTransfer);
}

static status_t writePage(void)
{
    static uint8_t buffer[EEPROM_BUFFER_SIZE];
    SetBufferUint16Be(buffer, 0, eepromStartAddress + sourceOffset);
    writeLength = MIN(sourceLength - sourceOffset, EEPROM_PAGE_SIZE);
    memcpy(buffer+EEPROM_ADDRESS_SIZE, sourceBuffer+sourceOffset, writeLength);
    status_t status = i2cAsyncWrite(buffer, writeLength+EEPROM_ADDRESS_SIZE);
    return status;
}

static void i2cCallback(I2C_Type *base, i2c_master_handle_t *handle, status_t status, void *userData)
{
    LastEepromTransferStatus = status;

    switch (CurrentEepromOperation) {
        case StorageOperation_Read:
            if (isReadSent) {
                IsStorageBusy = false;
                if (SuccessCallback) {
                    SuccessCallback();
                }
                return;
            }
            LastEepromTransferStatus = i2cAsyncRead(
                ConfigBufferIdToConfigBuffer(CurrentConfigBufferId)->buffer,
                CurrentConfigBufferId == ConfigBufferId_HardwareConfig ? HARDWARE_CONFIG_SIZE : USER_CONFIG_SIZE
            );
            IsStorageBusy = true;
            isReadSent = true;
            break;
        case StorageOperation_Write:
            if (status == kStatus_Success) {
                sourceOffset += writeLength;
            }
            IsStorageBusy = sourceOffset < sourceLength;
            if (!IsStorageBusy) {
                if (SuccessCallback) {
                    SuccessCallback();
                }
                return;
            }
            LastEepromTransferStatus = writePage();
            break;
        default:
            IsStorageBusy = false;
            break;
    }
}

void EEPROM_Init(void)
{
    I2C_MasterTransferCreateHandle(I2C_EEPROM_BUS_BASEADDR, &i2cHandle, i2cCallback, NULL);
}

status_t EEPROM_LaunchTransfer(storage_operation_t operation, config_buffer_id_t configBufferId, void (*successCallback))
{
    if (IsStorageBusy) {
        return kStatus_I2C_Busy;
    }

    CurrentEepromOperation = operation;
    CurrentConfigBufferId = configBufferId;
    SuccessCallback = successCallback;

    bool isHardwareConfig = CurrentConfigBufferId == ConfigBufferId_HardwareConfig;
    eepromStartAddress = isHardwareConfig ? 0 : HARDWARE_CONFIG_SIZE;

    switch (CurrentEepromOperation) {
        case StorageOperation_Read:
            isReadSent = false;
            static uint8_t addressBuffer[EEPROM_ADDRESS_SIZE];
            SetBufferUint16Be(addressBuffer, 0, eepromStartAddress);
            LastEepromTransferStatus = i2cAsyncWrite(addressBuffer, EEPROM_ADDRESS_SIZE);
            break;
        case StorageOperation_Write:
            sourceBuffer = ConfigBufferIdToConfigBuffer(CurrentConfigBufferId)->buffer;
            sourceOffset = 0;
            uint16_t userConfigSize = ValidatedUserConfigLength && configBufferId == ConfigBufferId_ValidatedUserConfig ? ValidatedUserConfigLength : USER_CONFIG_SIZE;
            sourceLength = isHardwareConfig ? HARDWARE_CONFIG_SIZE : userConfigSize;
            LastEepromTransferStatus = writePage();
            break;
    }

    IsStorageBusy = LastEepromTransferStatus == kStatus_Success;
    return LastEepromTransferStatus;
}
#endif
