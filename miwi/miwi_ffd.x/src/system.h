/* 
 * File:   system.h
 * Author: Not Supported
 *
 */
 
#ifndef __SYSTEM_H
#define __SYSTEM_H

/******************************************************************************/
/* System Function Prototypes                                                 */
/******************************************************************************/
#include <xc.h>
#include <stdbool.h>
#include <stddef.h>
#include "spi.h"
#include "symbol.h"

/************************ DATA TYPE *******************************/

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

#define SYS_CLK_FrequencySystemGet()    (16000000)

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

#include <libpic30.h>       /* Includes delay definition, after FCY           */ 

#endif