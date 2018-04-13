
#include <stdlib.h>
#include "../../HeartMaroon.h"
#include "../module/motor.h"
#include "../module/photoreflector.h"
#include "linetrace.h"

volatile static int numOfMove = 0;
volatile static int cooldown = 0;

void traceBaseToBase(int number, bool blocking)
{
	numOfMove = number;
	cooldown = 100;

	if (blocking)
		traceWait();
}

void traceWait()
{
	while(numOfMove != 0)
	{
	}
}

void traceFeed()
{
	if (0 < cooldown) cooldown--;

	if (numOfMove == 0) return;

	int photos = getPhotoreflectorState();

	if (photos == 0 && cooldown == 0) onBase();

	if (numOfMove == 0)
	{
		brakingMotor(LeftMotor);
		brakingMotor(RightMotor);
		return;
	}

	if (photos == 0 || photos == 1001){
		setMotorThrottle(LeftMotor, 40);
		setMotorThrottle(RightMotor, 40);
	}
	else if (photos == 1011)
	{
		setMotorThrottle(LeftMotor, 40);
		setMotorThrottle(RightMotor, 30);
	}
	else if (photos == 1101)
	{
		setMotorThrottle(LeftMotor, 30);
		setMotorThrottle(RightMotor, 40);
	}
	else if (photos == 11)
	{
		setMotorThrottle(LeftMotor, 30);
		setMotorThrottle(RightMotor, 10);
	}
	else if (photos == 1100)
	{
		setMotorThrottle(LeftMotor, 10);
		setMotorThrottle(RightMotor, 30);
	}
	else if (photos == 111)
	{
		setMotorThrottle(LeftMotor, 30);
		setMotorThrottle(RightMotor, 0);
	}
	else if (photos == 1110)
	{
		setMotorThrottle(LeftMotor, 0);
		setMotorThrottle(RightMotor, 30);
	}
}

static void onBase()
{
	cooldown = 100;

	if (0 < numOfMove)
		numOfMove--;
	else
		numOfMove++;
}
