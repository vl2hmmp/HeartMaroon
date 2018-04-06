/***************************************************************/
/*                                                             */
/*      PROJECT NAME :  HeartMaroon                            */


#include <stdio.h>
#include "iodefine.h"
#include "vect.h"
#include "main/module/debug.h"

void settingClock()
{
	// base clock 12MHz
	// system clock 96MHz
	// bus clock 48MHz
	// module clock 48MHz
	SYSTEM.SCKCR.LONG = 0x00010100;
}

void settingTimer()
{
	// release standby
	MSTP(TMR0) = 0;
	MSTP(TMR1) = 0;

	// allow interrupt
	IEN(TMR0, CMIA0) = 1;
	IEN(TMR1, OVI1) = 1;

	// set interrupt priority
	IPR(TMR0, CMIA0) = 1;
	IPR(TMR1, OVI1) = 1;

	// clear on compare match A
	TMR0.TCR.BYTE = 0x48;//0b01001000
	// clear on TCNT overflow
	TMR1.TCR.BYTE = 0x00;//0b00000000

	// timer 0 clock is 23.4kHz
	TMR0.TCCR.BYTE = 0x18;//00011000
	// timer 1 clock is 6MHz
	TMR1.TCCR.BYTE = 0x0A;//00001010

	// timer 0 compare match every 9.98 millisecond
	TMR0.TCORA = 0xEA;//234
}

void main(void)
{
	settingClock();
	settingTimer();
	initializeDebug();

	setLedState(Pulsing, Pulsing);

	while (1){
	}
}

void Excep_TMR0_CMIA0(void){
	debugFeed();
}
