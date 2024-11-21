#ifndef ROBOT_STATE_H
#define ROBOT_STATE_H

#include <iostream>

class Robot;
class Command;

// RobotState interface
class RobotState {
public:
    virtual ~RobotState() = default;
    virtual void handleCommand(Robot& robot, Command& command) = 0;
    virtual void enterState(Robot& robot) = 0;
};

// Implement Concrete State Classes

#endif