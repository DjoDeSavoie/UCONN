#include "robot.h"
#include "command.h"
#include <iostream>

// Main function to demonstrate the solution
int main() {
    std::cout <<"PRgoram starty";
    Robot robot(0, 0, 2, 2);
    MoveForwardCommand moveForward;
    MoveBackwardCommand moveBackward;
    MoveRightCommand moveRight;
    MoveLeftCommand moveLeft; 
    ChargeCommand charge;

    std::cout << "starting robot moves" << std::endl;
    robot.executeCommand(moveForward); 
    robot.executeCommand(moveForward);
    robot.executeCommand(moveRight); 
    robot.executeCommand(moveRight); 
    robot.executeCommand(moveForward);
    robot.executeCommand(charge); 
    robot.displayPosition();

    return 0;
}
