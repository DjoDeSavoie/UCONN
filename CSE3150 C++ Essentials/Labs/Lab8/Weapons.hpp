#pragma once

#include <iostream>
#include <string>

// Base class: Weapon
class Weapon {
public:
    Weapon(const std::string& n, int d) : name(n), damage(d) {}

    // Public interface
    void displayInfo() const {
        std::cout << "Weapon: " << name << ", Damage: " << damage << std::endl;
    }

    int getDamage() const {
        return damage;
    }

    virtual int specialAttack() = 0;    // Pure virtual function that must be overridden by derived classes
    
protected:
    std::string name;
    int damage;
};

// Derived class: Sword
class Sword : public Weapon {
public:
    Sword(const std::string& n, int d) : Weapon(n, d) {}

    int specialAttack() override {
        return damage + 10;
    }
};

// Derived class: Staff
class Staff : public Weapon {
public:
    Staff(const std::string& n, int d) : Weapon(n, d) {}

 // Fill this class with special attack overidden function. Take refrence from overiding of special attack in above class.

    int specialAttack() override {
        // Implement the special attack for Staff (e.g., increase damage)
        std::cout << name << " performs a magical special attack!" << std::endl;
        return damage * 2; // Example multiplier
    }

};