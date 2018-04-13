
#include "../../iodefine.h"
#include "encorder.h"

void initializeEncorder()
{
	// release standby
	MSTP(MTU1) = 0;
	MSTP(MTU2) = 0;
	MSTP(MTUA) = 0;

	// MTU mode is Phase count 1
	MTU1.TMDR.BIT.MD = 4;
	MTU2.TMDR.BIT.MD = 4;

	MTU1.TCNT = 0;
	MTU2.TCNT = 0;

	// MTU6 start count
	MTUA.TSTR.BIT.CST1 = 1;
	MTUA.TSTR.BIT.CST2 = 1;
}
