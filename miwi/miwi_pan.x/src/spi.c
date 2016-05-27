/* 
 * File:   spi.c
 * Author: Not Supported
 *
 */

/************************ HEADERS **********************************/
#include "user.h"
#include "spi.h"


/************************ FUNCTIONS ********************************/

/*********************************************************************
* Function:         void SPIPut(uint8_t v)
*
* PreCondition:     SPI has been configured
*
* Input:		    v - is the byte that needs to be transfered
*
* Output:		    none
*
* Side Effects:	    SPI transmits the byte
*
* Overview:		    This function will send a byte over the SPI
*
* Note:			    None
********************************************************************/
void SPIPut(uint8_t v)
{
    uint8_t i;
    IFS0bits.SPI1IF = 0;
    i = SPI1BUF;
    SPI1BUF = v;
    while(IFS0bits.SPI1IF == 0){}
}


/*********************************************************************
* Function:         uint8_t SPIGet(void)
*
* PreCondition:     SPI has been configured
*
* Input:		    none
*
* Output:		    uint8_t - the byte that was last received by the SPI
*
* Side Effects:	    none
*
* Overview:		    This function will read a byte over the SPI
*
* Note:			    None
********************************************************************/
uint8_t SPIGet(void)
{
    SPIPut(0x00);
    return SPI1BUF;
}

    /*********************************************************************
    * Function:         void SPIPut2(uint8_t v)
    *
    * PreCondition:     SPI has been configured
    *
    * Input:		    v - is the byte that needs to be transfered
    *
    * Output:		    none
    *
    * Side Effects:	    SPI transmits the byte
    *
    * Overview:		    This function will send a byte over the SPI
    *
    * Note:			    None
    ********************************************************************/
    void SPIPut2(uint8_t v)
    {
        uint8_t iii;
        IFS2bits.SPI2IF = 0;
        iii = SPI2BUF;
        SPI2BUF = v;
        while(IFS2bits.SPI2IF == 0){}
    }


    /*********************************************************************
    * Function:         uint8_t SPIGet2(void)
    *
    * PreCondition:     SPI has been configured
    *
    * Input:		    none
    *
    * Output:		    uint8_t - the byte that was last received by the SPI
    *
    * Side Effects:	    none
    *
    * Overview:		    This function will read a byte over the SPI
    *
    * Note:			    None
    ********************************************************************/
    uint8_t SPIGet2(void)
    {
        SPIPut2(0x00);
        return SPI2BUF;
    }
    
    /*********************************************************************
    * Function:         uint8_t SPIWrite2(uint8_t v)
    *
    * PreCondition:     SPI has been configured
    *
    * Input:		    v - is the byte that needs to be transfered
    *
    * Output:		    none
    *
    * Side Effects:	    SPI transmits the byte
    *
    * Overview:		    This function will send a byte over the SPI
    *
    * Note:			    None
    ********************************************************************/
    uint8_t SPIWrite2(uint8_t v)
    {
        SPI2BUF = v;
        while(!SPI2STATbits.SPIRBF);
        return SPI2BUF;
    }
