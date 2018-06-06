/***************************************************************/
/*                                                             */
/*      PROJECT NAME :  HeartMaroon                            */

#include "iodefine.h"
#include "vect.h"
#include "HeartMaroon.h"

#include "main/module/ad_converter.h"
#include "main/module/timer.h"
#include "main/module/debug.h"
#include "main/module/photoreflector.h"
#include "main/module/motor.h"
#include "main/module/encorder.h"
#include "main/module/psd_sensor.h"
#include "main/module/trajectory_tracking_control.h"
#include "main/service/line_trace.h"
#include "main/service/search_line.h"

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
	initializeTrajectoryTracking();

	setMotorThrottle(LeftMotor, 0);
	setMotorThrottle(RightMotor, 0);

	setLedState(InLed, Lighting);
	setLedState(OutLed, Lighting);
	sleep(1000);

	startEncorder();
	trajectoryTracking(0.0F, 90.0F, 5.0F);

/*
	setMotorThrottle(LeftMotor, 40);
	setMotorThrottle(RightMotor, 40);
	sleep(1200);
	setMotorThrottle(LeftMotor, 0);
	setMotorThrottle(RightMotor, 0);
	sleep(1000);

	searchLine();

	traceBaseToBase(3, FALSE);
*/

	while (1)
	{
		/*
		int val = (int)getEncorder(RightMotor);
		if (val % 2 == 0)
			setLedState(InLed, Lighting);
		else
			setLedState(InLed, None);

		val = (int)getEncorder(LeftMotor);
		if (val % 2 == 0)
			setLedState(OutLed, Lighting);
		else
			setLedState(OutLed, None);
			*/
	}
}

void feed()
{
	debugFeed();
	encoderFeed();
	traceFeed();
	trackingFeed();

//	int val = getDistance();
//	if (val < 10)
//		setLedState(OutLed, None);
//	else if (val < 20)
//		setLedState(OutLed, Pulsing);
//	else if (val < 30)
//		setLedState(OutLed, SlowFlashing);
//	else if (val < 40)
//		setLedState(OutLed, FastFlashing);
//	else
//		setLedState(OutLed, Lighting);
}
