#include "Item.h"
#include <cstdlib>

using namespace std;

Item::Item() : name("Empty"), description(""), type(ItemType::CONSUMABLE), value(0),
               strengthBonus(0), magicBonus(0), defenseBonus(0), speedBonus(0),
               requiredClass(EquipmentClass::ALL), isEquippable(false) {}

Item::Item(string name, string description, ItemType type, int value,
           int strBonus, int magBonus, int defBonus, int spdBonus,
           EquipmentClass reqClass)
    : name(name), description(description), type(type), value(value),
      strengthBonus(strBonus), magicBonus(magBonus), defenseBonus(defBonus), 
      speedBonus(spdBonus), requiredClass(reqClass),
      isEquippable(type == ItemType::WEAPON || type == ItemType::ARMOR) {}

string Item::getClassRequirement() const {
    switch (requiredClass) {
        case EquipmentClass::WARRIOR: return "Warrior";
        case EquipmentClass::MAGE: return "Mage";
        case EquipmentClass::ROGUE: return "Rogue";
        case EquipmentClass::CLERIC: return "Cleric";
        case EquipmentClass::RANGER: return "Ranger";
        case EquipmentClass::ALL: return "All Classes";
        default: return "Unknown";
    }
}

Item Item::generateRandomItem() {
    int roll = rand() % 100;
    
    if (roll < 50) {
        return Item("Health Potion", "Restores 50 HP", ItemType::CONSUMABLE, 50);
    } else if (roll < 70) {
        return Item("Mana Potion", "Restores 30 MP", ItemType::CONSUMABLE, 30);
    } else if (roll < 85) {
        int damage = 10 + (rand() % 15);
        return Item("Sword", "A solid weapon +" + to_string(damage) + " ATK", ItemType::WEAPON, damage);
    } else {
        int defense = 5 + (rand() % 10);
        return Item("Armor", "Protective gear +" + to_string(defense) + " DEF", ItemType::ARMOR, defense);
    }
}
