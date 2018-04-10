
#ifndef MAIN_DEBUG_H_
#define MAIN_DEBUG_H_

typedef enum
{
	None,
	Lighting,
	SlowFlashing,
	FastFlashing,
	Pulsing
} debugLedState;

void initializeDebug();

void setLedState(debugLedState left, debugLedState right);

void debugFeed();

#endif /* MAIN_DEBUG_H_ */
