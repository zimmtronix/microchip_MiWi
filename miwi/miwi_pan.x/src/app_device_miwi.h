/* 
 * File:   app_device_miwi.h
 * Author: Not Supported
 *
 */

#ifndef APP_DEVICE_MIWI_H
#define	APP_DEVICE_MIWI_H

#include <stdint.h>

uint8_t miwiInit(uint8_t reset);
void miwiProcess();
uint8_t miwiMsg(uint8_t ,uint8_t *, uint8_t);

#define DEVICEMAX 100

extern uint8_t miwi_state;

#define MIWI_SUCCESS        0
#define MIWI_FAIL           1
#define SCAN_FAIL           2
#define MY_CHANNEL_FAIL     3
#define MAC_ADDRESS_FAIL    4
#define RADIO_MISSING       5

#endif	/* APP_DEVICE_MIWI_H */

