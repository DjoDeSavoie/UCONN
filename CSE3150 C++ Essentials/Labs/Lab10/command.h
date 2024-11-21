#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>

class Robot;

// Command interface
class Command {
public:
    virtual ~Command() = default;
    virtual void execute(Robot& robot) = 0;
};

//TODO add concrete class definitions here

#endif 