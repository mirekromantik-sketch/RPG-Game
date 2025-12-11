#ifndef INVENTORY_H
#define INVENTORY_H

#include "Item.h"
#include <vector>

class Player;

class Inventory {
private:
    std::vector<Item> items;
    int maxSize;

public:
    Inventory(int maxSize = 20);
    
    bool addItem(const Item& item);
    void removeItem(int index);
    void display() const;
    void useItem(Player& player);
    void equipMenu(Player& player);
    Item* getItem(int index);
    
    int getSize() const { return items.size(); }
    int getMaxSize() const { return maxSize; }
    void increaseMaxSize(int amount) { maxSize += amount; }
    bool isFull() const { return items.size() >= maxSize; }
    const std::vector<Item>& getItems() const { return items; }
};

#endif
