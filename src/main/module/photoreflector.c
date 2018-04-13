
#include "../../iodefine.h"
#include "photoreflector.h"

void initializePhotoreflector()
{
	PORTD.DDR.BIT.B0 = 0;
	PORTD.DDR.BIT.B1 = 0;
	PORTD.DDR.BIT.B2 = 0;
	PORTD.DDR.BIT.B3 = 0;
	PORTD.ICR.BIT.B0 = 1;
	PORTD.ICR.BIT.B1 = 1;
	PORTD.ICR.BIT.B2 = 1;
	PORTD.ICR.BIT.B3 = 1;
}

int getPhotoreflectorState()
{
	char p0 = PORTD.PORT.BIT.B0;
	char p1 = PORTD.PORT.BIT.B1;
	char p2 = PORTD.PORT.BIT.B2;
	char p3 = PORTD.PORT.BIT.B3;
	return p0 * 1000 + p1 * 100 + p2 * 10 + p3;
}
