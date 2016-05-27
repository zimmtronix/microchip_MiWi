/* 
 * File:   main.c
 * Author: Not Supported
 *
 */

/******************************************************************************/
/* Wireless Remote                                                            */
/******************************************************************************/

/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/
/* Device header file */
#include <xc.h>
#include <stdio.h>          /* Includes sprintf definitions                   */
#include <stdint.h>         /* Includes uint16_t definition                   */
#include <stdbool.h>        /* Includes true/false definition                 */

#include "system.h"         /* System funct/params, like osc/peripheral config*/
#include "user.h"           /* User func/params system specific               */
#include "miwi_api.h"       /* User func/params for MiWi MiApp_ calls         */
#include "eeprom.h"         /* Allows writting to eeprom                      */


/******************************************************************************/
/*  Function Prototypes                                                       */
/******************************************************************************/
void ReadMacAddress(void);
uint8_t miwi_init(uint8_t);
void sysTasks(void);
uint8_t ButtonPressed(void); // returns if a button is pressed


/******************************************************************************/
/*  Defines                                                                   */
/******************************************************************************/
#define DEV_GATEWAY 0xFF
#define DEV_SENSOR  0x10
#define DEV_REMOTE  0x20
#define DEV_MODULE  0x30

//Change this to change the type of system
#define DEVICE_TYPE DEV_REMOTE

// return 1 if difference between xxx and yyy is more zzz
#define COMPARE(xxx, yyy, zzz) ((xxx>yyy) ? (xxx-yyy)>=zzz : (yyy-xxx)>=zzz )

#define MIWI_SUCCESS        0
#define MIWI_FAIL           1
#define SCAN_FAIL           2
#define MY_CHANNEL_FAIL     3
#define MAC_ADDRESS_FAIL    4
#define RADIO_MISSING       5

#define SHORT_TAP       100


/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/
uint8_t sendIt;

volatile uint32_t sys_time;
volatile uint8_t buttonBeepTimer;
volatile uint16_t ledTimer;

extern uint8_t myLongAddress[];
uint8_t sa_vip[2] = {0, 0};

/* Main Variables */
uint8_t miwi_status;



#if ADDITIONAL_NODE_ID_SIZE > 0
uint8_t AdditionalNodeID[ADDITIONAL_NODE_ID_SIZE] = {DEVICE_TYPE};
#endif

// *****************************************************************************
//              Functions
// *****************************************************************************

void ReadMacAddress(void)
{
    uint8_t iii;

    if (MY_ADDRESS_LENGTH > 6)
    {
        for (iii = 0; iii < 3; iii++)
        {
            EEPROMRead(&(myLongAddress[MY_ADDRESS_LENGTH - 1 - iii]), EEPROM_MAC_ADDR + iii, 1);
        }

        if (MY_ADDRESS_LENGTH > 7)
        {
            myLongAddress[4] = 0xFF;
        }
        myLongAddress[3] = 0xFE;

        for (iii = 0; iii < 3; iii++)
        {
            EEPROMRead(&(myLongAddress[2 - iii]), EEPROM_MAC_ADDR + 3 + iii, 1);
        }
    }
    else
    {
        for (iii = 0; iii < MY_ADDRESS_LENGTH; iii++)
        {
            EEPROMRead(&(myLongAddress[iii]), EEPROM_MAC_ADDR + 5 - iii, 1);
        }
    }
}

uint8_t miwi_init(uint8_t reset)
{
    uint8_t myChannel = 25;
    uint8_t iii;
    
    // Simple check to see if it could be valid
    if ((myLongAddress[MY_ADDRESS_LENGTH - 1] == 0x00) ||
            (myLongAddress[MY_ADDRESS_LENGTH - 1] == 0xFF))
    {
        return MAC_ADDRESS_FAIL;
    }

    // +++++++++++++++++++++++++++++++++++
    // Radio Setup
    // -----------------------------------
    if ((MiApp_ProtocolInit(true) == false) || (reset == true))
    {
        // First time
        MiApp_ProtocolInit(false);

        // Set default channel
        if (MiApp_SetChannel(myChannel) == false)
        {
            return MY_CHANNEL_FAIL;
        }

        // Set Connection Mode
        MiApp_ConnectionMode(ENABLE_ALL_CONN);

        iii = MiApp_SearchConnection(10, 0x02000000);
        if (iii > 0)
        {
            if (MiApp_EstablishConnection(0xFF, CONN_MODE_DIRECT) == 0xFF)
            {
                return MIWI_FAIL;
            }
            else
            {
                return MIWI_SUCCESS;
            }
        }
        else
        {
            return SCAN_FAIL;
        }
    }
    else
    {
        return MIWI_SUCCESS;
    }
    return MIWI_FAIL;
}

void sysTasks(void)
{
    static uint32_t btn1_start_time;
    static uint32_t btn2_start_time;
    static uint8_t preButtons;
    uint8_t nowButtons;

    nowButtons = ButtonPressed();
    uint32_t elapsed;

    //new button press
    if (nowButtons != preButtons)
    {
        preButtons = nowButtons;
        buttonBeepTimer = 50;
        beeperOn();
        if (nowButtons == 0)
        {

            // 11111111111111111111111111111111111111111111111111111111111111111
            if (btn1_start_time > 0)
            {
                elapsed = sys_time - btn1_start_time;
                if (elapsed > SHORT_TAP)
                {
                    if(LED_1)
                    {
                        sendIt = 2;
                    }
                    else
                    {
                        sendIt = 1;
                    }
                }
            }

            // 2222222222222222222222222222222222222222222222222222222222222222
            if (btn2_start_time > 0)
            {
                elapsed = sys_time - btn2_start_time;
                if (elapsed > SHORT_TAP)
                {
                    miwi_status = miwi_init(true);
                    if (miwi_status == MIWI_SUCCESS)
                    {
                        beeperOn();
                        __delay_ms(100);
                        beeperOff();
                        __delay_ms(25);
                        beeperOn();
                        __delay_ms(100);
                        beeperOff();
                        __delay_ms(25);
                        beeperOn();
                        __delay_ms(100);
                        beeperOff();
                    }
                    else if (miwi_status == MIWI_FAIL)
                    {
                        beeperOn();
                        __delay_ms(500);
                        beeperOff();
                        __delay_ms(500);
                        beeperOn();
                        __delay_ms(500);
                        beeperOff();
                    }
                    else
                    {
                        beeperOn();
                        __delay_ms(500);
                        beeperOff();
                    }
                }
            }
            // different buttons pressed
            btn1_start_time = 0;
            btn2_start_time = 0;
        }
        else
        {
            if (nowButtons == (1 << 1))
            {
                if (btn1_start_time == 0)
                {
                    btn1_start_time = sys_time;
                }
            }

            if (nowButtons == (1 << 2))
            {
                if (btn2_start_time == 0)
                {
                    btn2_start_time = sys_time;
                }
            }
        }
    }
}

uint8_t ButtonPressed(void)
{
    return !SW2_ << 2 | !SW1_ << 1;
}

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

    // +++++++++++++++++++++++++++++++++++
    // Radio Setup
    // -----------------------------------
    miwi_status = miwi_init(0);
    if (miwi_status == MIWI_SUCCESS)
    {
        beeperOn();
        __delay_ms(100);
        beeperOff();
        __delay_ms(25);
        beeperOn();
        __delay_ms(100);
        beeperOff();
        __delay_ms(25);
        beeperOn();
        __delay_ms(100);
        beeperOff();
        LED_1 = 1;
        LED_2 = 0;
    }
    else if (miwi_status == MIWI_FAIL)
    {
        beeperOn();
        __delay_ms(500);
        beeperOff();
        __delay_ms(500);
        beeperOn();
        __delay_ms(500);
        beeperOff();
    }
    else
    {
        beeperOn();
        __delay_ms(500);
        beeperOff();
    }

    // ----------------------------------------------------------------------------
    // Main Loop
    // ----------------------------------------------------------------------------
    while (1)
    {

        sysTasks(); // Buttons
        
        if (miwi_status != MIWI_SUCCESS)
        {
            if (ledTimer == 0)
            {
                ledTimer = 250;

                LED_1 ^= 1;
                LED_2 = !LED_1;
            }
        }


        // ----------------------------------------------------------------------------
        // Process radio
        // ---------------------------------------------------------------------------- 
        if (MiApp_MessageAvailable())
        {
            if (rxMessage.flags.bits.broadcast == 0)
            {
                uint8_t pktCMD = rxMessage.Payload[0];
                uint8_t pktMSG = rxMessage.Payload[1]; 
                if(pktCMD==0xC5)
                {
                    if(pktMSG == 1)
                    {
                        LED_1 = 1;
                        LED_2 = 0;
                    }
                    else
                    {
                        LED_1 = 0;
                        LED_2 = 1;
                    }
                }
            }
            MiApp_DiscardMessage();
        }
        else
        {  
            if(sendIt)
            {
                MiApp_FlushTx(); 
                MiApp_WriteData(0xC5);  // Command
                MiApp_WriteData(sendIt);
                MiApp_UnicastAddress(sa_vip, false, false);                
                sendIt = 0;
            }
            
        }
        // ----------------------------------------------------------------------------
        // End Process radio
        // ---------------------------------------------------------------------------- 
    }// end while
} // end main


