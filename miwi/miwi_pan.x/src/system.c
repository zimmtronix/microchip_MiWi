/* 
 * File:   system.c
 * Author: Not Supported
 *
 */

#include "system.h"
#include <xc.h>
#include <stdbool.h>
#include <stdint.h>          /* For uint32_t definition */

#include "user.h"

#include "miwi_api.h"
#include "miwi_nvm.h"

extern uint32_t sys_time;
volatile uint16_t chirp_counter; //Decremented in interrupt
volatile uint16_t chirpUp; //Decremented in interrupt
volatile uint16_t chirpDown; //Decremented in interrupt
extern uint16_t syncTimeout;

void chirp()
{
    chirp_counter = 50; // In milli-seconds, interrupt will stop it.
    beeper_on();
}

void chirp_off()
{
    chirpUp = 0;
    chirpDown = 10;
}

void chirp_on(uint16_t onTime, uint16_t offTime)
{
    chirpUp = onTime;
    chirpDown = offTime;
}


void sysTasks(void)
{
#define LONG_HOLD       7000
#define SHORT_HOLD      2000
#define SHORT_TAP       100

    static uint32_t start_time_miwi;


    static uint8_t preButtons;
    uint8_t nowButtons;
    nowButtons = ButtonPressed();    
    uint32_t elapsed;
        
    loopLeds();

    
    //new button press
    if (nowButtons != preButtons)
    {
        chirp();
        if (nowButtons == 0)
        {
            chirp_off();
            // 11111111111111111111111111111111111111111111111111111111111111111
            if (start_time_miwi > 0)
            {
                chirp_off();
                elapsed = sys_time - start_time_miwi;
                if ((elapsed <= SHORT_HOLD)&&(elapsed > SHORT_TAP))
                {
                    // Not sync 
                    syncTimeout = 1;
                    MiApp_ConnectionMode(1);
                }
                else if ((elapsed > SHORT_HOLD) && (elapsed < LONG_HOLD))
                {
                    // Sync mode
                    syncTimeout = 60;
                    MiApp_ConnectionMode(0);
                }
                else if (elapsed > LONG_HOLD)
                {
                    // Reset MiWi Network                       
                    syncTimeout = 1;               
                    miwiInit(true);  
                }
            }
        }

        // different buttons pressed
        start_time_miwi = 0;

        preButtons = nowButtons;

    }
    else
    {
        if (nowButtons == BUTTON_MIWI)
        {
            if (start_time_miwi == 0)
            {
                start_time_miwi = sys_time;
            }
            else
            {
                elapsed = sys_time - start_time_miwi;

                if (elapsed > 9000)
                {
                    chirp_off();
                }
                else if (elapsed > 7000)
                {
                    chirp_on(1, 1000);
                }
                else if (elapsed > 6000)
                {
                    chirp_on(25, 250);
                }
                else if (elapsed > 2500)
                {
                    chirp_off();
                }
                else if (elapsed > 2000)
                {
                    chirp_on(25, 25);
                }
            }
        }
    }
}


