
#ifndef MAIN_MODULE_TRAJECTORY_TRACKING_CONTROL_H_
#define MAIN_MODULE_TRAJECTORY_TRACKING_CONTROL_H_

#define Deg2Rad 0.0174533F

#define P_GAIN 7000.0F
#define I_GAIN 10.0F
#define D_GAIN 10.0F

void trackingFeed();
void initializeTrajectoryTracking();
void trajectoryTracking(float length, float angle, float time);
void waitForTracking();
bool isTracking();
static void makeTrajectory(float length, float angle, float time);
static void makeCompositeTrajectory();

#endif /* MAIN_MODULE_TRAJECTORY_TRACKING_CONTROL_H_ */
