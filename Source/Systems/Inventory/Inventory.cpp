#include "Inventory.h"
#include "../../Entities/Player/Player.h"
#include "../../Core/ConsoleUI.h"
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

Item* Inventory::getItem(int index) {
    if (index >= 0 && index < items.size()) {
        return &items[index];
    }
    return nullptr;
}

void Inventory::equipMenu(Player& player) {
    bool browsing = true;
    
    while (browsing) {
        ConsoleUI::clearScreen();
        ConsoleUI::printHeader("=== INVENTORY & EQUIPMENT ===");
        
        // Show current equipment
        cout << "\nCurrent Equipment:\n";
        ConsoleUI::setColor(ConsoleUI::Color::CYAN, ConsoleUI::Color::BLACK);
        player.showEquipment();
        ConsoleUI::setColor(ConsoleUI::Color::WHITE, ConsoleUI::Color::BLACK);
        
        ConsoleUI::printSeparator();
        cout << "\nInventory (" << items.size() << "/" << maxSize << "):\n" << endl;
        
        if (items.empty()) {
            ConsoleUI::printWarning("Your inventory is empty.");
        } else {
            for (int i = 0; i < items.size(); i++) {
                Item& item = items[i];
                
                // Color based on item type
                if (item.getType() == ItemType::WEAPON) {
                    ConsoleUI::setColor(ConsoleUI::Color::RED, ConsoleUI::Color::BLACK);
                } else if (item.getType() == ItemType::ARMOR) {
                    ConsoleUI::setColor(ConsoleUI::Color::BLUE, ConsoleUI::Color::BLACK);
                } else if (item.getType() == ItemType::CONSUMABLE) {
                    ConsoleUI::setColor(ConsoleUI::Color::GREEN, ConsoleUI::Color::BLACK);
                } else {
                    ConsoleUI::setColor(ConsoleUI::Color::YELLOW, ConsoleUI::Color::BLACK);
                }
                
                cout << (i + 1) << ". " << item.getName();
                ConsoleUI::setColor(ConsoleUI::Color::WHITE, ConsoleUI::Color::BLACK);
                cout << " - " << item.getDescription() << endl;
                
                if (item.getIsEquippable()) {
                    cout << "   [";
                    if (item.getStrengthBonus() != 0) cout << (item.getStrengthBonus() > 0 ? "+" : "") << item.getStrengthBonus() << " STR ";
                    if (item.getMagicBonus() != 0) cout << (item.getMagicBonus() > 0 ? "+" : "") << item.getMagicBonus() << " MAG ";
                    if (item.getDefenseBonus() != 0) cout << (item.getDefenseBonus() > 0 ? "+" : "") << item.getDefenseBonus() << " DEF ";
                    if (item.getSpeedBonus() != 0) cout << (item.getSpeedBonus() > 0 ? "+" : "") << item.getSpeedBonus() << " SPD ";
                    cout << "]" << endl;
                    
                    ConsoleUI::setColor(ConsoleUI::Color::CYAN, ConsoleUI::Color::BLACK);
                    cout << "   Class: " << item.getClassRequirement();
                    ConsoleUI::setColor(ConsoleUI::Color::WHITE, ConsoleUI::Color::BLACK);
                    cout << endl;
                }
                cout << endl;
            }
        }
        
        ConsoleUI::printSeparator();
        cout << "\nOptions:" << endl;
        cout << "Enter item number to EQUIP/USE it" << endl;
        cout << "0. Exit to main menu" << endl;
        cout << "\nChoice: ";
        
        int choice;
        cin >> choice;
        
        if (choice == 0) {
            browsing = false;
        } else if (choice > 0 && choice <= items.size()) {
            Item* item = getItem(choice - 1);
            if (item) {
                if (item->getIsEquippable()) {
                    if (player.equipItem(item)) {
                        cout << "\nPress Enter to continue...";
                        cin.ignore();
                        cin.get();
                    } else {
                        cout << "\nPress Enter to continue...";
                        cin.ignore();
                        cin.get();
                    }
                } else if (item->getType() == ItemType::CONSUMABLE) {
                    if (item->getName().find("Health Potion") != string::npos || 
                        item->getName().find("Potion") != string::npos) {
                        int healAmount = 50; // Default heal
                        if (item->getName().find("Minor") != string::npos) healAmount = 30;
                        else if (item->getName().find("Greater") != string::npos) healAmount = 100;
                        else if (item->getName().find("Superior") != string::npos) healAmount = 150;
                        
                        player.heal(healAmount);
                        ConsoleUI::printSuccess("Used " + item->getName() + "! Restored " + to_string(healAmount) + " HP!");
                        cout << "Current HP: " << player.getHP() << "/" << player.getMaxHP() << endl;
                        removeItem(choice - 1);
                        cout << "\nPress Enter to continue...";
                        cin.ignore();
                        cin.get();
                    }
                }
            }
        } else {
            ConsoleUI::printError("Invalid choice!");
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
    }
}
