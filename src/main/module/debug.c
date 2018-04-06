
#include <stdio.h>
#include "../../iodefine.h"
#include "debug.h"

volatile static debugLedState inDebugLedState;
volatile static debugLedState outDebugLedState;
volatile static int count;

void initializeDebug()
{
	PORTD.DDR.BIT.B4 = 1;
	PORTD.DDR.BIT.B5 = 1;
	inDebugLedState = None;
	outDebugLedState = None;
}

void setLedState(debugLedState in, debugLedState out)
{
	inDebugLedState = in;
	outDebugLedState = out;
}

void debugFeed()
{
	// update count
	count++;
	if (100 <= count) count = 0;

	switch (inDebugLedState) {
		case None:
			PORTD.DR.BIT.B4 = 0;
			break;
		case Lighting:
			PORTD.DR.BIT.B4 = 1;
			break;
		case SlowFlashing:
			if ((count / 50) % 2 == 0)
				PORTD.DR.BIT.B4 = 0;
			else
				PORTD.DR.BIT.B4 = 1;
			break;
		case FastFlashing:
			if ((count / 10) % 2 == 0)
				PORTD.DR.BIT.B4 = 0;
			else
				PORTD.DR.BIT.B4 = 1;
			break;
		case Pulsing:
			if (count < 5)
				PORTD.DR.BIT.B4 = 1;
			else
				PORTD.DR.BIT.B4 = 0;
			break;
		default:
			break;
	}
	switch (outDebugLedState) {
		case None:
			PORTD.DR.BIT.B5 = 0;
			break;
		case Lighting:
			PORTD.DR.BIT.B5 = 1;
			break;
		case SlowFlashing:
			if ((count / 50) % 2 == 1)
				PORTD.DR.BIT.B5 = 0;
			else
				PORTD.DR.BIT.B5 = 1;
			break;
		case FastFlashing:
			if ((count / 10) % 2 == 1)
				PORTD.DR.BIT.B5 = 0;
			else
				PORTD.DR.BIT.B5 = 1;
			break;
		case Pulsing:
			if (50 <= count && count < 55)
				PORTD.DR.BIT.B5 = 1;
			else
				PORTD.DR.BIT.B5 = 0;
			break;
		default:
			break;
	}
}
