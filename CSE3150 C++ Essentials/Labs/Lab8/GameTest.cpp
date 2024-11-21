#include <string>

#include "Character.hpp"
#include "Weapons.hpp"


int main() {
    Sword warriorSword("Legendary Sword", 25);
    Staff wizardStaff("Enchanted Staff", 30);

    Warrior warrior("Aragorn", 100, warriorSword, 20);
    Wizard wizard("Gandalf", 80, wizardStaff, 30);

    // Display information, equip weapons, and perform attacks
    warrior.displayInfo();
    warrior.attack(wizard);

    std::cout << std::endl;

    wizard.displayInfo();
    wizard.specialAttack(warrior);  

    std::cout << std::endl;
    
    // Create an object of a new weapon and change the warrior object using equipweapon. Change weapons and attack again
    Sword newSword("My wood Sword", 40);
    std::cout << "Equipping warrior with a new weapon." << std::endl;
    warrior.equipWeapon(newSword);
    warrior.attack(wizard);

    return 0;
}