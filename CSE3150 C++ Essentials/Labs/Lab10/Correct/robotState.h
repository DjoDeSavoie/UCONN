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

// Concrete State Classes
class IdleState : public RobotState {
public:
    void handleCommand(Robot& robot, Command& command) override;
    void enterState(Robot& robot) override {std::cout << "Robot is now Idle.\n"; }
};

class ExploringState : public RobotState {
public:
    void handleCommand(Robot& robot, Command& command) override;
    void enterState(Robot& robot) override { std::cout << "Robot is now Exploring.\n"; }
};

class ReturningState : public RobotState {
public:
    void handleCommand(Robot& robot, Command& command) override;
    void enterState(Robot& robot) override { std::cout << "Robot is now Returning.\n"; }
};

class ChargingState : public RobotState {
public:
    void handleCommand(Robot& robot, Command& command) override;
    void enterState(Robot& robot) override { std::cout << "Robot is now Charging.\n"; }
};
#endif