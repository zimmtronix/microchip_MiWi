/* 
 * File:   eeprom.c
 * Author: Not Supported
 *
 */

#include "system.h"
#include "user.h"

#include "eeprom.h"

void EEPROMRead(uint8_t *dest, uint8_t addr, uint8_t count)
{
    uint8_t oldRFIE = RFIE;                
    RFIE = 0;   // Disable radio interrupt so it doesn't steal SPI Bus
    
    EE_nCS = 0;
    __delay_us(1);
    
    SPIWrite(SPI_READ);
    __delay_us(1);
    SPIWrite(addr);
    __delay_us(1);
    
    while (count)
    {
        *dest++ = SPIWrite(0);
        count--;
    }
    EE_nCS = 1;
    RFIE = oldRFIE; // Enable radio interrupt 
}

void EEPROMWrite(uint8_t *src, uint8_t addr, uint8_t count)
{
    uint8_t PageCounter = 0;
    uint8_t oldRFIE = RFIE;
    RFIE = 0; // Disable radio interrupt so it doesn't steal SPI Bus

EEPROM_NEXT_PAGE:
    EEPROMWait();

    EE_nCS = 0;
    __delay_us(1);
    SPIWrite(SPI_EN_WRT);
    __delay_us(1);
    EE_nCS = 1;
    __delay_us(1);
    EE_nCS = 0;
    __delay_us(1);
    
    SPIWrite(SPI_WRITE);
    __delay_us(1);
    SPIWrite(addr);
    
    PageCounter = 0;
    while (count > 0)
    {
        SPIWrite(*src++);
        count--;
        PageCounter++;
        if (((addr + PageCounter) & (EEPROM_PAGE_SIZE - 1)) == 0)
        {
            EE_nCS = 1;
            addr += PageCounter;
            goto EEPROM_NEXT_PAGE;
        }
    }
    EE_nCS = 1;
    __delay_us(1);
    RFIE = oldRFIE; // Enable radio interrupt 
}


void EEPROMWait()
{
    uint8_t PageCounter = 0;
    do
    {
        EE_nCS = 0;
        __delay_us(1);
        SPIWrite(SPI_RD_STATUS);
        PageCounter = SPIWrite(0);
        EE_nCS = 1;
        __delay_us(1);
    }
    while (PageCounter & 0x01);    
}

void EEPROMWrsr()
{
//        EE_nCS = 0;
//        __delay_us(1);
//        SPIWrite(SPI_WRT_STATUS);
//        SPIWrite(0x04);
//        EE_nCS = 1;
//        __delay_us(1);
    
}

