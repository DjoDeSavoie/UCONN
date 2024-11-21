#include "robotState.h"
#include "robot.h"
#include "command.h"
#include <iostream>

// State-specific command handling
void IdleState::handleCommand(Robot& robot, Command& command) {
    command.execute(robot);
    robot.changeState(std::make_unique<ExploringState>());
}

void ExploringState::handleCommand(Robot& robot, Command& command) {
    command.execute(robot);
    if (robot.hasFoundExit()) {
        std::cout << "found exit at:\n";
        robot.displayPosition();
        robot.changeState(std::make_unique<ReturningState>());
    }
}

void ReturningState::handleCommand(Robot& robot, Command& command) {
    command.execute(robot);
    robot.goBackToStart();
}

void ChargingState::handleCommand(Robot& robot, Command& command) {
    if (dynamic_cast<ChargeCommand*>(&command)) {
        command.execute(robot);
        robot.changeState(std::make_unique<IdleState>());
    } else {
        std::cout << "Robot can't execute this command while charging.\n";
    }
}