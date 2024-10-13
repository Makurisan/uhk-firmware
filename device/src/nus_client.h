#ifndef __NUS_CLIENT_H__
#define __NUS_CLIENT_H__

// Includes

    #include <zephyr/bluetooth/conn.h>
    #include "messenger.h"

// Functions:

    extern void NusClient_Init(void);
    void NusClient_Disconnected();
    extern void gatt_discover(struct bt_conn *conn);
    extern void NusClient_Connect(struct bt_conn *conn);
    extern void NusClient_SendMessage(message_t msg);
    extern bool NusClient_Availability(messenger_availability_op_t operation);

#endif // __NUS_CLIENT_H__
