
#include <stdlib.h>
#include "../../iodefine.h"
#include "../../HeartMaroon.h"
#include "motor.h"
#include "utils.h"

void initializeMotor()
{
	// release standby
	MSTP(MTU6) = 0;
	MSTP(MTUB) = 0;

	// MTU clock is 750kHz
	MTU6.TCR.BIT.TPSC = 3;

	// clear on compare match TGRA
	// MTIOC6X go to high from low on compare match TGRA
	MTU6.TCR.BIT.CCLR = 1;

	// MTU mode is PWM 2
	MTU6.TMDR.BIT.MD = 3;

	// MTIOC6A is no output
	// MTIOC6B is changed from high to low on compare match TGRB
	MTU6.TIORH.BYTE = 0x50;//0b01010000
	// MTIOC6C is no output
	// MTIOC6D is changed from high to low on compare match TGRD
	MTU6.TIORL.BYTE = 0x50;//0b01010000

	// PWM frequency is 7.5kHz
	MTU6.TGRA = 100;

	// MTU6 start count
	MTUB.TSTR.BIT.CST0 = 1;

	PORTC.DDR.BIT.B0 = 1;
	PORTC.DDR.BIT.B1 = 1;
	PORTC.DDR.BIT.B2 = 1;
	PORTC.DDR.BIT.B3 = 1;

	setMotorThrottle(LeftMotor, 0);
	setMotorThrottle(RightMotor, 0);
	brakingMotor(LeftMotor);
	brakingMotor(RightMotor);
}

void setMotorThrottle(Motor motor, int throttle)
{
	char forwardFlag = 0 <= throttle;
	char reverseFlag = throttle < 0;
	int th = limit(throttle, -100, 100);

	switch (motor) {
		case LeftMotor:
			PORTC.DR.BIT.B2 = reverseFlag;
			PORTC.DR.BIT.B3 = forwardFlag;
			MTU6.TGRD = abs(th);
			break;
		case RightMotor:
			PORTC.DR.BIT.B0 = reverseFlag;
			PORTC.DR.BIT.B1 = forwardFlag;
			MTU6.TGRB = abs(th);
			break;
	}
}

void brakingMotor(Motor motor)
{
	switch (motor) {
		case LeftMotor:
			PORTC.DR.BIT.B2 = 1;
			PORTC.DR.BIT.B3 = 1;
			break;
		case RightMotor:
			PORTC.DR.BIT.B0 = 1;
			PORTC.DR.BIT.B1 = 1;
			break;
	}
}
