#ifndef ITEM_H
#define ITEM_H

#include <string>

enum class ItemType {
    WEAPON,
    ARMOR,
    CONSUMABLE,
    QUEST
};

class Item {
private:
    std::string name;
    std::string description;
    ItemType type;
    int value;

public:
    Item();
    Item(std::string name, std::string description, ItemType type, int value);
    
    static Item generateRandomItem();
    
    std::string getName() const { return name; }
    std::string getDescription() const { return description; }
    ItemType getType() const { return type; }
    int getValue() const { return value; }
};

#endif
