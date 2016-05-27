/* 
 * File:   symbol.c
 * Author: Not Supported
 *
 */

#include "system.h"


/************************ VARIABLES ********************************/

volatile uint8_t timerExtension1,timerExtension2;

/************************ FUNCTIONS ********************************/

/*********************************************************************
* Function:         void InitSymbolTimer()
*
* PreCondition:     none
*
* Input:            none
*
* Output:           none
*
* Side Effects:
*
* Overview:         This function will configure the UART for use at
*                   in 8 bits, 1 stop, no flow control mode
*
* Note:
********************************************************************/
void InitSymbolTimer()
{
    T4CON = 0b0000000000001000 | CLOCK_DIVIDER_SETTING;
    T4CONbits.TON = 1;

}


/*********************************************************************
* Function:         void InitSymbolTimer()
*
* PreCondition:     none
*
* Input:            none
*
* Output:           MIWI_TICK - the current symbol time
*
* Side Effects:
*
* Overview:         This function returns the current time
*
* Note:
********************************************************************/
MIWI_TICK MiWi_TickGet(void)
{
    MIWI_TICK currentTime;

    currentTime.word.w1 = TMR5;
    currentTime.word.w0 = TMR4;
    if( currentTime.word.w1 != TMR5 )
   {
       currentTime.word.w1 = TMR5;
       currentTime.word.w0 = TMR4;
    }

    return currentTime;
}

