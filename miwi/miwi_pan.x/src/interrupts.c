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

extern volatile uint16_t chirp_counter;
extern volatile uint16_t chirpUp; //Decremented in interrupt
extern volatile uint16_t chirpDown; //Decremented in interrupt
extern uint16_t timeFlag;
extern uint16_t syncTimeout;


volatile uint32_t sys_time;
volatile uint32_t sec_time;

volatile uint32_t tenMsCounter;

/******************************************************************************/
/* Interrupt Routines                                                         */
/******************************************************************************/
// Reset interrupt on water sense pins will be changed to alarm later


/* Updates 100 per second*/
void __attribute__((interrupt, auto_psv)) _T2Interrupt(void)
{
    tenMsCounter++;
    _T2IF = 0;
}

/* Updates 1000 per second*/
void __attribute__((interrupt, auto_psv)) _T3Interrupt(void)
{    
    static uint16_t count;
    static uint16_t dir = 0;
    if (count++ > 1000)
    {
        count = 0;
        sec_time++;
    
        if(syncTimeout)
        {
            syncTimeout--;
        }
    }
    

    if (chirp_counter == 0)
    {
        if (chirpUp)
        {
            if (dir == 0)
            {
                dir = 1;
                chirp_counter = chirpUp;
            }
            else
            {
                dir = 0;
                chirp_counter = chirpDown;
            }
        }        
    }
    else
    {
        chirp_counter--;
        if (chirp_counter == 0)
        {
            if ((chirpUp == 0) || (dir == 0))
            {
                beeper_off();
            }
            else
            {
                beeper_on();
            }
        }        
    }
    sys_time++;
    _T3IF = 0;
}

void __attribute__((interrupt, auto_psv)) _ADC1Interrupt(void)
{
    _SAMP = 1;
    _AD1IF = 0;
}


