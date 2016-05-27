/*
 * File:   eeprom.h
 * Author: Not Supported
 *
 */

#ifndef __EEPROM_H
    #define __EEPROM_H

    #define SPI_WRT_STATUS  0x01
#ifndef  SPI_WRITE
    #define SPI_WRITE       0x02
#endif
#ifndef SPI_READ
    #define SPI_READ        0x03
#endif
    #define SPI_DIS_WRT     0x04
    #define SPI_RD_STATUS   0x05
    #define SPI_EN_WRT      0x06


    #define EEPROM_MAC_ADDR 0xFA
    #define EEPROM_PAGE_SIZE 16

    void EEPROMRead(uint8_t *dest, uint8_t addr, uint8_t count);
    void EEPROMWrite(uint8_t *src, uint8_t addr, uint8_t count);
    void EEPROMWait(void);
    void EEPROMWrsr(void);

#endif
