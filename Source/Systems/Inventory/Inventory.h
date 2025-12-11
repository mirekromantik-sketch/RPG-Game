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
    
    int getSize() const { return items.size(); }
    bool isFull() const { return items.size() >= maxSize; }
};

#endif
