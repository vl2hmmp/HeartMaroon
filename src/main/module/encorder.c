
#include "../../iodefine.h"
#include "debug.h"
#include "motor.h"
#include "encorder.h"

volatile static long leftCount;
volatile static long rightCount;

void initializeEncorder()
{
	// release standby
	MSTP(MTU1) = 0;
	MSTP(MTU2) = 0;
	MSTP(MTUA) = 0;

	// allow interrupt
	//IEN(MTU1, TCIV1) = ALLOW_INTERRUPT;
	//IEN(MTU1, TCIU1) = ALLOW_INTERRUPT;
	//IEN(MTU2, TCIV2) = ALLOW_INTERRUPT;
	//IEN(MTU2, TCIU2) = ALLOW_INTERRUPT;

	// set interrupt priority
	//IPR(MTU1, TCIV1) = HIGH_PRIORITY;
	//IPR(MTU1, TCIU1) = HIGH_PRIORITY;
	//IPR(MTU2, TCIV2) = HIGH_PRIORITY;
	//IPR(MTU2, TCIU2) = HIGH_PRIORITY;

	// MTU1 stop count
	MTUA.TSTR.BIT.CST1 = 0;
	// MTU2 stop count
	MTUA.TSTR.BIT.CST2 = 0;

	// MTU mode is Phase count 1
	MTU1.TMDR.BIT.MD = 4;
	MTU2.TMDR.BIT.MD = 4;

	MTU1.TIER.BIT.TCIEV = 1;
	MTU1.TIER.BIT.TCIEU = 1;
	MTU2.TIER.BIT.TCIEV = 1;
	MTU2.TIER.BIT.TCIEU = 1;

	// MTU1 start count
	MTUA.TSTR.BIT.CST1 = 1;
	// MTU2 start count
	MTUA.TSTR.BIT.CST2 = 1;

	PORT2.DDR.BIT.B2 = 0;
	PORT2.DDR.BIT.B3 = 0;
	PORT2.DDR.BIT.B4 = 0;
	PORT2.DDR.BIT.B5 = 0;
	PORT2.ICR.BIT.B2 = 1;
	PORT2.ICR.BIT.B3 = 1;
	PORT2.ICR.BIT.B4 = 1;
	PORT2.ICR.BIT.B5 = 1;
}

void startEncorder()
{
	leftCount = 0;
	rightCount = 0;
	MTU1.TCNT = 32768;
	MTU2.TCNT = 32768;
}

float getEncorder(Motor motor)
{
	switch (motor) {
		case LeftMotor:
			return leftCount / 42800.0;
			break;
		case RightMotor:
			return rightCount / 42800.0;
			break;
	}
	return 0;
}

void encodeFeed()
{
	leftCount += MTU2.TCNT - 32768;
	rightCount += MTU1.TCNT - 32768;
	MTU1.TCNT = 32768;
	MTU2.TCNT = 32768;
}
