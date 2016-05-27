/* 
 * File:   configuration_bits.c
 * Author: Not Supported
 *
 */

/* Device header file */
#include <xc.h>

_CONFIG1(JTAGEN_OFF & FWDTEN_OFF & WDTPS_PS1024)	// JTAG off, watchdog timer off
_CONFIG2(FNOSC_FRCPLL & OSCIOFNC_ON & POSCMOD_NONE)	// FRC with 4x PLL
_CONFIG3(SOSCSEL_IO);                                   // SOSCI pins as IO
_CONFIG4(RTCOSC_LPRC);                                  // RTCC uses LPRC 
        
