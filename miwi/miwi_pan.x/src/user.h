/* 
 * File:   user.h
 * Author: Not Supported
 *
 */

#ifndef __USER_H
#define __USER_H

#include "system.h"
#include <libpic30.h>

#include "miwi_config.h"          //MiWi Application layer configuration file
//#include "miwi_config_p2p.h"      //MiWi Protocol layer configuration file
#include "miwi_config_mesh.h"      //MiWi Protocol layer configuration file
//#include "miwi_config_pro.h"      //MiWi Protocol layer configuration file
#include "config_89xa.h"         //Tranceiver configuration file
#include "eeprom.h"


/* Legacy Defines for porting code*/
typedef uint8_t BYTE;
typedef uint16_t WORD;
typedef uint32_t DWORD;
typedef long LONG;
typedef bool BOOL;

/******************************************************************************/
/* Function Defines                                                           */
/******************************************************************************/

uint8_t getConnMode();
uint8_t getIsValid(uint8_t iii);
uint8_t getlongAddressValid(uint8_t iii);
uint8_t getshortAddressValid(uint8_t iii);
uint8_t getConnectionAddress(uint8_t map,uint8_t id);
uint8_t getRXOnWhenIdle(uint8_t iii);
uint8_t getdirectConnection(uint8_t iii);
uint8_t getPeerInfo(uint8_t iii,uint8_t jjj);
uint8_t getAltAddress(uint8_t iii,uint8_t jjj);
uint8_t getPANID(uint8_t iii,uint8_t jjj);

void ReadMacAddress(void);

uint8_t ButtonPressed(void);

/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/

#define beeperOn()  (_RP16R = 22)   
#define beeperOff() (_RP16R = 0)
#define beeping()   (_RP16R != 0)
#define beeper_on()                 _RP16R=22  
#define beeper_off()                _RP16R=0   
#define beeper_status()             _RP16R

/******************************************************************************/
/* Global variables                                                           */
/******************************************************************************/

extern uint8_t myLongAddress[];

/******************************************************************************/
/* enum values and structures                                                 */
/******************************************************************************/


typedef struct {
    uint8_t miwiPresent;
} MODULE;

/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/
#define DEV_GATEWAY 0xFF
#define DEV_WS  0x10
#define DEV_TH  0x11
#define DEV_FT  0x12
#define DEV_RS  0x30
#define DEV_RP  0xF0

#define DEVICE_TYPE DEV_GATEWAY

#define SOFTWARE_SECURITY

#define USE_EXTERNAL_EEPROM

//TRANSCEIVER DEFINITIONS
#define PHY_IRQ1                    _INT2IF
#define PHY_IRQ1_En                 _INT2IE
#define PHY_IRQ0                    _INT1IF
#define PHY_IRQ0_En                 _INT1IE

#define IRQ1_INT_PIN                _RF5
#define IRQ1_INT_TRIS               _TRISF5
#define IRQ0_INT_PIN                _RF4
#define IRQ0_INT_TRIS               _TRISF4

#define PHY_RESETn                  _RD5
#define PHY_RESETn_TRIS             _TRISD5

// SPI Chip Select
#define Data_nCS                    _LATD4
#define Data_nCS_TRIS               _TRISD4
#define Config_nCS                  _LATD13
#define Config_nCS_TRIS             _TRISD13
#define NET_nCS                     _LATD12
#define NET_nCS_TRIS                _TRISD12
#define EE_nCS_TRIS                 _TRISD2
#define EE_nCS                      _LATD2      //Small EEPROM with MAC
#define EES_nCS_TRIS                _TRISD1
#define EES_nCS                     _LATD1      //Large EEPROM without MAC 

#define M95M02_nCS                  EES_nCS
#define EE25AA02_nCS                EE_nCS

//SPI DEFINITIONS
#define SPI_SDI                     _LATD10
#define SDI_TRIS                    _TRISD10
#define SPI_SDO                     _LATD11
#define SDO_TRIS                    _TRISD11
#define SPI_SCK                     _LATD0
#define SCK_TRIS                    _TRISD0

#define SPI_SDI2                     _LATD8
#define SDI2_TRIS                    _TRISD8
#define SPI_SDO2                     _LATA15
#define SDO2_TRIS                    _TRISA15
#define SPI_SCK2                     _LATD9
#define SCK2_TRIS                    _TRISD9

#define IRQ4                     _LATD14
#define IRQ4_TRIS                _TRISD14

#define ENC100_SPISTATbits          (SPI1STATbits)
#define ENC100_CS_IO                NET_nCS
#define ENC100_CS_TRIS              NET_nCS_TRIS
#define ENC100_SSPBUF               SPI1BUF
#define ENC100_SPISTAT              SPI1STAT
#define ENC100_SPICON1              SPI1CON1

//PUSH BUTTON, LED PIN DEFINITIONS
#define SW5                         _RE4
#define SW5_TRIS                    _TRISE4
#define SW4                         _RE3
#define SW4_TRIS                    _TRISE3
#define SW3                         _RE2
#define SW3_TRIS                    _TRISE2
#define SW2                         _RE1
#define SW2_TRIS                    _TRISE1
#define SW1                         _RE0
#define SW1_TRIS                    _TRISE0

#define RED_5                       _LATA9
#define RED_5_TRIS                  _TRISA9
#define GRN_5                       _LATA10
#define GRN_5_TRIS                  _TRISA10
#define RED_4                       _LATB8
#define RED_4_TRIS                  _TRISB8
#define GRN_4                       _LATB9
#define GRN_4_TRIS                  _TRISB9
#define RED_3                       _LATB10
#define RED_3_TRIS                  _TRISB10
#define GRN_3                       _LATB11
#define GRN_3_TRIS                  _TRISB11
#define RED_2                       _LATB12
#define RED_2_TRIS                  _TRISB12
#define GRN_2                       _LATB13
#define GRN_2_TRIS                  _TRISB13
#define RED_1                       _LATB14
#define RED_1_TRIS                  _TRISB14
#define GRN_1                       _LATB15
#define GRN_1_TRIS                  _TRISB15

// Beeper
#define PIEZO_LAT                   _LATF3
#define PIEZO_TRIS                  _TRISF3

// Valve Board IO
#define WAT1_SNS                    _RE6
#define WSNS1_TRIS                  _TRISE6
#define WAT2_SNS                    _RC1
#define WSNS2_TRIS                  _TRISC1

#define ACO1                        _LATE5
#define ACO1_READ                   _RE5
#define ACO1_TRIS                   _TRISE5
#define ACO1_PU                     _CN63PUE
#define ACO2                        _LATE7
#define ACO2_READ                   _RE7
#define ACO2_TRIS                   _TRISE7
#define ACO2_PU                     _CN65PUE

#define PWR_CLK1                    _LATG8
#define PWR_CLK1_TRIS               _TRISG8
#define PWR_CLK2                    _LATG7
#define PWR_CLK2_TRIS               _TRISG7

#define ACIA1                        _RG6           //ACI1
#define ACIA1_TRIS                   _TRISG6
#define ACIA2                        _RB6           //SIGA
#define ACIA2_TRIS                   _TRISB6

#define ACIB1                        _RC3           //ACI2
#define ACIB1_TRIS                   _TRISC3
#define ACIB2                        _RB7           //SIGB
#define ACIB2_TRIS                   _TRISB7


#define VLV_ON1                    _LATG0
#define VLV_ON1_TRIS               _TRISG0
#define VLV_ON2                    _LATF1
#define VLV_ON2_TRIS               _TRISF1

#define VLV_EN1                    _LATD7
#define VLV_EN1_TRIS               _TRISD7
#define VLV_EN2                    _LATD6
#define VLV_EN2_TRIS               _TRISD6

#define VLV_FB1                    _RG1
#define VLV_FB1_TRIS               _TRISG1
#define VLV_FB2                    _RF0
#define VLV_FB2_TRIS               _TRISF0

// Eternet Board
#define PWR_CLKA                    _LATE8
#define PWR_CLKA_TRIS               _TRISE8
#define PWR_CLKB                    _LATE9
#define PWR_CLKB_TRIS               _TRISE9

//ANALOG INPUTS
#define VBAT_LAT                    _LATB2
#define VBAT_TRIS                   _TRISB2
#define VBAT_AN                     _PCFG2
#define VBAT_CSSL                   _CSSL2
#define VBAT_CHANNEL                2

#define ISNS_LAT                    _LATB3
#define ISNS_TRIS                   _TRISB3
#define ISNS_AN                     _PCFG3
#define ISNS_CSSL                   _CSSL3
#define ISNS_CHANNEL                3

#define TEMP_LAT                    _LATB4
#define TEMP_TRIS                   _TRISB4
#define TEMP_AN                     _PCFG4
#define TEMP_CSSL                   _CSSL4
#define TEMP_CHANNEL                4

#define VPOS_LAT                    _LATB5
#define VPOS_TRIS                   _TRISB5
#define VPOS_AN                     _PCFG5
#define VPOS_CSSL                   _CSSL5
#define VPOS_CHANNEL                5

#define REF_AN                      _PCFG17
#define REF_CSSL                    _CSSL17
#define REF_CHANNEL                 17

#define TMRL TMR2

/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/
void InitApp(void); /* I/O and Peripheral Initialization */

#endif
