/******************************************************************************/
/* MAIN PAN                                                                   */
/******************************************************************************/
/** INCLUDES *******************************************************/
#include "system.h"
#include <libpic30.h>
#include <stdio.h>

// Board specific details
#include "user.h"

// MiWi configuration
#include "app_device_miwi.h"
#include "miwi_api.h"
#include "drv_mrf_miwi_security.h"
#include "miwi_nvm.h"

MODULE sysStatus;

extern uint8_t ledMode[5];
volatile uint16_t syncTimeout;

// MiWi
#if ADDITIONAL_NODE_ID_SIZE > 0
uint8_t AdditionalNodeID[ADDITIONAL_NODE_ID_SIZE] = {DEVICE_TYPE};
#endif


/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

int16_t main(void)
{
    /* Main Variables */

    
    /* Initialize IO ports and peripherals */
    InitApp();
    
    // *************************************************************************
    // Set configuration
    // *************************************************************************

    // Radio needs time to setup
    PHY_RESETn_TRIS = 0;
    PHY_RESETn = 1;
    __delay_us(100);
    PHY_RESETn = 0;
    PHY_RESETn_TRIS = 1;
    __delay_ms(20);
    
    /* Init code */
    ReadMacAddress(); // Read long address from EEPROM

    sysStatus.miwiPresent = miwiInit(false);

    // Blink lights
    beeper_on();
    RED_1 = 1;
    GRN_1 = 0;
    __delay_ms(100);
    beeper_off();
    GRN_1 = 1;
    RED_1 = 0;
    __delay_ms(100);
    
    GRN_1 = 0;
    RED_1 = 0;
    __delay_ms(100);
    
    while (1)
    {
        // Local Control Section
        sysTasks();
        
        // MiWi section
        miwiProcess();

        /* Quick scan to see what is online offline*/
        uint8_t totalDevices;
        uint8_t iii;
        totalDevices=0;

        for (iii = 0; iii < DEVICEMAX - 2; iii++)
        {
            if (ConnectionTable[iii].status.bits.isValid == 1)
            {
                totalDevices++;                    
            }
        }

        uint8_t tmp;
        // TODO:  Check if devices, check if online
        nvmGetConnMode(&tmp);
        if (tmp == ENABLE_ALL_CONN)
        {
            ledMode[0] = BLINK_GRN;
            if(syncTimeout==0)
            {
                MiApp_ConnectionMode(1);
            }
        }
        else if (totalDevices)
        {
            ledMode[0] = MANUAL_GRN;
        }
        else
        {
            ledMode[0] = MANUAL_RED;
        }
    }//end while
}//end main


/*******************************************************************************
 End of File
 */
