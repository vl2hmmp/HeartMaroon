
#include <math.h>
#include "encorder.h"
#include "motor.h"
#include "dead_reckoning.h"
#include "trajectory_tracking_control.h"

volatile static float width;// [m]

volatile static float positionX;// [m]
volatile static float positionY;// [m]
volatile static float direction;// [rad]

volatile static float previouslyLeftPosition;// [m]
volatile static float previouslyRightPosition;// [m]

void initializeDeadReckoning() {
	width= 0.263;// [m]
}

void setBasePosition()
{
	positionX = 0;
	positionY = 0;
	direction = 0;

	previouslyLeftPosition = convertRotate2Meter(getEncorder(LeftMotor));
	previouslyRightPosition = convertRotate2Meter(getEncorder(RightMotor));
}

void deadReckoningFeed()
{
	// 微小移動距離
	float ld = convertRotate2Meter(getEncorder(LeftMotor)) - previouslyLeftPosition;
	float rd = convertRotate2Meter(getEncorder(RightMotor)) - previouslyRightPosition;
	float d = (ld + rd) / 2;
	// 微小回転角
	float a = ((ld - rd) / 2) / (width / 2);

	// 現在位置更新
	positionX += d * cosf(direction + a / 2);
	positionY += d * sinf(direction + a / 2);
	direction += a;
}
