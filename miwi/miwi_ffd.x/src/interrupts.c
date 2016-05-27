/* 
 * File:   interrupts.c
 * Author: Not Supported
 *
 */

/* Device header file */
#include <xc.h>

#include <stdint.h>        /* Includes uint16_t definition */
#include <stdbool.h>       /* Includes true/false definition */

#include "user.h"

extern uint32_t sys_time;

extern uint16_t ledTimer;

extern uint8_t buttonBeepTimer;


// 1ms 1s timer used for system time

void _ISRFAST __attribute__((interrupt, auto_psv)) _T3Interrupt(void)
{
    if (ledTimer)
    {
        ledTimer--;
    }
    
    // the time the beeper sounds after a button press
    if (buttonBeepTimer)
    {
        buttonBeepTimer--;
        if (buttonBeepTimer == 0)
        {
            beeperOff();
        }
    }

    // ms couner
    sys_time++;
    _T3IF = 0;
}

