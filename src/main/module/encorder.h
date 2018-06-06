
#ifndef MAIN_MODULE_ENCORDER_H_
#define MAIN_MODULE_ENCORDER_H_

#include "motor.h"

#define PI  3.141592654f

void initializeEncorder();

void startEncorder();

float getEncorder(Motor motor);

float convertRotate2Meter(float rotate);

void encoderFeed();

#endif /* MAIN_MODULE_ENCORDER_H_ */
