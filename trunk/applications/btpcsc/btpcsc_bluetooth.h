/*
 * Copyright 2010 Manuel Eberl <manueleberl@gmx.de> for Giesecke & Devrient
 * Licensed under the Apache License, Version 2.0 (the "License"); 
 * you may not use this file except in compliance with the License. 
 * You may obtain a copy of the License at 
 * 
 *      http://www.apache.org/licenses/LICENSE-2.0 
 *
 * Unless required by applicable law or agreed to in writing, software 
 * distributed under the License is distributed on an "AS IS" BASIS, 
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
 * See the License for the specific language governing permissions and 
 * limitations under the License. 
 */

/*****************************************************************
/
/ File   :   btpcsp_bluetooth.h
/ Author :   Manuel Eberl <manueleberl@gmx.de>
/ Date   :   September 30, 2010
/ Purpose:   Provides functions to establish and control a
/            Bluetooth connection for the PCSC Bluetooth bridge
/
******************************************************************/

#ifndef _btpcsc_bluetooth_h_
#define _btpcsc_bluetooth_h_

#ifdef __cplusplus
extern "C" {
#endif 

#define BT_PCSC_SUCCESS 0
#define BT_PCSC_ERROR_NOT_SUPPORTED -4200
#define BT_PCSC_ERROR_UNKNOWN_CMD -4201
#define BT_PCSC_ERROR_NO_READERS -4202
#define BT_PCSC_ERROR_NO_SUCH_READER -4203
#define BT_PCSC_ERROR_CONNECTION -4204
#define ERROR_CONNECTION_TIMEOUT -4205
#define BT_PCSC_ERROR_CONNECTION_CONNECT -4206
#define BT_PCSC_ERROR_CONNECTION_SDP -4207
#define BT_PCSC_ERROR_CONNECTION_SERVER_NOT_ACTIVE -4208
#define BT_PCSC_ERROR_CONNECTION_CHANNEL_CLOSED -4209
#define BT_PCSC_ERROR_INVALID_ACK -4210
#define BT_PCSC_ERROR_DISCONNECTED -4212
#define BT_PCSC_ERROR_INSUFFICIENT_BUFFER -4217
#define BT_PCSC_ERROR_INVALID_SLOT -4218
#define BT_PCSC_ERROR_UNKNOWN -4999

#define BT_PCSC_UUID {0x42, 0x21, 0x9a, 0xbb, 0x16, 0x15, 0x44, 0x86, 0xbd, 0x50, 0x49, 0x6b, 0xd5, 0x04, 0x96, 0xd8}
#define BT_PCSC_ACK_CONNECTION {0x13, 0x37, 0x30, 0xF8}

#define BT_PCSC_CMD_ACK 1
#define BT_PCSC_CMD_DISCONNECT 2
#define BT_PCSC_CMD_SEND_APDU 16
#define BT_PCSC_CMD_RECV_APDU 17
#define BT_PCSC_CMD_GET_PRESENT 24
#define BT_PCSC_CMD_GET_PRESENT_RESULT 25
#define BT_PCSC_CMD_GET_SLOTS 32
#define BT_PCSC_CMD_GET_SLOTS_RESULT 33
#define BT_PCSC_CMD_SET_SLOT 34
#define BT_PCSC_CMD_NOT_SUPPORTED 254
#define BT_PCSC_CMD_ERROR 255

#define BT_PCSC_CMD_ERROR_NO_READERS 32

#include <stdint.h>
#include <pthread.h>

typedef struct bt_pcsc_connection {
    int lun, channel;
    char remote_addr[18];
    char valid;
    int socket;
    pthread_mutex_t mutex;
    struct bt_pcsc_connection *next;
} bt_pcsc_connection;



// Creates a new connection, adds it to the list and returns a pointer to it.
bt_pcsc_connection *add_connection(int lun, int channel, char *remote_addr, char valid);

// Removes a connection, but does NOT close it.
void remove_connection(int lun);

// Finds and returns the connection with the specified lun or NULL if there
// is no such connection.
bt_pcsc_connection *get_connection(int lun);

// Establishes a bluetooth connection to the service with the right UUID
// on the device with the specified address.
int bt_connect(bt_pcsc_connection *connection);

// Transmits an APDU over the specified connection
int bt_recv_apdu(bt_pcsc_connection *connection, uint16_t *apdu_length, void *apdu);

// Receives an APDU over the specified connection
int bt_recv_apdu(bt_pcsc_connection *connection, uint16_t *apdu_length, void *apdu);

// Determines whether the device is connected and a card is 
// present in the selected slot
int bt_is_card_present(bt_pcsc_connection *connection);

// Asks the server how many readers it has and what their names are
int bt_get_slots(bt_pcsc_connection *connection, char *slots[], int maxslots);

// Sets the card reader to be used by this connection
int bt_set_slot(bt_pcsc_connection *connection, char *slot);

// Closes the connection gracefully
int bt_disconnect(bt_pcsc_connection *connection);


#ifdef __cplusplus
}
#endif

#endif
