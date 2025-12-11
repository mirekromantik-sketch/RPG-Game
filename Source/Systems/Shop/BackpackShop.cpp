#include "BackpackShop.h"
#include "../../Core/ConsoleUI.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct BackpackUpgrade {
    int slots;
    int price;
    string description;
};

void openBackpackShop(Player& player) {
    vector<BackpackUpgrade> upgrades = {
        {5, 100, "Add 5 slots to your backpack"},
        {10, 250, "Add 10 slots to your backpack"},
        {25, 500, "Add 25 slots to your backpack"},
        {50, 1000, "Add 50 slots to your backpack"},
        {100, 2500, "Add 100 slots to your backpack"},
        {1000, 20000, "Add 1000 slots to your backpack (MEGA UPGRADE!)"}
    };
    
    bool shopping = true;
    while (shopping) {
        ConsoleUI::clearScreen();
        ConsoleUI::printHeader("=== BACKPACK SHOP ===");
        ConsoleUI::setColor(ConsoleUI::Color::YELLOW, ConsoleUI::Color::BLACK);
        cout << "Your Gold: " << player.getGold() << endl;
        ConsoleUI::setColor(ConsoleUI::Color::CYAN, ConsoleUI::Color::BLACK);
        cout << "Current Backpack Size: " << player.getInventory().getSize() 
             << "/" << player.getInventory().getMaxSize() << " slots" << endl;
        ConsoleUI::setColor(ConsoleUI::Color::WHITE, ConsoleUI::Color::BLACK);
        ConsoleUI::printSeparator();
        
        cout << "\n--- Backpack Upgrades ---\n" << endl;
        
        for (size_t i = 0; i < upgrades.size(); i++) {
            ConsoleUI::setColor(ConsoleUI::Color::GREEN, ConsoleUI::Color::BLACK);
            cout << (i + 1) << ". +" << upgrades[i].slots << " Slots - " 
                 << upgrades[i].price << " gold";
            ConsoleUI::setColor(ConsoleUI::Color::WHITE, ConsoleUI::Color::BLACK);
            cout << "\n   " << upgrades[i].description << endl;
            ConsoleUI::setColor(ConsoleUI::Color::MAGENTA, ConsoleUI::Color::BLACK);
            cout << "   New Size: " << player.getInventory().getMaxSize() + upgrades[i].slots 
                 << " slots";
            ConsoleUI::setColor(ConsoleUI::Color::WHITE, ConsoleUI::Color::BLACK);
            cout << "\n" << endl;
        }
        
        cout << (upgrades.size() + 1) << ". Leave Shop" << endl;
        ConsoleUI::printSeparator();
        cout << "Choice: ";
        
        int choice;
        cin >> choice;
        
        if (choice == (int)upgrades.size() + 1) {
            shopping = false;
            ConsoleUI::printInfo("Thanks for visiting!");
        } else if (choice > 0 && choice <= (int)upgrades.size()) {
            BackpackUpgrade& upgrade = upgrades[choice - 1];
            
            if (player.getGold() >= upgrade.price) {
                player.addGold(-upgrade.price);
                player.getInventory().increaseMaxSize(upgrade.slots);
                ConsoleUI::printSuccess("Backpack upgraded! Added " + to_string(upgrade.slots) + " slots!");
                ConsoleUI::setColor(ConsoleUI::Color::CYAN, ConsoleUI::Color::BLACK);
                cout << "New Backpack Size: " << player.getInventory().getMaxSize() << " slots" << endl;
                ConsoleUI::setColor(ConsoleUI::Color::WHITE, ConsoleUI::Color::BLACK);
                cout << "\nPress Enter to continue...";
                cin.ignore();
                cin.get();
            } else {
                ConsoleUI::printError("Not enough gold! You need " + to_string(upgrade.price) + " gold.");
                cout << "\nPress Enter to continue...";
                cin.ignore();
                cin.get();
            }
        } else {
            ConsoleUI::printError("Invalid choice!");
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
    }
}
