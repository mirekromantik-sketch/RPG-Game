#include "ArmorShop.h"
#include "../../Core/ConsoleUI.h"
#include <iostream>
#include <vector>

using namespace std;

struct ArmorShopItem {
    string name;
    string description;
    int price;
    int strBonus;
    int magBonus;
    int defBonus;
    int spdBonus;
    EquipmentClass reqClass;
};

void openArmorShop(Player& player) {
    vector<ArmorShopItem> armors = {
        // Warrior armor
        {"Iron Plate", "Heavy warrior protection", 120, 3, 0, 8, -2, EquipmentClass::WARRIOR},
        {"Steel Plate Armor", "Superior plate protection", 400, 5, 0, 18, -3, EquipmentClass::WARRIOR},
        {"Dragonheart Armor", "Legendary heavy armor", 1600, 15, 0, 40, 0, EquipmentClass::WARRIOR},
        {"Titanium Warlord Plate", "Near-indestructible heavy plate", 700, 10, 0, 25, -2, EquipmentClass::WARRIOR},
        {"Moltenheart Armor", "Forged in dragonfire", 2500, 20, 0, 55, 0, EquipmentClass::WARRIOR},
        {"Colossus Exosuit", "Absurdly OP heavy armor", 10000, 40, 0, 110, 2, EquipmentClass::WARRIOR},
        {"Obsidian Plate", "Dark rock-hard protection", 1200, 15, 0, 35, -1, EquipmentClass::WARRIOR},
        {"Thunderstrike Armor", "Shocks enemies on contact", 1800, 18, 0, 40, 1, EquipmentClass::WARRIOR},
        {"Ironclad Bastion", "Ultimate defensive armor", 2200, 25, 0, 50, 0, EquipmentClass::WARRIOR},
        {"Warbringer Plate", "Conqueror’s legacy", 3500, 30, 0, 60, 2, EquipmentClass::WARRIOR},
        {"Dragonbone Armor", "Bones of ancient dragons", 4000, 32, 0, 65, 3, EquipmentClass::WARRIOR},
        {"Goliath Plate", "Makes wearer nearly unstoppable", 5000, 40, 0, 80, 5, EquipmentClass::WARRIOR},
        {"Armageddon Suit", "Ultimate WARRIOR armor", 15000, 70, 0, 150, 10, EquipmentClass::WARRIOR},
        
        // Mage armor
        {"Apprentice Robes", "Basic magic robes", 100, 0, 6, 2, 3, EquipmentClass::MAGE},
        {"Enchanted Robes", "Magically enhanced robes", 380, 0, 15, 5, 5, EquipmentClass::MAGE},
        {"Archmage Vestments", "Ultimate mage armor", 1500, 0, 35, 12, 10, EquipmentClass::MAGE},
        {"Voidweave Silk", "Absorbs arcane attacks", 650, 0, 18, 8, 6, EquipmentClass::MAGE},
        {"Celestial Mantle", "Starlight-infused robe", 2300, 0, 40, 15, 14, EquipmentClass::MAGE},
        {"Astral Ascendant Robes", "Ridiculously OP", 9500, 0, 95, 30, 25, EquipmentClass::MAGE},
        {"Mystic Shroud", "Protects against magic", 1200, 0, 25, 10, 8, EquipmentClass::MAGE},
        {"Arcane Vestments", "Empowered with ancient runes", 2000, 0, 35, 12, 12, EquipmentClass::MAGE},
        {"Sorcerer’s Cloak", "Boosts spell casting", 2500, 0, 45, 15, 15, EquipmentClass::MAGE},
        {"Ethereal Robes", "Lightweight magical protection", 3000, 0, 50, 18, 18, EquipmentClass::MAGE},
        {"Stormweaver Mantle", "Harnesses elemental fury", 3500, 0, 60, 20, 20, EquipmentClass::MAGE},
        {"Archon Robes", "Blessed by cosmic forces", 5000, 0, 75, 25, 22, EquipmentClass::MAGE},
        {"Infinity Shroud", "The ultimate mage armor", 20000, 0, 150, 50, 40, EquipmentClass::MAGE},
        
        // Rogue armor
        {"Leather Armor", "Light and flexible", 90, 2, 0, 4, 5, EquipmentClass::ROGUE},
        {"Shadow Suit", "Perfect for stealth", 370, 5, 0, 10, 15, EquipmentClass::ROGUE},
        {"Nightshade Armor", "Legendary rogue armor", 1450, 12, 0, 22, 30, EquipmentClass::ROGUE},
        {"Whispercloak", "Silent as the grave", 620, 6, 0, 12, 18, EquipmentClass::ROGUE},
        {"Soulshadow Weave", "Absorbs enemy vision", 2100, 14, 0, 30, 28, EquipmentClass::ROGUE},
        {"Phantomstrike Armor", "Legendary assassin gear", 9000, 30, 0, 55, 50, EquipmentClass::ROGUE},
        {"Shadowveil Suit", "Blend with darkness", 1500, 8, 0, 15, 20, EquipmentClass::ROGUE},
        {"Nightstalker Garb", "Perfect for ambushes", 1800, 10, 0, 20, 22, EquipmentClass::ROGUE},
        {"Eclipse Weave", "Reduces detection risk", 2000, 12, 0, 25, 25, EquipmentClass::ROGUE},
        {"Silent Step Armor", "Increases dodge chance", 2200, 14, 0, 30, 28, EquipmentClass::ROGUE},
        {"Duskfang Suit", "Frightens enemies", 2500, 16, 0, 35, 30, EquipmentClass::ROGUE},
        {"Specter Garb", "Move like a shadow", 4000, 22, 0, 45, 40, EquipmentClass::ROGUE},
        {"Nightveil", "Ultimate rogue armor", 15000, 40, 0, 80, 60, EquipmentClass::ROGUE},
        
        // Cleric armor
        {"Initiate's Vestments", "Basic holy armor", 110, 2, 4, 5, 1, EquipmentClass::CLERIC},
        {"Holy Plate", "Blessed armor", 420, 5, 10, 15, 2, EquipmentClass::CLERIC},
        {"Divine Aegis", "Ultimate holy protection", 1550, 15, 25, 35, 5, EquipmentClass::CLERIC},
        {"Blessed Radiant Mail", "Glows with holy power", 700, 4, 12, 18, 6, EquipmentClass::CLERIC},
        {"Armor of Sacred Valor", "Worn by holy champions", 2500, 12, 28, 40, 10, EquipmentClass::CLERIC},
        {"Lightforged Aegisplate", "Divine-tier protection", 10000, 35, 50, 75, 18, EquipmentClass::CLERIC},
        {"Sanctuary Plate", "Protects the faithful", 1200, 6, 18, 20, 8, EquipmentClass::CLERIC},
        {"Paladin’s Guard", "Blessed with light", 1800, 10, 25, 28, 10, EquipmentClass::CLERIC},
        {"Holy Sentinel Armor", "Resists dark magic", 2200, 14, 32, 35, 12, EquipmentClass::CLERIC},
        {"Divine Radiance Mail", "Shines with holy light", 3000, 18, 40, 40, 14, EquipmentClass::CLERIC},
        {"Seraphic Plate", "Armor of angels", 3500, 20, 45, 45, 15, EquipmentClass::CLERIC},
        {"Celestial Aegis", "Top-tier divine armor", 5000, 25, 60, 60, 18, EquipmentClass::CLERIC},
        {"Heavenward Armor", "Ultimate cleric armor", 20000, 50, 120, 120, 30, EquipmentClass::CLERIC},

        // Ranger armor
        {"Hunter's Garb", "Light ranger armor", 95, 3, 0, 5, 4, EquipmentClass::RANGER},
        {"Wildwood Armor", "Nature-blessed armor", 390, 8, 3, 12, 10, EquipmentClass::RANGER},
        {"Forestlord's Mail", "Legendary ranger armor", 1500, 18, 8, 25, 22, EquipmentClass::RANGER},
        {"Windrunner Garb", "Swift and silent", 620, 6, 0, 9, 16, EquipmentClass::RANGER},
        {"Stormleaf Harness", "Nature’s fury made armor", 2100, 12, 5, 22, 18, EquipmentClass::RANGER},
        {"Sylvan Warden Mail", "Elite forest guardian gear", 9000, 28, 12, 48, 35, EquipmentClass::RANGER},
        {"Shadowwood Cloak", "Blend with forest shadows", 1500, 6, 3, 12, 14, EquipmentClass::RANGER},
        {"Hunter’s Vestments", "Increases ranged attack", 1800, 8, 4, 16, 16, EquipmentClass::RANGER},
        {"Elven Hunter Armor", "Crafted by elven smiths", 2000, 10, 5, 20, 18, EquipmentClass::RANGER},
        {"Forestwarden Garb", "Nature-protection", 2200, 12, 6, 25, 20, EquipmentClass::RANGER},
        {"Wildheart Harness", "Boosts agility", 2500, 14, 8, 30, 22, EquipmentClass::RANGER},
        {"Naturelord’s Mail", "Legendary ranger armor", 4000, 20, 10, 40, 30, EquipmentClass::RANGER},
        {"Worldtree Plate", "Insanely OP ranger armor", 15000, 45, 20, 90, 50, EquipmentClass::RANGER},
        
        // Universal armor
        {"Traveler's Cloak", "Good for any adventurer", 180, 3, 2, 6, 3, EquipmentClass::ALL},
        {"Mystic Chain", "Magic enhanced chainmail", 550, 8, 8, 15, 5, EquipmentClass::ALL},
        {"Arcane Chainweave", "Light yet powerful", 700, 6, 8, 18, 8, EquipmentClass::ALL},
        {"Dragonsteel Brigandine", "Forged with draconic magic", 2800, 15, 12, 30, 12, EquipmentClass::ALL},
        {"Godskin Cloak", "Worn by divine beings", 15000, 40, 35, 55, 25, EquipmentClass::ALL},
        {"Traveler’s Armor", "Good for any adventurer", 1000, 8, 10, 20, 10, EquipmentClass::ALL},
        {"Mystic Plate", "Magic-resistant armor", 2200, 12, 20, 30, 15, EquipmentClass::ALL},
        {"Eternal Guard", "Durable for all classes", 3000, 18, 25, 40, 18, EquipmentClass::ALL},
        {"Omniguard Suit", "Universal defensive power", 3500, 20, 30, 45, 20, EquipmentClass::ALL},
        {"Celestial Guard", "Blessed for all adventurers", 5000, 25, 35, 55, 25, EquipmentClass::ALL},
        {"Infinity Armor", "Ridiculously OP universal armor", 12000, 40, 80, 100, 40, EquipmentClass::ALL},
        {"Godslayer Plate", "Ultimate universal armor", 25000, 80, 150, 200, 80, EquipmentClass::ALL}
    };
    
    bool shopping = true;
    while (shopping) {
        ConsoleUI::clearScreen();
        ConsoleUI::printHeader("=== ARMOR SHOP ===");
        ConsoleUI::setColor(ConsoleUI::Color::YELLOW, ConsoleUI::Color::BLACK);
        cout << "Your Gold: " << player.getGold() << " | Your Class: " << player.getClassName();
        ConsoleUI::setColor(ConsoleUI::Color::WHITE, ConsoleUI::Color::BLACK);
        cout << endl;
        ConsoleUI::printSeparator();
        
        for (size_t i = 0; i < armors.size(); i++) {
            auto& a = armors[i];
            
            bool canUse = (a.reqClass == EquipmentClass::ALL);
            if (!canUse) {
                if (player.getClassName() == "Warrior") canUse = (a.reqClass == EquipmentClass::WARRIOR);
                else if (player.getClassName() == "Mage") canUse = (a.reqClass == EquipmentClass::MAGE);
                else if (player.getClassName() == "Rogue") canUse = (a.reqClass == EquipmentClass::ROGUE);
                else if (player.getClassName() == "Cleric") canUse = (a.reqClass == EquipmentClass::CLERIC);
                else if (player.getClassName() == "Ranger") canUse = (a.reqClass == EquipmentClass::RANGER);
            }
            
            if (canUse) {
                ConsoleUI::setColor(ConsoleUI::Color::GREEN, ConsoleUI::Color::BLACK);
            } else {
                ConsoleUI::setColor(ConsoleUI::Color::DARK_GRAY, ConsoleUI::Color::BLACK);
            }
            
            cout << (i + 1) << ". " << a.name << " - " << a.price << " gold";
            ConsoleUI::setColor(ConsoleUI::Color::WHITE, ConsoleUI::Color::BLACK);
            cout << "\n   " << a.description;
            cout << " [";
            if (a.strBonus != 0) cout << (a.strBonus > 0 ? "+" : "") << a.strBonus << " STR ";
            if (a.magBonus != 0) cout << (a.magBonus > 0 ? "+" : "") << a.magBonus << " MAG ";
            if (a.defBonus != 0) cout << (a.defBonus > 0 ? "+" : "") << a.defBonus << " DEF ";
            if (a.spdBonus != 0) cout << (a.spdBonus > 0 ? "+" : "") << a.spdBonus << " SPD ";
            cout << "]\n";
            
            string classReq = "All Classes";
            if (a.reqClass == EquipmentClass::WARRIOR) classReq = "Warrior Only";
            else if (a.reqClass == EquipmentClass::MAGE) classReq = "Mage Only";
            else if (a.reqClass == EquipmentClass::ROGUE) classReq = "Rogue Only";
            else if (a.reqClass == EquipmentClass::CLERIC) classReq = "Cleric Only";
            else if (a.reqClass == EquipmentClass::RANGER) classReq = "Ranger Only";
            
            ConsoleUI::setColor(ConsoleUI::Color::CYAN, ConsoleUI::Color::BLACK);
            cout << "   Class: " << classReq;
            ConsoleUI::setColor(ConsoleUI::Color::WHITE, ConsoleUI::Color::BLACK);
            cout << "\n" << endl;
        }
        
        cout << (armors.size() + 1) << ". Leave Shop" << endl;
        ConsoleUI::printSeparator();
        cout << "Choice: ";
        
        int choice;
        cin >> choice;
        
        if (choice == (int)armors.size() + 1) {
            shopping = false;
            ConsoleUI::printInfo("Thanks for visiting!");
        } else if (choice > 0 && choice <= (int)armors.size()) {
            auto& a = armors[choice - 1];
            
            if (player.getGold() >= a.price) {
                player.addGold(-a.price);
                Item newItem(a.name, a.description, ItemType::ARMOR, a.price / 2, a.strBonus, a.magBonus, a.defBonus, a.spdBonus, a.reqClass);
                player.getInventory().addItem(newItem);
                ConsoleUI::printSuccess("Purchased " + a.name + "!");
                cout << "\nPress Enter to continue...";
                cin.ignore();
                cin.get();
            } else {
                ConsoleUI::printError("Not enough gold! You need " + to_string(a.price) + " gold.");
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
