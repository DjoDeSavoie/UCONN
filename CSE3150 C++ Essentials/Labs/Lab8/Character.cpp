#include "Character.hpp"

// *****************************************
// Character definitions
// *****************************************
void Character :: displayInfo() const {
    std::cout << "Name: " << name << ", Health: " << health << std::endl;
    weapon.displayInfo();
}

void Character :: equipWeapon(Weapon& w) {
    weapon = w;
}

void Character :: attack(Character& op) const {
    std::cout << name << " attacks with ";
    weapon.displayInfo();
    std::cout << "Damage: " << weapon.getDamage() << std::endl;
    op.getHit(weapon.getDamage());
}

// void Character :: specialAttack(Character& op) const {
//     std::cout << name << " attacks with ";
//     weapon.displayInfo();
//     std::cout << "Damage: " << weapon.getDamage() << std::endl;
//     op.getHit(weapon.specialAttack());
// }

void Character :: getHit(int damage) {
    health -= damage;
    std::cout << name << " takes " << damage << " damage. Remaining health: " << health << std::endl;
}

// *****************************************
// Warrior definitions
// *****************************************
void Warrior :: attack(Character& op) const {
    int damage = weapon.getDamage() + strength;
    std::cout << "Warrior " << name << " swings his sword! Damage: " << damage << std::endl;
    op.getHit(damage);
}

void Warrior :: specialAttack(Character& op) const {
    int damage = weapon.specialAttack() + strength;
    std::cout << "Warrior " << name << " swings his sword with a special attack! Damage: " << damage << std::endl;
    op.getHit(damage);
}

void Warrior :: getHit(int damage) {
    if (strength > damage) {
        std::cout << "Warrior " << name << " blocks the attack!" << std::endl;
        return;
    }
    health -= damage;
    std::cout << "Warrior " << name << " takes " << damage << " damage. Remaining health: " << health << std::endl;
}

// *****************************************
// Wizard definitions - Fill these defintions for Wizard Derived Class. Take Refrence from Warrior Class
// *****************************************


void Wizard::attack(Character& op) const {
    int damage = weapon.getDamage() + magicPower;
    std::cout << "Wizard " << name << " casts a spell! Damage: " << damage << std::endl;
    op.getHit(damage);
}

void Character::specialAttack(Character& op) const {
    // Default special attack (optional)
    std::cout << name << " performs a basic special attack!" << std::endl;
    op.getHit(weapon.getDamage() * 1.5); // example multiplier
}

void Wizard::getHit(int damage) {
    if (damage < magicPower / 2) {
        std::cout << "Wizard " << name << " magically reduces the attack damage!" << std::endl;
        return;
    }
    health -= damage;
    std::cout << "Wizard " << name << " takes " << damage << " damage. Remaining health: " << health << std::endl;
}

void Wizard::healingSpell() {
    int healing = 20; // Example healing amount
    health += healing;
    std::cout << "Wizard " << name << " casts a healing spell! Health is now " << health << std::endl;
}
