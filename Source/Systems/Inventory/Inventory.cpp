#include "Inventory.h"
#include "../../Entities/Player/Player.h"
#include <iostream>

using namespace std;

Inventory::Inventory(int maxSize) : maxSize(maxSize) {}

bool Inventory::addItem(const Item& item) {
    if (isFull()) {
        cout << "Your inventory is full!" << endl;
        return false;
    }
    items.push_back(item);
    return true;
}

void Inventory::removeItem(int index) {
    if (index >= 0 && index < items.size()) {
        items.erase(items.begin() + index);
    }
}

void Inventory::display() const {
    cout << "\n=== Inventory (" << items.size() << "/" << maxSize << ") ===" << endl;
    
    if (items.empty()) {
        cout << "Your inventory is empty." << endl;
        return;
    }
    
    for (int i = 0; i < items.size(); i++) {
        cout << i + 1 << ". " << items[i].getName() 
             << " - " << items[i].getDescription() << endl;
    }
}

void Inventory::useItem(Player& player) {
    display();
    
    if (items.empty()) return;
    
    cout << "\nEnter the number of the item you want to use (0 to cancel): ";
    int choice;
    cin >> choice;
    
    if (choice < 1 || choice > items.size()) {
        cout << "Invalid choice." << endl;
        return;
    }
    
    Item& item = items[choice - 1];
    
    if (item.getType() == ItemType::CONSUMABLE) {
        if (item.getName() == "Health Potion") {
            int healAmount = item.getValue();
            player.heal(healAmount);
            cout << "Used " << item.getName() << "! Restored " << healAmount << " HP!" << endl;
            cout << "Current HP: " << player.getHP() << "/" << player.getMaxHP() << endl;
        }
        removeItem(choice - 1);
    } else {
        cout << "Cannot use this item in combat." << endl;
    }
}
