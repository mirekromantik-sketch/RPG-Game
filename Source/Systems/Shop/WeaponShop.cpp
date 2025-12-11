#include "WeaponShop.h"
#include "../../Core/ConsoleUI.h"
#include <iostream>
#include <vector>

using namespace std;

struct WeaponShopItem {
    string name;
    string description;
    int price;
    int strBonus;
    int magBonus;
    int spdBonus;
    EquipmentClass reqClass;
};

void openWeaponShop(Player& player) {
    vector<WeaponShopItem> weapons = {
        // Warrior weapons
        {"Iron Sword", "A basic warrior's blade", 100, 5, 0, 0, EquipmentClass::WARRIOR},
        {"Steel Greatsword", "A heavy warrior weapon", 300, 12, 0, -2, EquipmentClass::WARRIOR},
        {"Legendary Claymore", "Ultimate warrior blade", 1500, 35, 0, 5, EquipmentClass::WARRIOR},
        {"Ragnarok Cleaver", "Cleave enemies like gods", 1800, 38, 0, 4, EquipmentClass::WARRIOR},
        {"Oblivion Axe", "Chops through reality itself", 4000, 70, 0, 10, EquipmentClass::WARRIOR},
        {"Titan Hammer", "Weight of a mountain", 2200, 50, 0, 2, EquipmentClass::WARRIOR},
        {"Bloodfang Greatsword", "Drains life with each hit", 1600, 42, 0, 6, EquipmentClass::WARRIOR},
        {"Earthsplitter", "Smashes the ground and foes", 2000, 48, 0, -1, EquipmentClass::WARRIOR},
        {"Infernal Blade", "Burns enemies to ash", 3200, 65, 0, 7, EquipmentClass::WARRIOR},
        {"Colossus Fang", "Massive crushing power", 2900, 55, 0, 0, EquipmentClass::WARRIOR},
        {"Hammer of the Fallen", "Empowered by fallen warriors", 2100, 45, 0, 3, EquipmentClass::WARRIOR},
        {"Titanforge Sword", "Forged in divine fire", 3500, 72, 0, 8, EquipmentClass::WARRIOR},
        {"Doombringer", "Legendary end-of-all weapon", 10000, 120, 0, 20, EquipmentClass::WARRIOR},
        
        // Mage weapons
        {"Wooden Staff", "A simple magical staff", 100, 0, 8, 2, EquipmentClass::MAGE},
        {"Crystal Staff", "A staff of pure magic", 400, 0, 18, 3, EquipmentClass::MAGE},
        {"Archmage Scepter", "Staff of ultimate power", 1500, 0, 40, 8, EquipmentClass::MAGE},
        {"Netherflare Staff", "Flames from another dimension", 2500, 0, 55, 12, EquipmentClass::MAGE},
        {"Soulbinder Wand", "Traps souls for power", 1800, 0, 42, 10, EquipmentClass::MAGE},
        {"Voidcaster", "Channels void energy", 3000, 0, 60, 15, EquipmentClass::MAGE},
        {"Phoenix Rod", "Rebirth through fire", 2200, 0, 48, 9, EquipmentClass::MAGE},
        {"Astral Scepter", "Manipulates stars", 4000, 0, 70, 20, EquipmentClass::MAGE},
        {"Eclipse Wand", "Shadow and light combined", 3600, 0, 65, 18, EquipmentClass::MAGE},
        {"Chronomancer Staff", "Bends time", 5000, 0, 80, 25, EquipmentClass::MAGE},
        {"Stormcaller Rod", "Unleashes tempests", 4200, 0, 68, 22, EquipmentClass::MAGE},
        {"Celestial Wand", "Taps pure cosmic energy", 5500, 0, 90, 30, EquipmentClass::MAGE},
        {"Infinity Scepter", "The ultimate mage weapon", 20000, 0, 200, 50, EquipmentClass::MAGE},
        
        // Rogue weapons
        {"Iron Dagger", "A swift assassin's blade", 80, 4, 0, 4, EquipmentClass::ROGUE},
        {"Shadow Blade", "Strikes from the darkness", 350, 10, 0, 12, EquipmentClass::ROGUE},
        {"Nightfall", "Legendary rogue weapon", 1400, 25, 0, 25, EquipmentClass::ROGUE},
        {"Venomfang Dagger", "Poisons with each strike", 1500, 20, 0, 25, EquipmentClass::ROGUE},
        {"Night Whisper", "Silent, deadly, unseen", 1800, 24, 0, 28, EquipmentClass::ROGUE},
        {"Dagger of Shadows", "Absorbs light and HP", 2000, 28, 0, 30, EquipmentClass::ROGUE},
        {"Twinfangs", "Dual daggers of havoc", 2200, 32, 0, 35, EquipmentClass::ROGUE},
        {"Assassin’s Edge", "One strike, instant death", 3000, 40, 0, 38, EquipmentClass::ROGUE},
        {"Specter Blades", "Pass through walls", 4000, 50, 0, 45, EquipmentClass::ROGUE},
        {"Viperfang", "Fastest dagger in existence", 3200, 45, 0, 42, EquipmentClass::ROGUE},
        {"Shadowfang Twinblades", "Double your damage", 5000, 60, 0, 55, EquipmentClass::ROGUE},
        {"Phantom Claws", "Rip through reality", 7000, 75, 0, 70, EquipmentClass::ROGUE},
        {"Death’s Kiss", "Ultimate rogue weapon", 15000, 150, 0, 100, EquipmentClass::ROGUE},
        
        // Cleric weapons
        {"Holy Mace", "Blessed by the gods", 120, 3, 5, 1, EquipmentClass::CLERIC},
        {"Divine Hammer", "Smites evil", 450, 8, 12, 2, EquipmentClass::CLERIC},
        {"Heaven's Judgement", "Ultimate holy weapon", 1600, 20, 30, 5, EquipmentClass::CLERIC},
        {"Sanctified Mace", "Blessed with holy wrath", 1800, 12, 32, 4, EquipmentClass::CLERIC},
        {"Hammer of Light", "Shines on evil", 2100, 18, 38, 5, EquipmentClass::CLERIC},
        {"Celestial Warhammer", "Power of heavens", 3000, 25, 50, 8, EquipmentClass::CLERIC},
        {"Divine Lance", "Pierces darkness", 2500, 22, 45, 7, EquipmentClass::CLERIC},
        {"Holy Avenger", "Massive holy damage", 4000, 35, 60, 10, EquipmentClass::CLERIC},
        {"Radiant Scepter", "Emits blinding light", 2200, 15, 42, 6, EquipmentClass::CLERIC},
        {"Blessed Morningstar", "Crushes evil hearts", 2800, 28, 55, 9, EquipmentClass::CLERIC},
        {"Purity Hammer", "Exorcises demons", 3500, 40, 70, 12, EquipmentClass::CLERIC},
        {"Divine Retribution", "Massive smite power", 8000, 75, 120, 20, EquipmentClass::CLERIC},
        {"Heavenfall", "OP holy relic", 20000, 150, 250, 50, EquipmentClass::CLERIC},
        
        // Ranger weapons
        {"Hunting Bow", "A reliable ranger's bow", 90, 5, 0, 3, EquipmentClass::RANGER},
        {"Elven Longbow", "Crafted by elven masters", 400, 12, 2, 8, EquipmentClass::RANGER},
        {"Stormbow", "Legendary ranger weapon", 1500, 28, 5, 18, EquipmentClass::RANGER},
        {"Windpiercer Bow", "Arrows fly like wind", 1800, 30, 5, 15, EquipmentClass::RANGER},
        {"Moonshadow Longbow", "Silent as the night", 2000, 35, 7, 18, EquipmentClass::RANGER},
        {"Stormstrike Bow", "Lightning-infused arrows", 2500, 42, 10, 22, EquipmentClass::RANGER},
        {"Falcon Eye", "Never misses a target", 2200, 38, 8, 20, EquipmentClass::RANGER},
        {"Nature's Wrath", "Bow infused with forest power", 2800, 45, 12, 25, EquipmentClass::RANGER},
        {"Thunderhawk Bow", "Calls down storms", 3200, 50, 15, 28, EquipmentClass::RANGER},
        {"Shadowvine Bow", "Silent yet deadly", 3000, 48, 10, 26, EquipmentClass::RANGER},
        {"Dragonstring Bow", "Stronger than steel", 4000, 60, 18, 35, EquipmentClass::RANGER},
        {"Eagleheart Longbow", "Legendary ranger weapon", 5000, 72, 20, 40, EquipmentClass::RANGER},
        {"Worldbreaker Bow", "Insanely overpowered", 15000, 150, 50, 80, EquipmentClass::RANGER},
        
        // Universal weapons
        {"Balanced Sword", "Good for any class", 200, 8, 3, 2, EquipmentClass::ALL},
        {"Enchanted Blade", "Magic enhanced weapon", 600, 15, 8, 5, EquipmentClass::ALL},
        {"Omniblade", "Good for anyone", 2000, 25, 15, 10, EquipmentClass::ALL},
        {"Eclipse Edge", "Shadow + light", 3500, 40, 25, 15, EquipmentClass::ALL},
        {"Aetherfang", "Pure energy weapon", 5000, 60, 35, 25, EquipmentClass::ALL},
        {"Infinity Blade", "Limitless power", 8000, 90, 50, 30, EquipmentClass::ALL},
        {"Void Reaper", "Destroys everything", 10000, 120, 60, 40, EquipmentClass::ALL},
        {"Starshard Sword", "Cosmic energy infused", 4500, 55, 30, 20, EquipmentClass::ALL},
        {"Dragonfang", "Dragon-blooded weapon", 6000, 70, 40, 25, EquipmentClass::ALL},
        {"Titan Edge", "Crushes the unworthy", 7000, 80, 45, 30, EquipmentClass::ALL},
        {"Celestial Sword", "Blessed by gods", 9000, 100, 60, 35, EquipmentClass::ALL},
        {"Armageddon Blade", "Ridiculously OP universal weapon", 20000, 200, 150, 60, EquipmentClass::ALL}
    };
    
    bool shopping = true;
    while (shopping) {
        ConsoleUI::clearScreen();
        ConsoleUI::printHeader("=== WEAPON SHOP ===");
        ConsoleUI::setColor(ConsoleUI::Color::YELLOW, ConsoleUI::Color::BLACK);
        cout << "Your Gold: " << player.getGold() << " | Your Class: " << player.getClassName();
        ConsoleUI::setColor(ConsoleUI::Color::WHITE, ConsoleUI::Color::BLACK);
        cout << endl;
        ConsoleUI::printSeparator();
        
        for (size_t i = 0; i < weapons.size(); i++) {
            auto& w = weapons[i];
            
            // Color based on if player can use it
            EquipmentClass reqClass = w.reqClass;
            bool canUse = (reqClass == EquipmentClass::ALL);
            if (!canUse) {
                if (player.getClassName() == "Warrior") canUse = (reqClass == EquipmentClass::WARRIOR);
                else if (player.getClassName() == "Mage") canUse = (reqClass == EquipmentClass::MAGE);
                else if (player.getClassName() == "Rogue") canUse = (reqClass == EquipmentClass::ROGUE);
                else if (player.getClassName() == "Cleric") canUse = (reqClass == EquipmentClass::CLERIC);
                else if (player.getClassName() == "Ranger") canUse = (reqClass == EquipmentClass::RANGER);
            }
            
            if (canUse) {
                ConsoleUI::setColor(ConsoleUI::Color::GREEN, ConsoleUI::Color::BLACK);
            } else {
                ConsoleUI::setColor(ConsoleUI::Color::DARK_GRAY, ConsoleUI::Color::BLACK);
            }
            
            cout << (i + 1) << ". " << w.name << " - " << w.price << " gold";
            ConsoleUI::setColor(ConsoleUI::Color::WHITE, ConsoleUI::Color::BLACK);
            cout << "\n   " << w.description;
            cout << " [";
            if (w.strBonus != 0) cout << (w.strBonus > 0 ? "+" : "") << w.strBonus << " STR ";
            if (w.magBonus != 0) cout << (w.magBonus > 0 ? "+" : "") << w.magBonus << " MAG ";
            if (w.spdBonus != 0) cout << (w.spdBonus > 0 ? "+" : "") << w.spdBonus << " SPD ";
            cout << "]\n";
            
            string classReq = "All Classes";
            if (reqClass == EquipmentClass::WARRIOR) classReq = "Warrior Only";
            else if (reqClass == EquipmentClass::MAGE) classReq = "Mage Only";
            else if (reqClass == EquipmentClass::ROGUE) classReq = "Rogue Only";
            else if (reqClass == EquipmentClass::CLERIC) classReq = "Cleric Only";
            else if (reqClass == EquipmentClass::RANGER) classReq = "Ranger Only";
            
            ConsoleUI::setColor(ConsoleUI::Color::CYAN, ConsoleUI::Color::BLACK);
            cout << "   Class: " << classReq;
            ConsoleUI::setColor(ConsoleUI::Color::WHITE, ConsoleUI::Color::BLACK);
            cout << "\n" << endl;
        }
        
        cout << (weapons.size() + 1) << ". Leave Shop" << endl;
        ConsoleUI::printSeparator();
        cout << "Choice: ";
        
        int choice;
        cin >> choice;
        
        if (choice == (int)weapons.size() + 1) {
            shopping = false;
            ConsoleUI::printInfo("Thanks for visiting!");
        } else if (choice > 0 && choice <= (int)weapons.size()) {
            auto& w = weapons[choice - 1];
            
            if (player.getGold() >= w.price) {
                player.addGold(-w.price);
                Item newItem(w.name, w.description, ItemType::WEAPON, w.price / 2, w.strBonus, w.magBonus, 0, w.spdBonus, w.reqClass);
                player.getInventory().addItem(newItem);
                ConsoleUI::printSuccess("Purchased " + w.name + "!");
                cout << "\nPress Enter to continue...";
                cin.ignore();
                cin.get();
            } else {
                ConsoleUI::printError("Not enough gold! You need " + to_string(w.price) + " gold.");
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
