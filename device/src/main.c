#include "main.h"
#include "shared/attributes.h"
#include "zephyr/storage/flash_map.h"
#include "keyboard/key_scanner.h"
#include "keyboard/leds.h"
#include "keyboard/oled/oled.h"
#include "keyboard/charger.h"
#include "keyboard/spi.h"
#include "keyboard/uart.h"
#include "nus_client.h"
#include "nus_server.h"
#include "keyboard/i2c.h"
#include "peripherals/merge_sensor.h"
#include "shell.h"
#include "device.h"
#include "usb/usb.h"
#include "bt_conn.h"
#include "bt_advertise.h"
#include "settings.h"
#include "flash.h"
#include "usb_commands/usb_command_apply_config.h"
#include "macros/shortcut_parser.h"
#include "macros/keyid_parser.h"
#include "macros/core.h"
#include "legacy/timer.h"
#include "legacy/user_logic.h"
#include "legacy/config_manager.h"
#include "messenger.h"
#include "legacy/led_manager.h"
#include "legacy/debug.h"
#include "state_sync.h"
#include "keyboard/charger.h"
#include <stdint.h>
#include "debug_eventloop_timing.h"
// #include <zephyr/drivers/gpio.h>
// #include "dongle_leds.h"

k_tid_t Main_ThreadId = 0;

static void sleepTillNextMs() {
    static uint64_t wakeupTimeUs = 0;
    const uint64_t minSleepTime = 100;
    uint64_t currentTimeUs = k_cyc_to_us_near64(k_cycle_get_32());

    wakeupTimeUs = wakeupTimeUs+1000;

    if (currentTimeUs < wakeupTimeUs) {
        k_usleep(MAX(wakeupTimeUs-currentTimeUs, minSleepTime));
    } else {
        k_usleep(minSleepTime);
        wakeupTimeUs = currentTimeUs;
    }
}

static void scheduleNextRun() {
    uint32_t nextEventTime = 0;
    bool eventIsValid = false;
    if (EventScheduler_Vector & EventVector_EventScheduler) {
        nextEventTime = EventScheduler_Process();
        eventIsValid = true;
    }
    CurrentTime = k_uptime_get();
    int32_t diff = nextEventTime - CurrentTime;
    bool haveMoreWork = (EventScheduler_Vector & EventVector_ReportUpdateMask);
    if (haveMoreWork) {
        EVENTLOOP_TIMING(printk("Continuing immediately\n"));
        // Mouse keys don't like being called twice in one second for some reason
        sleepTillNextMs();
        return;
    } else if (eventIsValid) {
        EVENTLOOP_TIMING(printk("Sleeping for %d\n", diff));
        k_sleep(K_MSEC(diff));
    } else {
        EVENTLOOP_TIMING(printk("Sleeping forever\n"));
        k_sleep(K_FOREVER);
    }
}

int main(void) {
    Main_ThreadId = k_current_get();
    printk("----------\n" DEVICE_NAME " started\n");

    // const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(DT_ALIAS(led0_green), gpios);
    // gpio_pin_configure_dt(&led0, GPIO_OUTPUT);
    // while (true) {
    //     gpio_pin_set_dt(&led0, true);
    //     k_sleep(K_MSEC(1000));
    //     gpio_pin_set_dt(&led0, false);
    //     set_dongle_led(&red_pwm_led, 100);
    //     k_sleep(K_MSEC(1000));
    //     set_dongle_led(&red_pwm_led, 0);
    //     set_dongle_led(&green_pwm_led, 100);
    //     k_sleep(K_MSEC(1000));
    //     set_dongle_led(&green_pwm_led, 0);
    //     set_dongle_led(&blue_pwm_led, 100);
    //     k_sleep(K_MSEC(1000));
    //     set_dongle_led(&blue_pwm_led, 0);
    // }

    if (DEVICE_IS_UHK80_RIGHT) {
        flash_area_open(FLASH_AREA_ID(hardware_config_partition), &hardwareConfigArea);
        flash_area_open(FLASH_AREA_ID(user_config_partition), &userConfigArea);
    }

    if (!DEVICE_IS_UHK_DONGLE) {
        InitUart();
        InitI2c();
        InitSpi();

        #ifdef DEVICE_HAS_OLED
        InitOled();
        #endif // DEVICE_HAS_OLED

        InitLeds();

    #ifdef DEVICE_HAS_MERGE_SENSOR
        MergeSensor_Init();
    #endif // DEVICE_HAS_MERGE_SENSOR

        InitKeyScanner();

    }
    USB_EnableHid();


    if (!DEVICE_IS_UHK_DONGLE) {
        InitCharger(); // has to be after usb initialization
    }

    bt_init();
    InitSettings();

    if (DEVICE_IS_UHK80_RIGHT) {
        HOGP_Enable();
    }

    if (DEVICE_IS_UHK80_LEFT || DEVICE_IS_UHK80_RIGHT) {
        int err = NusServer_Init();
        if (!err) {
            uint8_t advType = ADVERTISE_NUS;
            if (DEVICE_IS_UHK80_RIGHT) {
                advType |= ADVERTISE_HID;
            }
            Advertise(advType);
        }
    }

    if (DEVICE_IS_UHK80_RIGHT || DEVICE_IS_UHK_DONGLE) {
        NusClient_Init();
    }

    if (DEVICE_IS_UHK80_LEFT || DEVICE_IS_UHK80_RIGHT) {
        ConfigManager_ResetConfiguration(false);
    }

    if (DEVICE_IS_UHK80_RIGHT) {
        InitFlash();
        printk("Reading hardware config\n");
        Flash_ReadAreaSync(hardwareConfigArea, 0, HardwareConfigBuffer.buffer, HARDWARE_CONFIG_SIZE);
        printk("Reading user config\n");
        Flash_ReadAreaSync(userConfigArea, 0, StagingUserConfigBuffer.buffer, USER_CONFIG_SIZE);
        printk("Applying user config\n");
        bool factoryMode = false;
        if (factoryMode) {
            LedManager_FullUpdate();
        } else {
            UsbCommand_ApplyConfig();
        }
        printk("User config applied\n");
        ShortcutParser_initialize();
        KeyIdParser_initialize();
        Macros_Initialize();
    }

    Messenger_Init();

    StateSync_Init();

#if DEVICE_IS_UHK80_RIGHT
    while (true)
    {
        CurrentTime = k_uptime_get();
        Messenger_ProcessQueue();
        if (EventScheduler_Vector & EventVector_UserLogicUpdateMask) {
            EVENTLOOP_TIMING(EVENTLOOP_TIMING(EventloopTiming_Start()));
            RunUserLogic();
            EVENTLOOP_TIMING(EventloopTiming_End());
        }
        scheduleNextRun();
    }
#else
    while (true)
    {
        CurrentTime = k_uptime_get();
        Messenger_ProcessQueue();
        RunUhk80LeftHalfLogic();
        scheduleNextRun();
    }
#endif
}
