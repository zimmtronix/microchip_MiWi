// controls the LEDs and blinks them
#include <stdint.h>
#include "app_led.h"
#include "system.h"
#include "user.h"

uint8_t ledMode[5];
extern uint32_t sys_time;



void updateLeds(uint8_t led, uint8_t ledMode);
void loopLeds(void);

void updateLeds(uint8_t led, uint8_t ledMode)
{
    static uint8_t red[5];
    static uint8_t grn[5];
    if(led>4)
    {
        return;
    }
    switch (ledMode)
    {        
    case MANUAL_OFF:
        red[led] = 0;
        grn[led] = 0;
        break;

    case MANUAL_RED:
        red[led] = 1;
        grn[led] = 0;
        break;

    case MANUAL_GRN:
        red[led] = 0;
        grn[led] = 1;
        break;

    case MANUAL_ORG:
        red[led] = 1;
        grn[led] = 1;
        break;

    case BLINK_GRN:
        red[led] = 0;
        grn[led] ^= 1;
        break;

    case BLINK_RED:
        red[led] ^= 1;
        grn[led] = 0;
        break;

    case BLINK_ORG:
        red[led] ^= 1;
        grn[led] = red[led];
        break;

    case BLINK_RED_GRN:
        red[led] ^= 1;
        grn[led] = !red[led];
        break;
    case BLINK_RED_ORG:
        red[led] = 1;
        grn[led] ^= 1;
        break;
    case BLINK_GRN_ORG:
        red[led] ^= 1;
        grn[led] = 1;
        break;
    }
    switch(led)
    {
    case 0:
        RED_1=red[0];
        GRN_1=grn[0];
        break;
    case 1:
        RED_2=red[1];
        GRN_2=grn[1];
        break;
    case 2:
        RED_3=red[2];
        GRN_3=grn[2];
        break;
    case 3:
        RED_4=red[3];
        GRN_4=grn[3];
        break;
    case 4:
        RED_5=red[4];
        GRN_5=grn[4];
        break;
    }
}

void loopLeds()
{
    static uint32_t timer;

    if((sys_time-timer)>(250))
    {
        timer=sys_time;
        updateLeds(0,ledMode[0]);
        updateLeds(1,ledMode[1]);
        updateLeds(2,ledMode[2]);
        updateLeds(3,ledMode[3]);
        updateLeds(4,ledMode[4]);
    }
}


