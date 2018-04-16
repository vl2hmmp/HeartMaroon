/***************************************************************/
/*                                                             */
/*      PROJECT NAME :  HeartMaroon                            */

#include "iodefine.h"
#include "vect.h"
#include "HeartMaroon.h"
#include "main/module/adconverter.h"
#include "main/module/timer.h"
#include "main/module/debug.h"
#include "main/module/photoreflector.h"
#include "main/module/motor.h"
#include "main/module/encorder.h"
#include "main/service/linetrace.h"

void settingClock()
{
	// base clock 12MHz
	// system clock 96MHz
	// bus clock 48MHz
	// module clock 48MHz
	SYSTEM.SCKCR.LONG = 0x00010100;
}

void main(void)
{
	settingClock();
	initializeTimer();
	initializeDebug();
	initializePhotoreflector();
	initializeMotor();
	initializeEncorder();
	initializeADConverter();

	setLedState(InLed, Lighting);
	setLedState(OutLed, Lighting);

	//traceBaseToBase(2, FALSE);

	while (1){
		int val = getEncorder(RightMotor);
		if ((val / 100) % 2 == 0)
			setLedState(InLed, Lighting);
		else
			setLedState(InLed, FastFlashing);

		val = getADConvertValue(0);
		if (val < 100)
			setLedState(OutLed, None);
		else if (val < 200)
			setLedState(OutLed, Pulsing);
		else if (val < 300)
			setLedState(OutLed, SlowFlashing);
		else if (val < 400)
			setLedState(OutLed, FastFlashing);
		else
			setLedState(OutLed, Lighting);
	}
}

void Excep_TMR0_CMIA0(void){
	debugFeed();
	traceFeed();
}
