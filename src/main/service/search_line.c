
#include "../module/motor.h"
#include "../module/photoreflector.h"
#include "search_line.h"

void searchLine()
{
	setMotorThrottle(LeftMotor, 26);
	setMotorThrottle(RightMotor, 0);

	while (getPhotoreflectorState() == 1111);

	setMotorThrottle(LeftMotor, 0);
	setMotorThrottle(RightMotor, 0);
}
