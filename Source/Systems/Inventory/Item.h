#ifndef ITEM_H
#define ITEM_H

#include <string>

enum class ItemType {
    WEAPON,
    ARMOR,
    CONSUMABLE,
    QUEST
};

enum class EquipmentClass {
    ALL,
    WARRIOR,
    MAGE,
    ROGUE,
    CLERIC,
    RANGER
};

class Item {
private:
    std::string name;
    std::string description;
    ItemType type;
    int value;
    
    // Equipment stats
    int strengthBonus;
    int magicBonus;
    int defenseBonus;
    int speedBonus;
    EquipmentClass requiredClass;
    bool isEquippable;

public:
    Item();
    Item(std::string name, std::string description, ItemType type, int value,
         int strBonus = 0, int magBonus = 0, int defBonus = 0, int spdBonus = 0,
         EquipmentClass reqClass = EquipmentClass::ALL);
    
    static Item generateRandomItem();
    
    std::string getName() const { return name; }
    std::string getDescription() const { return description; }
    ItemType getType() const { return type; }
    int getValue() const { return value; }
    
    int getStrengthBonus() const { return strengthBonus; }
    int getMagicBonus() const { return magicBonus; }
    int getDefenseBonus() const { return defenseBonus; }
    int getSpeedBonus() const { return speedBonus; }
    EquipmentClass getRequiredClass() const { return requiredClass; }
    bool getIsEquippable() const { return isEquippable; }
    
    std::string getClassRequirement() const;
};

#endif
