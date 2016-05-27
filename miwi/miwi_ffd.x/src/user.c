/* 
 * File:   user.c
 * Author: Not Supported
 *
 */

/* Device header file */
#include <xc.h>
#include <stdint.h>          /* For uint32_t definition */
#include <stdbool.h>         /* For true/false definition */
#include "user.h"            /* variables/params used by user.c */

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/
void InitApp(void)
{
    /* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
     * Beeper and 1ms Timer setup
     * ----------------------------------------------------------------------*/
    beeperOff();
    PIEZO_LAT = 0;
    PIEZO_TRIS = 0;
    
    OC5CON1=0;
    OC5CON2=0;

    OC5RS = FCY/2600-1;
    OC5R = OC5RS/2;

    OC5CON2bits.SYNCSEL=0b11111;
    OC5CON1bits.OCTSEL = 1; //Timer3 as source
    OC5CON1bits.OCM = 0x6;  // Set OCM to PWM
    
    T3CON = 0x00;
    TMR3 = 0x00;
    PR3 = FCY/1000-1;
    _T3IP = 1;
    _T3IF = 0;
    _T3IE = 1;
    T3CONbits.TCKPS = 0;
    T3CONbits.TON = 1;
    //beeperOn();


    /* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
     * INPUT setup
     * ----------------------------------------------------------------------*/
    SW1_TRIS = 1;
    SW2_TRIS = 1;   
   
    SW1_PU = 1;
    SW2_PU = 1;


    /* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
     * Basic IO setup
     * ----------------------------------------------------------------------*/
    LED_1_TRIS = 0;
    LED_2_TRIS = 0;


    /* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
     * SPI setup
     * ----------------------------------------------------------------------*/
    SDI_TRIS = 1;
    SDO_TRIS = 0;
    SCK_TRIS = 0;
    SPI_SDO = 0;
    SPI_SCK = 0;

    Data_nCS_TRIS = 0;
    Config_nCS_TRIS = 0;
    EE_nCS_TRIS = 0;
    EES_nCS_TRIS = 0;
    SSEL_nCS_TRIS = 0;
    Data_nCS = 1;
    Config_nCS = 1;
    EE_nCS = 1;
    EES_nCS = 1;
    SSEL_nCS = 1;

    _SPI1MD = 0;
    SPI1CON1bits.PPRE = 1;  // 4:1 Prescaler
    SPI1CON1bits.SPRE = 6;  // 2:1 Prescaler
    SPI1CON1bits.MSTEN = 1; // Master Mode
    SPI1CON1bits.CKE = 1;   // Clock edge
    SPI1STATbits.SPIEN = 1; // Start Bus

    // Assign SCK1 to RP15 - SCK
    _RP15R = 8;

    // Assign SDO1 to RP14 - MOSI
    _RP14R = 7;

    // Assign SDI1 to RP11 - MISO
    _SDI1R = 11;


    /* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
     * Interrupt setup
     * ----------------------------------------------------------------------*/
    RF_INT_TRIS = 1;
    IRQ1_INT_TRIS = 1;
    IRQ0_INT_TRIS = 1;

    _INT1R = 10; //IRQ0
    _INT2R = 21; //IRQ1

    INTCON2bits.INT1EP = 0;
    INTCON2bits.INT2EP = 0;

    _INT2IP = 4;

    _INT1IP = 4;

    // Make RB0 as Digital input
    AD1PCFGbits.PCFG2 = 1;

    #if defined(ENABLE_NVM)
        EE_nCS_TRIS = 0;
        EE_nCS = 1;
    #endif


    PHY_IRQ1 = 0;
    PHY_IRQ0 = 0;
    PHY_RESETn_TRIS = 1;
}

