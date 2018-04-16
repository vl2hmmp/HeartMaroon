
#include "../../iodefine.h"
#include "motor.h"
#include "encorder.h"

void initializeEncorder()
{
	// release standby
	MSTP(MTU1) = 0;
	MSTP(MTU2) = 0;
	MSTP(MTUA) = 0;

	// MTU1 stop count
	MTUA.TSTR.BIT.CST1 = 0;
	// MTU2 stop count
	MTUA.TSTR.BIT.CST2 = 0;

	// MTU mode is Phase count 1
	MTU1.TMDR.BIT.MD = 4;
	MTU2.TMDR.BIT.MD = 4;

	MTU1.TCNT = 0;
	MTU2.TCNT = 0;

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

int getEncorder(Motor motor)
{
	switch (motor) {
		case LeftMotor:
			return MTU2.TCNT;
			break;
		case RightMotor:
			return MTU1.TCNT;
			break;
	}
	return 0;
}
