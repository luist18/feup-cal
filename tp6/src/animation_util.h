#ifndef FICHAJUNG_ANIMATION_UTIL_H
#define FICHAJUNG_ANIMATION_UTIL_H

#define _USE_MATH_DEFINES

#include <cmath>
#include <graphviewer.h>

#define CHEST_X 300
#define CHEST_Y 200
#define WAIST_X 300
#define WAIST_Y 400
#define ARM_DISTANCE 150
#define LEG_DISTANCE 150
#define LEG_INITIAL_ANGLE -0.84
#define ANGLE_DIVS 15
#define ANGLE_INCREMENT M_PI_4/ANGLE_DIVS
#define CHEST_ID 9
#define LEFT_ARM_ID 8
#define RIGHT_ARM_ID 10
#define LEFT_ARM_EDGE_ID 9
#define RIGHT_ARM_EDGE_ID 10
#define WAIST_ID 11
#define LEFT_LEG_ID 12
#define RIGHT_LEG_ID 13
#define LEFT_LEG_EDGE_ID 12
#define RIGHT_LEG_EDGE_ID 13
#define STARTING_INDEX 14
#define NUMBER_OF_MOVING_NODES 5

void animate(GraphViewer *gv, int sleep_time);

void clear(GraphViewer *gv, int &index);

void computeLocations(GraphViewer *gv, float &angle, int &index);

void computeAngle(float &angle, int &direction);

#endif //FICHAJUNG_ANIMATION_UTIL_H
