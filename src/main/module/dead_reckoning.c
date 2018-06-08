
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

void initializeDeadReckoning()
{
	width= 0.256;// [m]
}

void setBasePosition()
{
	positionX = 0;
	positionY = 0;
	direction = 0;

	previouslyLeftPosition = convertRotate2Meter(getEncorder(LeftMotor));
	previouslyRightPosition = convertRotate2Meter(getEncorder(RightMotor));
}

void getLocations(float* posX, float* posY, float* dir)
{
	*posX = positionX;
	*posY = positionY;
	*dir = direction;
}

void returnBase()
{
	float px = positionX;
	float py = positionY;
	float d = direction;

	float rad = atan2f(py, px);
	if (errno == EDOM)
		rad = 0;

	trajectoryTracking(0.0F, (0.0F - d + rad) * Rad2Deg, 3.0F);
	waitForTracking();

	float len = sqrt(px * px + py * py);
	trajectoryTracking(0.0F - len, 0.0F, 3.0F);
	waitForTracking();

	trajectoryTracking(0.0F, (0.0F - rad) * Rad2Deg, 3.0F);
	waitForTracking();
}

void deadReckoningFeed()
{
	// 微小移動距離
	float l = convertRotate2Meter(getEncorder(LeftMotor));
	float r = convertRotate2Meter(getEncorder(RightMotor));
	float ld = l - previouslyLeftPosition;
	float rd = r - previouslyRightPosition;
	float d = (ld + rd) / 2;
	// 微小回転角
	float a = ((rd - ld) / 2) / (width / 2);

	// 現在位置更新
	positionX += d * cosf(direction + a / 2);
	positionY += d * sinf(direction + a / 2);
	direction += a;

	previouslyLeftPosition = l;
	previouslyRightPosition = r;
}
