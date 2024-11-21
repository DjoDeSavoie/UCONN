#ifndef ROBOT_H
#define ROBOT_H

#include <memory>
#include "robotState.h"

class Command;

class Robot {
public:
    Robot(int startX, int startY, int exitX, int exitY);
    void changeState(std::unique_ptr<RobotState> newState);
    void executeCommand(Command& command);
    void setBatteryLevel(int level);
    int getBatteryLevel() const;
    void exploreMaze();
    void goBackToStart();
    bool hasFoundExit() const;
    void setFoundExit(bool found);
    void move(int x, int y);
    void displayPosition();
    void wait();


private:
    std::unique_ptr<RobotState> state;
    int batteryLevel;
    int pos_x, pos_y;
    int exit_x, exit_y;
    bool foundExit;
};

#endif