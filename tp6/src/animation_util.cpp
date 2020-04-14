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

    gv->removeNode(WAIST_ID);

    gv->removeNode(LEFT_LEG_ID);
    gv->removeNode(RIGHT_LEG_ID);
    gv->removeEdge(LEFT_LEG_EDGE_ID);
    gv->removeEdge(RIGHT_LEG_EDGE_ID);

    float angle = 0.0f;
    int left_direction = 1;
    int index = 0;

    while (1) {
        clear(gv, index);
        computeLocations(gv, angle, index);
        gv->rearrange();
        computeAngle(angle, left_direction);
        _sleep(sleep_time);
    }
}

void clear(GraphViewer *gv, int &index) {
    if (index == 0) return;

    int current_index = STARTING_INDEX + (index - 1) * NUMBER_OF_MOVING_NODES;

    gv->removeNode(current_index);
    gv->removeEdge(current_index);
    gv->removeNode(current_index + 1);
    gv->removeEdge(current_index + 1);
    gv->removeNode(current_index + 2);
    gv->removeEdge(current_index + 2);
    gv->removeNode(current_index + 3);
    gv->removeEdge(current_index + 3);
    gv->removeNode(current_index + 4);
    gv->removeEdge(current_index + 4);
}

void computeLocations(GraphViewer *gv, float &angle, int &index) {
    int current_index = STARTING_INDEX + (index * NUMBER_OF_MOVING_NODES);

    // Computing location for the left and right arm
    int left_arm_x = CHEST_X - ARM_DISTANCE * cos(angle);
    int left_arm_y = CHEST_Y + ARM_DISTANCE * sin(angle);

    int right_arm_x = CHEST_X + ARM_DISTANCE * cos(angle);
    int right_arm_y = CHEST_Y - ARM_DISTANCE * sin(angle);

    // Adding the new ones
    gv->addNode(current_index, left_arm_x, left_arm_y);
    gv->addEdge(current_index, current_index, CHEST_ID, EdgeType::UNDIRECTED);
    gv->addNode(current_index + 1, right_arm_x, right_arm_y);
    gv->addEdge(current_index + 1, current_index + 1, CHEST_ID, EdgeType::UNDIRECTED);

    // Computing location for the waist
    int waist_y = WAIST_Y + sin(-angle) * 30;
    gv->addNode(current_index + 2, CHEST_X, waist_y);
    gv->addEdge(current_index + 2, current_index + 2, CHEST_ID, EdgeType::UNDIRECTED);

    // Computing location for the left and right leg
    double leg_angle = LEG_INITIAL_ANGLE + angle / 2;

    int left_leg_x = WAIST_X - LEG_DISTANCE * cos(leg_angle);
    int left_leg_y = WAIST_Y - LEG_DISTANCE * sin(leg_angle);

    int right_leg_x = WAIST_X + LEG_DISTANCE * cos(leg_angle);
    int right_leg_y = WAIST_Y - LEG_DISTANCE * sin(leg_angle);

    gv->addNode(current_index + 3, left_leg_x, left_leg_y);
    gv->addEdge(current_index + 3, current_index + 3, current_index + 2, EdgeType::UNDIRECTED);
    gv->addNode(current_index + 4, right_leg_x, right_leg_y);
    gv->addEdge(current_index + 4, current_index + 4, current_index + 2, EdgeType::UNDIRECTED);

    ++index;
}

void computeAngle(float &angle, int &direction) {
    angle += ANGLE_INCREMENT * direction;

    if (abs(angle) > M_PI_4) {
        angle = M_PI_4 * sgn(angle);
        direction *= -1;
    }
}
