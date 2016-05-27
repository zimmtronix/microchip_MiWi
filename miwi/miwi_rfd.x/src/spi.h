/* 
 * File:   spi.h
 * Author: Not Supported
 *
 */

#ifndef SPI_H
#define	SPI_H

#include <stdint.h>

/************************ FUNCTION PROTOTYPES **********************/
void SPIPut(uint8_t v);
uint8_t SPIGet(void);
uint8_t SPIWrite(uint8_t v);

/************************ MACROS ***********************************/
#define SPIInit()   SSPIF = 1

#endif	/* SPI_H */

