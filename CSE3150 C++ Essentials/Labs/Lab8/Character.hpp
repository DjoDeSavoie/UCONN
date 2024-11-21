#pragma once

#include <iostream>
#include <string>

#include "Weapons.hpp"

// Base class: Character
class Character {
public:
    Character(const std::string& n, int h, Weapon& w) : name(n), health(h), weapon(w) {}

    void displayInfo() const;
    void equipWeapon(Weapon& w);
    virtual void attack(Character& op) const;
    virtual void specialAttack(Character& op) const;  // Make sure this is not pure virtual
    virtual void getHit(int damage);

protected:
    std::string name;
    int health;
    Weapon& weapon;
};

// Derived class: Warrior
class Warrior : public Character {
public:
    Warrior(const std::string& n, int h, Weapon& w, int s) : Character(n, h, w), strength(s) {}

    // Override base class function
    void attack(Character& op) const override;
    void specialAttack(Character& op) const override;
    void getHit(int damage) override;

    void setStrength(int s) { strength = s; }

private:
    int strength;
};

// Derived class: Wizard
class Wizard : public Character {
public:
    Wizard(const std::string& n, int h, Weapon& w, int mp) : Character(n, h, w), magicPower(mp) {}

    // Fill this out for Wizard. Take refrence from above Warrior class.
    void attack(Character& op)const;
    // void specialAttack(Character& op) const override;
    void getHit(int damage);
    void healingSpell();

private:
    int magicPower;
};