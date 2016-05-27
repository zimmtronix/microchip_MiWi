/*
 * File:   system.h
 * Author: Not Supported
 *
 */

#ifndef SYSTEM_H
#define SYSTEM_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>


#include "spi.h"
#include "symbol.h"
#include "app_led.h"
#include "app_device_miwi.h"


/************************ DATA TYPE *******************************/
#define BUTTON_MIWI     (0b00001)
#define BUTTON_USB      (0b00010)
#define BUTTON_SLOTA    (0b00100)
#define BUTTON_SLOTB    (0b01000)
#define BUTTON_RESET    (0b10000)
#define BUTTON_PROGRAM  (0b10001)

typedef union
{
    uint8_t  v[4];
    uint16_t w[2];
    uint32_t Val;

}API_UINT32_UNION;

typedef union
{
    uint8_t  v[2];
    uint16_t Val;

}API_UINT16_UNION;


/*********************************************************************
* Macro: #define	SYS_CLK_FrequencySystemGet()
*
* Overview: This macro returns the system clock frequency in Hertz.
*
*
********************************************************************/
// enabled Crystal PLL
#define SYS_CLK_FrequencySystemGet()    (32000000)

/*********************************************************************
* Macro: #define	SYS_CLK_FrequencyPeripheralGet()
*
* Overview: This macro returns the peripheral clock frequency
*			used in Hertz.
*
*
********************************************************************/

#define SYS_CLK_FrequencyPeripheralGet()    (SYS_CLK_FrequencySystemGet()/2)

/*********************************************************************
* Macro: #define	SYS_CLK_FrequencyInstructionGet()
*
* Overview: This macro returns instruction clock frequency
*			used in Hertz.
*
*
********************************************************************/

#define SYS_CLK_FrequencyInstructionGet()   (SYS_CLK_FrequencySystemGet()/2)
#define FCY                                 (SYS_CLK_FrequencyInstructionGet())

/*********************************************************************
* Macro: #define	GetInstructionClock()
*
* Overview: This macro returns instruction clock frequency
*			used in Hertz, used in TCPIP
*
*
********************************************************************/

#define GetInstructionClock()   SYS_CLK_FrequencyInstructionGet()
#define GetPeripheralClock()	(SYS_CLK_FrequencySystemGet()/2)


/*********************************************************************
* Function: void sysTasks(void)
*
* Overview: Runs system level tasks that keep the system running
*
* PreCondition: System has been initalized with sysInit()
*
* Input: None
*
* Output: None
*
********************************************************************/
void sysTasks(void);


// Base RAM and ROM pointer types for given architecture
#define PTR_BASE        unsigned short
#define ROM_PTR_BASE    unsigned short

// Definitions that apply to all except Microchip MPLAB C Compiler for PIC18 MCUs (C18)
#define memcmppgm2ram(a,b,c)    memcmp(a,b,c)
#define strcmppgm2ram(a,b)      strcmp(a,b)
#define memcpypgm2ram(a,b,c)    memcpy(a,b,c)
#define strcpypgm2ram(a,b)      strcpy(a,b)
#define strncpypgm2ram(a,b,c)   strncpy(a,b,c)
#define strstrrampgm(a,b)       strstr(a,b)
#define strlenpgm(a)            strlen(a)
#define strchrpgm(a,b)          strchr(a,b)
#define strcatpgm2ram(a,b)      strcat(a,b)

// Definitions that apply to all 16-bit and 32-bit products
// (PIC24F, PIC24H, dsPIC30F, dsPIC33F, and PIC32)
#define ROM        const

// 16-bit specific defines (PIC24F, PIC24H, dsPIC30F, dsPIC33F)
#define Reset()    asm("reset")
#define FAR        __attribute__((far))


#endif //SYSTEM_H
