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
#include "main/module/dead_reckoning.h"
#include "main/service/line_trace.h"
#include "main/service/search_line.h"
#include "main/service/search_ball.h"

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
	initializeDeadReckoning();

	setMotorThrottle(LeftMotor, 0);
	setMotorThrottle(RightMotor, 0);

	setLedState(InLed, Lighting);
	setLedState(OutLed, Lighting);
	sleep(1000);

	startEncorder();

	//searchLine();

	//traceBaseToBase(3, FALSE);

	setBasePosition();
	setSearchingBase();
	float dir = 0;
	float dst = 0;
	bool result = searchBall(&dir, &dst);
	if (result){
		trajectoryTracking(0.0F, dir * Rad2Deg, 3.0F);
		waitForTracking();
		trajectoryTracking(dst, 0.0F, 3.0F);
		waitForTracking();
		returnBase();
	}

	while (1)
	{
		/*
		float val = getDistance();
		if (val < 0.1)
			setLedState(OutLed, None);
		else if (val < 0.2)
			setLedState(OutLed, Pulsing);
		else if (val < 0.3)
			setLedState(OutLed, SlowFlashing);
		else if (val < 0.4)
			setLedState(OutLed, FastFlashing);
		else
			setLedState(OutLed, Lighting);
			*/
	}
}

void feed()
{
	debugFeed();
	encoderFeed();
	traceFeed();
	trackingFeed();
	deadReckoningFeed();
}
