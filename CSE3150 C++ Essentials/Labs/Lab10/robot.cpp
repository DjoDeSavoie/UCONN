#include <iostream>
#include <memory> 
#include <chrono>
#include <thread>
#include "robot.h"
#include "robotState.h"

// Implementations of Robot's methods
Robot::Robot(int startX, int startY, int exitX, int exitY) : batteryLevel(100), foundExit(false), pos_x(startX), pos_y(startY), exit_x(exitX), exit_y(exitY), state(std::make_unique<IdleState>()) {
    state->enterState(*this);
}

void Robot::changeState(std::unique_ptr<RobotState> newState) {
    state = std::move(newState);
    state->enterState(*this);
}

void Robot::executeCommand(Command& command) {
    state->handleCommand(*this, command);
}

void Robot::setBatteryLevel(int level) {
    batteryLevel = level;
    if (batteryLevel < 20) {
        changeState(std::make_unique<ChargingState>());
    }
}

int Robot::getBatteryLevel() const {
    return batteryLevel;
}

void Robot::exploreMaze() {
    std::cout << "Robot is exploring the maze.\n";
    if (foundExit) {
        changeState(std::make_unique<ReturningState>());
    }
}

void Robot::goBackToStart() {
    std::cout << "Robot is returning to the start.\n";
    this->pos_x = 0;
    this->pos_y = 0;
    changeState(std::make_unique<IdleState>());
}

bool Robot::hasFoundExit() const {
    return foundExit;
}

void Robot::setFoundExit(bool found) {
    foundExit = found;
}

void Robot::displayPosition() {
    std::cout << "x position: " << this->pos_x << std::endl;
    std::cout << "y position: " << this->pos_y << std::endl;
}

void Robot::move(int x, int y) {
    this->pos_x = this->pos_x + x;
    this->pos_y = this->pos_y + y;

    this->batteryLevel -= 10;
}

void Robot::wait(){
     std::this_thread::sleep_for(std::chrono::seconds(5));
}