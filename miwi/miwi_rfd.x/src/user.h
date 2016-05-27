/* 
 * File:   user.h
 * Author: Not Supported
 *
 */

#ifndef __USER_H
#define __USER_H

#include "miwi_config.h"          //MiWi Application layer configuration file
//#include "miwi_config_p2p.h"      //MiWi Protocol layer configuration file
#include "miwi_config_mesh.h"      //MiWi Protocol layer configuration file
//#include "miwi_config_pro.h"      //MiWi Protocol layer configuration file
#include "config_89xa.h"          //Tranceiver configuration file
#include "system.h"

/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/
void InitApp(void); // I/O and Peripheral Initialization 

/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/

#define beeperOn()  (_RP5R = 22)   
#define beeperOff() (_RP5R = 0)
#define beeping()   (_RP5R != 0)

#define SOFTWARE_SECURITY

#define USE_EXTERNAL_EEPROM

#define EEPROM_SHARE_SPI

//TRANSCEIVER DEFINITIONS
#define PHY_IRQ1                    _INT2IF
#define PHY_IRQ1_En                 _INT2IE
#define PHY_IRQ0                    _INT1IF
#define PHY_IRQ0_En                 _INT1IE

#define IRQ1_INT_PIN                _RC5
#define IRQ1_INT_TRIS               _TRISC5
#define IRQ0_INT_PIN                _RB10
#define IRQ0_INT_TRIS               _TRISB10

#define Config_nCS                  _LATA7
#define Config_nCS_TRIS             _TRISA7
#define Data_nCS                    _LATA8
#define Data_nCS_TRIS               _TRISA8
#define PHY_RESETn                  _LATA10
#define PHY_RESETn_TRIS             _TRISA10

//SPI DEFINITIONS
#define SPI_SDI                     _LATB11
#define SDI_TRIS                    _TRISB11
#define SPI_SDO                     _LATB14
#define SDO_TRIS                    _TRISB14
#define SPI_SCK                     _LATB15
#define SCK_TRIS                    _TRISB15

//PUSH BUTTON, LED PIN DEFINITIONS
#define SW1_                        _RB7   
#define SW1_TRIS                    _TRISB7
#define SW1_IE                      _CN23IE
#define SW1_PU                      _CN23PUE

#define SW2_                        _RB6   
#define SW2_TRIS                    _TRISB6
#define SW2_IE                      _CN24IE
#define SW2_PU                      _CN24PUE

#define LED_2                       _LATC8
#define LED_1                       _LATC9
#define LED_2_TRIS                  _TRISC8
#define LED_1_TRIS                  _TRISC9

// Beeper
#define PIEZO_LAT                   _LATB5
#define PIEZO_TRIS                  _TRISB5
#define PIEZO                       PIEZO_LAT

// External EEPROM SPI chip select pin definition
#define EE_nCS_TRIS                 _TRISA3
#define EE_nCS                      _LATA3

#define EES_nCS_TRIS                _TRISA2
#define EES_nCS                     _LATA2
#define SSEL_nCS_TRIS               _TRISB4
#define SSEL_nCS                    _LATB4

#define TMRL TMR2

#endif
