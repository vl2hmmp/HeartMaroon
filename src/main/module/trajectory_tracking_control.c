
#include "../../HeartMaroon.h"
#include "encorder.h"
#include "motor.h"
#include "trajectory_tracking_control.h"

volatile static float samplingTime;// [s]
volatile static float width;// [m]

volatile static int maxTime;
volatile static int nowTime;

volatile static float linearTrajectory[1024];// [m]
volatile static float curveTrajectory[1024];// [m]
volatile static float leftTrajectory[1024];// [m]
volatile static float rightTrajectory[1024];// [m]

volatile static float leftInitialPosition;// [m]
volatile static float rightInitialPosition;// [m]
volatile static float leftAccumulatedError;// [m]
volatile static float rightAccumulatedError;// [m]

void trackingFeed() {
	if (maxTime <= nowTime)
		return;

	float leftPosition = convertRotate2Meter(getEncorder(LeftMotor)) - leftInitialPosition;
	float rightPosition = convertRotate2Meter(getEncorder(RightMotor)) - rightInitialPosition;
	leftAccumulatedError += leftTrajectory[nowTime] - leftPosition;
	rightAccumulatedError += rightTrajectory[nowTime] - rightPosition;
	float leftVerocity = leftTrajectory[nowTime + 1] - leftTrajectory[nowTime];
	float rightVerocity = rightTrajectory[nowTime + 1] - rightTrajectory[nowTime];

	int leftThrottle = P_GAIN * (leftTrajectory[nowTime] - leftPosition) + I_GAIN * leftAccumulatedError + D_GAIN * leftVerocity;
	int rightThrottle = P_GAIN * (rightTrajectory[nowTime] - rightPosition) + I_GAIN * rightAccumulatedError + D_GAIN * rightVerocity;

	setMotorThrottle(LeftMotor, leftThrottle);
	setMotorThrottle(RightMotor, rightThrottle);

	nowTime++;
	if (maxTime == nowTime){
		setMotorThrottle(LeftMotor, 0);
		setMotorThrottle(RightMotor, 0);
	}
}

void initializeTrajectoryTracking() {
	samplingTime = 0.01F;// [s]
	width= 0.256;// [m]
}

void trajectoryTracking(float length, float angle, float time) {
	// 軌道生成
	maxTime = (int)(time / samplingTime);
	makeTrajectory(length, angle, time);
	makeCompositeTrajectory();

	// 現在位置を初期位置としてセット
	leftInitialPosition = convertRotate2Meter(getEncorder(LeftMotor));
	rightInitialPosition = convertRotate2Meter(getEncorder(RightMotor));
	leftAccumulatedError = 0;
	rightAccumulatedError = 0;
	nowTime = 0;
}

void waitForTracking()
{
	while(isTracking());
}

bool isTracking()
{
	return nowTime < maxTime;
}

static void makeTrajectory(float length, float angle, float time)
{
	// 係数の値については実験テーマ7を参照
	float a2 = 3.0f * length / (time * time);
	float a3 = -2.0f * length / (time * time * time);

	// 直進軌道の生成
	for (int i = 0; i <= maxTime; i++) {
		float t = i * samplingTime;
		linearTrajectory[i] = a2 * t * t + a3 * t * t * t;
	}

	a2 = 3.0f * angle / (time * time);
	a3 = -2.0f * angle / (time * time * time);

	// 定置旋回軌道の生成
	for (int i = 0; i <= maxTime; i++) {
		float t = i * samplingTime;
		curveTrajectory[i] = a2 * t * t + a3 * t * t * t;
	}
}

static void makeCompositeTrajectory()
{
	// 直進軌道と定置旋回軌道の合成
	for (int i = 0; i <= maxTime; i++) {
		leftTrajectory[i] = (linearTrajectory[i] - (width / 2) * curveTrajectory[i] * Deg2Rad);
		rightTrajectory[i] = (linearTrajectory[i] + (width / 2) * curveTrajectory[i] * Deg2Rad);
	}
}
