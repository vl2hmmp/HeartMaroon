
#include <math.h>
#include "../../HeartMaroon.h"
#include "../module/debug.h"
#include "../module/psd_sensor.h"
#include "../module/dead_reckoning.h"
#include "../module/trajectory_tracking_control.h"

volatile static float baseDirection;// [rad]

void setSearchingBase()
{
	float px, py, d;
	getLocations(&px, &py, &d);
	baseDirection = d;
}

bool searchBall(float* direction, float* distance)
{
	float minDistance = 0.46F;
	float minDirection = 0;

	setLedState(OutLed, None);

	trajectoryTracking(0.0F, 45.0F, 3.0F);
	while(isTracking()){
		float dst = getDistance();
		if (dst < minDistance){
			setLedState(OutLed, Lighting);
			float px, py, d;
			getLocations(&px, &py, &d);
			minDistance = dst;
			minDirection = d;
		}
	}

	setLedState(OutLed, None);

	trajectoryTracking(0.0F, -90.0F, 6.0F);
	while(isTracking()){
		float dst = getDistance();
		if (dst < minDistance){
			setLedState(OutLed, Lighting);
			float px, py, d;
			getLocations(&px, &py, &d);
			minDistance = dst;
			minDirection = d;
		}
	}

	trajectoryTracking(0.0F, 45.0F, 3.0F);
	waitForTracking();

	*direction = minDirection - baseDirection;
	*distance = minDistance;
	return minDistance < 0.36F;
}
