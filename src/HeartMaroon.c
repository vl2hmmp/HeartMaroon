/***************************************************************/
/*                                                             */
/*      PROJECT NAME :  HeartMaroon                            */


#include <stdio.h>
#include "iodefine.h"
#include "vect.h"
#include "main/module/timer.h"
#include "main/module/debug.h"
#include "main/module/photoreflector.h"
#include "main/module/motor.h"

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

	setLedState(Lighting, Lighting);

	while (1){
		int photos = getPhotoreflectorState();
	}
}

void Excep_TMR0_CMIA0(void){
	debugFeed();
}
