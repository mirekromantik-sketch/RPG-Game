#include "Item.h"
#include <cstdlib>

using namespace std;

Item::Item() : name("Empty"), description(""), type(ItemType::CONSUMABLE), value(0) {}

Item::Item(string name, string description, ItemType type, int value)
    : name(name), description(description), type(type), value(value) {}

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
