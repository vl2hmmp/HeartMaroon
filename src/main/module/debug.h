
#ifndef MAIN_DEBUG_H_
#define MAIN_DEBUG_H_

typedef enum
{
	InLed,
	OutLed
} DebugLed;

typedef enum
{
	None,
	Lighting,
	SlowFlashing,
	FastFlashing,
	Pulsing
} DebugLedState;

void initializeDebug();

void setLedState(DebugLed led, DebugLedState state);

void debugFeed();

#endif /* MAIN_DEBUG_H_ */
