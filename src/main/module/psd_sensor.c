
#include "psd_sensor.h"
#include "ad_converter.h"

volatile static float previouslyDistance = 0;// [m]

float getDistance()
{
	float d = (float)getADConvertValue(0);
	d = (-0.00000718824 * d * d * d) + (0.007552017 * d * d) - (2.669235294 * d) + 329.7386555;
	d = d / 100;
	d = 0.8 * d + 0.2 * previouslyDistance;
	previouslyDistance = d;
	return d;
}

