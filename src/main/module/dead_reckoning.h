
#ifndef MAIN_MODULE_DEAD_RECKONING_H_
#define MAIN_MODULE_DEAD_RECKONING_H_

#define Rad2Deg 57.29578F

void initializeDeadReckoning();
void setBasePosition();
void getLocations(float* posX, float* posY, float* dir);
void returnBase();
void deadReckoningFeed();

#endif /* MAIN_MODULE_DEAD_RECKONING_H_ */
