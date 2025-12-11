#include "Town.h"
#include "../../Core/ConsoleUI.h"
#include "../../Entities/Player/Player.h"
#include "../Shop/WeaponShop.h"
#include "../Shop/ArmorShop.h"
#include "../Shop/PotionShop.h"
#include "../Shop/BackpackShop.h"
#include <iostream>

using namespace std;

Town::Town(string name, string description, TownType type)
    : name(name), description(description), type(type), 
      hasWeaponShop(true), hasArmorShop(true), hasPotionShop(true), hasBackpackShop(true),
      hasInn(true), innCost(50) {}

Town::~Town() {
    for (NPC* npc : npcs) {
        delete npc;
    }
}

void Town::addNPC(NPC* npc) {
    npcs.push_back(npc);
}

void Town::visit(Player& player) {
    ConsoleUI::clearScreen();
    ConsoleUI::printHeader("=== " + name + " ===");
    
    ConsoleUI::setColor(ConsoleUI::Color::CYAN, ConsoleUI::Color::BLACK);
    cout << "\n" << description << endl;
    ConsoleUI::setColor(ConsoleUI::Color::WHITE, ConsoleUI::Color::BLACK);
    
    showTownMenu(player);
}

void Town::showTownMenu(Player& player) {
    bool inTown = true;
    
    while (inTown) {
        ConsoleUI::printSeparator();
        cout << "\nWhat would you like to do in " << name << "?" << endl;
        
        int option = 1;
        
        if (hasWeaponShop) {
            cout << option++ << ". Visit Weapon Shop" << endl;
        }
        if (hasArmorShop) {
            cout << option++ << ". Visit Armor Shop" << endl;
        }
        if (hasPotionShop) {
            cout << option++ << ". Visit Potion Shop" << endl;
        }
        if (hasBackpackShop) {
            cout << option++ << ". Visit Backpack Shop" << endl;
        }
        if (hasInn) {
            cout << option++ << ". Rest at Inn (" << innCost << " gold)" << endl;
        }
        if (!npcs.empty()) {
            cout << option++ << ". Talk to NPCs" << endl;
        }
        cout << "0. Leave Town" << endl;
        
        cout << "\nChoice: ";
        int choice;
        cin >> choice;
        
        if (choice == 0) {
            ConsoleUI::printInfo("You leave " + name + ".");
            inTown = false;
        } else {
            int currentOption = 1;
            
            if (hasWeaponShop && choice == currentOption++) {
                openWeaponShop(player);
            } else if (hasArmorShop && choice == currentOption++) {
                openArmorShop(player);
            } else if (hasPotionShop && choice == currentOption++) {
                openPotionShop(player);
            } else if (hasBackpackShop && choice == currentOption++) {
                openBackpackShop(player);
            } else if (hasInn && choice == currentOption++) {
                restAtInn(player);
            } else if (!npcs.empty() && choice == currentOption++) {
                talkToNPCs();
            } else {
                ConsoleUI::printError("Invalid choice!");
                cout << "\nPress Enter to continue...";
                cin.ignore();
                cin.get();
            }
        }
    }
}

void Town::talkToNPCs() {
    ConsoleUI::clearScreen();
    ConsoleUI::printHeader("=== NPCs in " + name + " ===");
    
    cout << "\nWho would you like to talk to?" << endl;
    
    for (size_t i = 0; i < npcs.size(); i++) {
        cout << (i + 1) << ". " << npcs[i]->getName();
        if (npcs[i]->getHasQuest()) {
            ConsoleUI::setColor(ConsoleUI::Color::YELLOW, ConsoleUI::Color::BLACK);
            cout << " (!)";
            ConsoleUI::setColor(ConsoleUI::Color::WHITE, ConsoleUI::Color::BLACK);
        }
        cout << endl;
    }
    cout << "0. Go back" << endl;
    
    cout << "\nChoice: ";
    int choice;
    cin >> choice;
    
    if (choice > 0 && choice <= (int)npcs.size()) {
        npcs[choice - 1]->talk();
    }
}

void Town::restAtInn(Player& player) {
    if (player.getGold() >= innCost) {
        player.addGold(-innCost);
        player.rest();
        ConsoleUI::printSuccess("You rest at the inn and feel refreshed!");
        ConsoleUI::printInfo("HP fully restored! Gold: " + to_string(player.getGold()));
    } else {
        ConsoleUI::printError("You don't have enough gold! Inn costs " + to_string(innCost) + " gold.");
    }
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}
