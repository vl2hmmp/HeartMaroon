
#ifndef MAIN_MODULE_MOTOR_H_
#define MAIN_MODULE_MOTOR_H_

#include "../../HeartMaroon.h"

typedef enum
{
	LeftMotor,
	RightMotor
} Motor;

void initializeMotor();

void setMotorThrottle(Motor motor, int throttle);

void brakingMotor(Motor motor);

#endif /* MAIN_MODULE_MOTOR_H_ */
