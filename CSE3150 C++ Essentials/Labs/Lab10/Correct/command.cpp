#include "command.h"
#include "robot.h"

void ChargeCommand::execute(Robot& robot) { 
    std::cout << "Charging battery.\n"; 
    robot.setBatteryLevel(100);  // Battery fully charged
}

void MoveForwardCommand::execute(Robot& robot){
    robot.move(0,1);
}
void MoveBackwardCommand::execute(Robot& robot){
    robot.move(0,-1);
}
void MoveRightCommand::execute(Robot& robot){
    robot.move(1,0);    
}
void MoveLeftCommand::execute(Robot& robot){
    robot.move(-1,0);
}

