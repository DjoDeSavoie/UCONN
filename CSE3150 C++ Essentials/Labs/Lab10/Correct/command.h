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

// Concrete Command Classes
class MoveForwardCommand : public Command {
public:
    void execute(Robot& robot) override;
};

class MoveBackwardCommand : public Command {
public:
    void execute(Robot& robot) override;
};

class MoveRightCommand : public Command {
public:
    void execute(Robot& robot) override;
};

class MoveLeftCommand : public Command {
public:
    void execute(Robot& robot) override;
};

class ChargeCommand : public Command {
public:
    void execute(Robot& robot) override;
};

#endif 