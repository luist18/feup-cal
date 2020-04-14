#include "animation_util.h"

template<typename T>
int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

void animate(GraphViewer *gv, int sleep_time) {
    // Removing old nodes and edges
    gv->removeNode(LEFT_ARM_ID);
    gv->removeNode(RIGHT_ARM_ID);
    gv->removeEdge(LEFT_ARM_EDGE_ID);
    gv->removeEdge(RIGHT_ARM_EDGE_ID);

    float angle = 0.0f;
    int left_direction = 1;
    int index = 0;

    while (1) {
        clear(gv, index);
        computeLocations(gv, angle, index);
        gv->rearrange();
        //computeAngle(angle, left_direction);
        _sleep(sleep_time*100);
    }
}

void clear(GraphViewer *gv, int &index) {
    if (index == 0) return;

    gv->removeNode(STARTING_INDEX + index - 1);
    gv->removeNode(STARTING_INDEX + index);
    gv->removeEdge(STARTING_INDEX + index - 1);
    gv->removeEdge(STARTING_INDEX + index);
}

void computeLocations(GraphViewer *gv, float &angle, int &index) {
    // Computing location for the left and right arm
    int left_arm_x = CHEST_X - ARM_DISTANCE * cos(angle);
    int left_arm_y = CHEST_Y - ARM_DISTANCE * sin(angle);

    cout << left_arm_x << endl;
    int right_arm_x = CHEST_X + ARM_DISTANCE * cos(angle);
    int right_arm_y = CHEST_Y + ARM_DISTANCE * sin(angle);

    // Adding the new ones
    gv->addNode(STARTING_INDEX + index, left_arm_x, left_arm_y);
    //gv->addNode(STARTING_INDEX + 1 + index, right_arm_x, right_arm_y);
    //gv->addEdge(STARTING_INDEX + index, CHEST_ID, LEFT_ARM_ID, EdgeType::UNDIRECTED);
    //gv->addEdge(STARTING_INDEX + 1 + index, CHEST_ID, RIGHT_ARM_ID, EdgeType::UNDIRECTED);

    ++index;
}

void computeAngle(float &angle, int &direction) {
    angle += ANGLE_INCREMENT * direction;

    if (abs(angle) > M_PI_4) {
        angle = M_PI_4 * sgn(angle);
        direction *= -1;
    }
}
