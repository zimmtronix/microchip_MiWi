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
     * Simple timer setup
     * ----------------------------------------------------------------------*/
    PR2 = FCY/256/100-1;
    TMR2 = 0;
    T2CONbits.TCKPS = 3;
    T2CONbits.TON = 1;
    _T2IP = 2;  // Interrupt priority 2 (low)
    _T2IF = 0;
    _T2IE = 1;


    /* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
     * Beeper setup
     * ----------------------------------------------------------------------*/
    //beeper_off();  // Set io to pin
    _RP16R=0;
    PIEZO_TRIS = 0;
    PIEZO_LAT = 0;
    
    OC5CON1=0;
    OC5CON2=0;

    OC5RS = FCY/2600-1;
    OC5R = OC5RS/2;

    OC5CON2bits.SYNCSEL=0b11111;
    OC5CON1bits.OCTSEL = 1; //Timer3 as source
    OC5CON1bits.OCM = 0x6;  // Set OCM to PWM

    PR3 = FCY/1000-1;
    TMR3 = 0;
    T3CONbits.TCKPS = 0;
    T3CONbits.TON = 1;
    _T3IP = 2;  // Interrupt priority 2 (low)
    _T3IF = 0;
    _T3IE = 1;
    //beeper_on();  // Set pwm to pin

    /* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
     * Switch setup and on change interrupt
     * ----------------------------------------------------------------------*/
    SW1_TRIS = 1;
    _CN58PUE = 1;

    SW2_TRIS = 1;
    _CN59PUE = 1;

    SW3_TRIS = 1;
    _CN60PUE = 1;

    SW4_TRIS = 1;
    _CN61PUE = 1;

    SW5_TRIS = 1;
    _CN62PUE = 1;

    /* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
     * Basic IO setup
     * ----------------------------------------------------------------------*/
    RED_1_TRIS = 0;
    GRN_1_TRIS = 0;
    RED_2_TRIS = 0;
    GRN_2_TRIS = 0;
    RED_3_TRIS = 0;
    GRN_3_TRIS = 0;
    RED_4_TRIS = 0;
    GRN_4_TRIS = 0;
    RED_5_TRIS = 0;
    GRN_5_TRIS = 0;

    // Valve Board IO
    WSNS1_TRIS = 1;
    WSNS2_TRIS = 1;

    ACO1 = 0;
    ACO1_TRIS = 0;

    ACO2 = 0;
    ACO2_TRIS = 0;
    
    PWR_CLKA =0;
    PWR_CLKA_TRIS =0;
    PWR_CLKB =0;
    PWR_CLKB_TRIS =0;

    ACIA1_TRIS = 1;
    ACIA2_TRIS = 1;
    ACIB1_TRIS = 1;
    ACIB2_TRIS = 1;
    

    PWR_CLK1 = 0;
    PWR_CLK1_TRIS = 0;
    PWR_CLK2 = 0;
    PWR_CLK2_TRIS = 0;

    VLV_ON1 = 0;
    VLV_ON1_TRIS = 0;
    VLV_ON2 = 0;
    VLV_ON2_TRIS = 0;

    VLV_EN1 = 0;
    VLV_EN1_TRIS = 0;
    VLV_EN2 = 0;
    VLV_EN2_TRIS = 0;


    VLV_FB1_TRIS = 1;
    VLV_FB2_TRIS = 1;

    /* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
     * SPI setup
     * ----------------------------------------------------------------------*/
    SDI_TRIS = 0;
    SDO_TRIS = 1;
    SCK_TRIS = 0;
    SPI_SDO = 0;
    SPI_SCK = 0;

    SDI2_TRIS = 0;
    SDO2_TRIS = 1;
    SCK2_TRIS = 0;
    SPI_SDO2 = 0;
    SPI_SCK2 = 0;

    Data_nCS_TRIS = 0;
    Config_nCS_TRIS = 0;
    EE_nCS_TRIS = 0;
    EES_nCS_TRIS = 0;
    NET_nCS_TRIS = 0;


    Data_nCS = 1;
    Config_nCS = 1;
    EE_nCS = 1;
    EES_nCS = 1;
    NET_nCS = 1;


    //SPI 1
    _SPI1MD = 0;
    SPI1CON1bits.PPRE = 1;  // 16:1 Prescaler
    SPI1CON1bits.SPRE = 6;  // 2:1 Prescaler
    SPI1CON1bits.MSTEN = 1; // Master Mode
    SPI1CON1bits.CKE = 1;   // Clock edge
    SPI1STATbits.SPIEN = 1; // Start Bus

    // Assign SCK1 to RP11 - SCK
    _RP11R = 8;

    // Assign SDO1 to RP12 - MISO
    _RP3R = 7;

    // Assign SDI1 to RP3 - MOSI
    _SDI1R = 12;
    
    //SPI 2
    _SPI2MD = 0;
    SPI2CON1bits.PPRE = 1;  // 16:1 Prescaler
    SPI2CON1bits.SPRE = 7;  // 1:1 Prescaler
    SPI2CON1bits.MSTEN = 1; // Master Mode
    SPI2CON1bits.CKE = 1;   // Clock edge
    SPI2STATbits.SPIEN = 1; // Start Bus

    // Assign SCK2 to RP4 - SCK
    _RP4R = 11;

    // Assign SDO2 to RP2 - MISO
    _RP2R = 10;

    // Assign SDI2 to RP35 - MOSI
    _SDI2R = 35;

    // Extra pin on Ethernet board.
    IRQ4_TRIS = 1;

    // Interrupts
    RF_INT_TRIS = 1;
    IRQ1_INT_TRIS = 1;
    IRQ0_INT_TRIS = 1;

    _INT1R = 10;
    _INT2R = 17;

    _INT1EP = 0; //positive edge
    _INT2EP = 0; //positive edge
    
    _INT1IP = 4;  // 0-7 priority 7 highest
    _INT2IP = 4;  // 0-7 priority 7 highest

    PHY_IRQ1 = 0;
    PHY_IRQ0 = 0;
    PHY_RESETn_TRIS = 1;
}

uint8_t ButtonPressed(void)
{
    uint8_t retval = 0;
    
     
    if(SW1==0)
    {
        retval|=0b00001;
    }
    if(SW2==0)
    {
        retval|=0b00010;
    }
    if(SW3==0)
    {
        retval|=0b00100;
    }
    if(SW4==0)
    {
        retval|=0b01000;
    }
    if(SW5==0)
    {
        retval|=0b10000;
    }
    
    return retval;
}

void ReadMacAddress(void)
{
    uint8_t i;

	if( MY_ADDRESS_LENGTH > 6 )
	{
	    for(i = 0; i < 3; i++)
	    {
	        EEPROMRead(&(myLongAddress[MY_ADDRESS_LENGTH-1-i]), EEPROM_MAC_ADDR+i, 1);
	    }

	    if( MY_ADDRESS_LENGTH > 7 )
	    {
                myLongAddress[4] = 0xFF;

	    }
            myLongAddress[3] = 0xFE;

	    for(i = 0; i < 3; i++)
	    {
	        EEPROMRead(&(myLongAddress[2-i]), EEPROM_MAC_ADDR+3+i, 1);
	    }
	}
	else
	{
	    for(i = 0; i < MY_ADDRESS_LENGTH; i++)
	    {
	        EEPROMRead(&(myLongAddress[i]), EEPROM_MAC_ADDR+5-i, 1);
	    }
	}
}
