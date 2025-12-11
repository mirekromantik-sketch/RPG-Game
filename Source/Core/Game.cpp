#include "Game.h"
#include "ConsoleUI.h"
#include "../Entities/Enemies/Enemy.h"
#include "../Entities/Enemies/boss.h"
#include "../Systems/Shop/WeaponShop.h"
#include "../Systems/Shop/ArmorShop.h"
#include "../Systems/Shop/PotionShop.h"
#include "../Systems/NPC/NPC.h"
#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

Game::Game() : player(nullptr), running(true) {
    initializeTowns();
}

Game::~Game() {
    if (player) {
        // Auto-save with current save file name
        string saveName = player->getName() + "_autosave";
        saveManager.saveGame(*player, saveName);
        delete player;
    }
    
    // Clean up towns
    for (Town* town : towns) {
        delete town;
    }
}

void Game::run() {
    ConsoleUI::clearScreen();
    ConsoleUI::printHeader("WELCOME TO RPG GAME");
    ConsoleUI::printColoredText("\n          ~ A Text-Based Adventure ~\n\n", ConsoleUI::CYAN);
    
    showStartMenu();
    
    while (running) {
        showMainMenu();
    }
}

void Game::showStartMenu() {
    ConsoleUI::printHeader("START MENU");
    
    vector<string> saveFiles = saveManager.listSaveFiles();
    
    ConsoleUI::printSeparator('-', 60);
    ConsoleUI::printColoredText("  1. ", ConsoleUI::YELLOW);
    cout << "New Game\n";
    ConsoleUI::printColoredText("  2. ", ConsoleUI::YELLOW);
    cout << "Load Game\n";
    
    if (!saveFiles.empty()) {
        ConsoleUI::printColoredText("  3. ", ConsoleUI::YELLOW);
        cout << "Delete Save\n";
    }
    
    ConsoleUI::printColoredText("  0. ", ConsoleUI::RED);
    cout << "Exit\n";
    ConsoleUI::printSeparator('-', 60);
    
    if (!saveFiles.empty()) {
        ConsoleUI::printInfo("Found " + to_string(saveFiles.size()) + " save file(s)");
    } else {
        ConsoleUI::printWarning("No save files found");
    }
    
    ConsoleUI::printColoredText("\n  Choice: ", ConsoleUI::CYAN);
    
    int choice;
    cin >> choice;
    
    switch (choice) {
        case 1:
            characterCreation();
            break;
        case 2:
            loadSaveMenu();
            if (!player) {
                ConsoleUI::printError("Failed to load game. Creating new character...");
                ConsoleUI::waitForEnter();
                characterCreation();
            }
            break;
        case 3:
            if (!saveFiles.empty()) {
                deleteSaveMenu();
                showStartMenu();
            } else {
                ConsoleUI::printError("Invalid choice!");
                ConsoleUI::waitForEnter();
                showStartMenu();
            }
            break;
        case 0:
            running = false;
            ConsoleUI::clearScreen();
            ConsoleUI::printHeader("GOODBYE");
            ConsoleUI::printSuccess("Thank you for playing!");
            break;
        default:
            ConsoleUI::printError("Invalid choice!");
            ConsoleUI::waitForEnter();
            showStartMenu();
    }
}

void Game::loadSaveMenu() {
    ConsoleUI::clearScreen();
    ConsoleUI::printHeader("LOAD GAME");
    
    vector<string> saveFiles = saveManager.listSaveFiles();
    
    if (saveFiles.empty()) {
        ConsoleUI::printError("No save files found!");
        ConsoleUI::waitForEnter();
        return;
    }
    
    ConsoleUI::printSeparator('-', 60);
    for (size_t i = 0; i < saveFiles.size(); i++) {
        ConsoleUI::printColoredText("  " + to_string(i + 1) + ". ", ConsoleUI::YELLOW);
        cout << saveFiles[i] << "\n";
    }
    ConsoleUI::printColoredText("  0. ", ConsoleUI::RED);
    cout << "Cancel\n";
    ConsoleUI::printSeparator('-', 60);
    
    ConsoleUI::printColoredText("\n  Choose save to load: ", ConsoleUI::CYAN);
    
    int choice;
    cin >> choice;
    
    if (choice == 0) {
        return;
    }
    
    if (choice > 0 && choice <= (int)saveFiles.size()) {
        string saveName = saveFiles[choice - 1];
        saveManager.setSaveFile(saveName);
        
        if (saveManager.loadGame(player, saveName)) {
            ConsoleUI::printSuccess("Game loaded successfully!");
        } else {
            ConsoleUI::printError("Failed to load save file!");
        }
        ConsoleUI::waitForEnter();
    } else {
        ConsoleUI::printError("Invalid choice!");
        ConsoleUI::waitForEnter();
    }
}

void Game::deleteSaveMenu() {
    ConsoleUI::clearScreen();
    ConsoleUI::printHeader("DELETE SAVE");
    
    vector<string> saveFiles = saveManager.listSaveFiles();
    
    if (saveFiles.empty()) {
        ConsoleUI::printError("No save files found!");
        ConsoleUI::waitForEnter();
        return;
    }
    
    ConsoleUI::printSeparator('-', 60);
    for (size_t i = 0; i < saveFiles.size(); i++) {
        ConsoleUI::printColoredText("  " + to_string(i + 1) + ". ", ConsoleUI::YELLOW);
        cout << saveFiles[i] << "\n";
    }
    ConsoleUI::printColoredText("  0. ", ConsoleUI::RED);
    cout << "Cancel\n";
    ConsoleUI::printSeparator('-', 60);
    
    ConsoleUI::printColoredText("\n  Choose save to delete: ", ConsoleUI::CYAN);
    
    int choice;
    cin >> choice;
    
    if (choice == 0) {
        return;
    }
    
    if (choice > 0 && choice <= (int)saveFiles.size()) {
        string saveName = saveFiles[choice - 1];
        
        ConsoleUI::printWarning("Are you sure you want to delete '" + saveName + "'? (y/n): ");
        char confirm;
        cin >> confirm;
        
        if (confirm == 'y' || confirm == 'Y') {
            saveManager.deleteSave(saveName);
            ConsoleUI::printSuccess("Save file deleted!");
        } else {
            ConsoleUI::printInfo("Deletion cancelled.");
        }
        ConsoleUI::waitForEnter();
    } else {
        ConsoleUI::printError("Invalid choice!");
        ConsoleUI::waitForEnter();
    }
}

void Game::saveGame() {
    if (player) {
        ConsoleUI::printHeader("SAVE GAME");
        
        ConsoleUI::printColoredText("  Enter save name (or press Enter for default): ", ConsoleUI::CYAN);
        cin.ignore();
        string saveName;
        getline(cin, saveName);
        
        if (saveName.empty()) {
            saveName = player->getName() + "_save";
        }
        
        if (saveManager.saveGame(*player, saveName)) {
            ConsoleUI::printSuccess("Game saved as '" + saveName + "'!");
        } else {
            ConsoleUI::printError("Failed to save game!");
        }
    }
}

void Game::loadGame() {
    if (saveManager.loadGame(player)) {
        ConsoleUI::printSuccess("Game loaded successfully!");
    } else {
        ConsoleUI::printError("No save file found or failed to load!");
    }
}

void Game::showMainMenu() {
    ConsoleUI::printHeader("MAIN MENU");
    
    // Display player status bar
    if (player) {
        ConsoleUI::setColor(ConsoleUI::YELLOW, ConsoleUI::BLACK);
        cout << "  " << player->getName() << " | ";
        ConsoleUI::setColor(ConsoleUI::CYAN, ConsoleUI::BLACK);
        cout << "Lv." << player->getLevel() << " ";
        ConsoleUI::setColor(ConsoleUI::GREEN, ConsoleUI::BLACK);
        cout << player->getClassName() << " ";
        ConsoleUI::setColor(ConsoleUI::MAGENTA, ConsoleUI::BLACK);
        cout << "(" << player->getOriginName() << ")";
        ConsoleUI::resetColor();
        cout << "\n";
        ConsoleUI::setColor(ConsoleUI::RED, ConsoleUI::BLACK);
        cout << "  HP: " << player->getHP() << "/" << player->getMaxHP();
        ConsoleUI::setColor(ConsoleUI::YELLOW, ConsoleUI::BLACK);
        cout << "  |  Gold: " << player->getGold();
        ConsoleUI::resetColor();
        cout << "\n\n";
    }
    
    ConsoleUI::printSeparator('-', 60);
    ConsoleUI::printColoredText("  1. ", ConsoleUI::YELLOW);
    cout << "Show Character\n";
    ConsoleUI::printColoredText("  2. ", ConsoleUI::YELLOW);
    cout << "Explore World\n";
    ConsoleUI::printColoredText("  3. ", ConsoleUI::YELLOW);
    cout << "Show Inventory\n";
    ConsoleUI::printColoredText("  4. ", ConsoleUI::YELLOW);
    cout << "Show Quests\n";
    ConsoleUI::printColoredText("  5. ", ConsoleUI::YELLOW);
    cout << "Travel to Towns\n";
    ConsoleUI::printColoredText("  6. ", ConsoleUI::YELLOW);
    cout << "Story Boss Challenge\n";
    ConsoleUI::printColoredText("  7. ", ConsoleUI::YELLOW);
    cout << "Rest (Restore HP)\n";
    ConsoleUI::printColoredText("  8. ", ConsoleUI::YELLOW);
    cout << "Talent Tree\n";
    ConsoleUI::printColoredText("  9. ", ConsoleUI::YELLOW);
    cout << "Distribute Attribute Points\n";
    ConsoleUI::printColoredText(" 10. ", ConsoleUI::YELLOW);
    cout << "Save Game\n";
    ConsoleUI::printColoredText("  0. ", ConsoleUI::RED);
    cout << "Exit Game\n";
    ConsoleUI::printSeparator('-', 60);
    ConsoleUI::printColoredText("\n  Choice: ", ConsoleUI::CYAN);
    
    int choice;
    cin >> choice;
    
    switch (choice) {
        case 1:
            ConsoleUI::clearScreen();
            player->showStats();
            ConsoleUI::waitForEnter();
            break;
        case 2:
            exploreWorld();
            break;
        case 3:
            ConsoleUI::clearScreen();
            showInventory();
            ConsoleUI::waitForEnter();
            break;
        case 4:
            ConsoleUI::clearScreen();
            showQuests();
            ConsoleUI::waitForEnter();
            break;
        case 5:
            visitTowns();
            break;
        case 6:
            storyBossEncounter();
            break;
        case 7:
            player->rest();
            ConsoleUI::printSuccess("You rest and restore health!");
            ConsoleUI::waitForEnter();
            break;
        case 8:
            ConsoleUI::clearScreen();
            player->openTalentTree();
            break;
        case 9:
            ConsoleUI::clearScreen();
            player->distributeAttributePoints();
            ConsoleUI::waitForEnter();
            break;
        case 10:
            ConsoleUI::clearScreen();
            saveGame();
            ConsoleUI::waitForEnter();
            break;
        case 0:
            running = false;
            ConsoleUI::clearScreen();
            ConsoleUI::printHeader("GOODBYE");
            ConsoleUI::printSuccess("Game saved. Thank you for playing!");
            break;
        default:
            ConsoleUI::printError("Invalid choice!");
            ConsoleUI::waitForEnter();
    }
}

void Game::characterCreation() {
    ConsoleUI::printHeader("CHARACTER CREATION");
    
    ConsoleUI::printColoredText("  Enter your character's name: ", ConsoleUI::CYAN);
    string name;
    cin.ignore();
    getline(cin, name);

    ConsoleUI::clearScreen();
    ConsoleUI::printHeader("CHOOSE YOUR ORIGIN");
    ConsoleUI::printSeparator('-', 60);
    ConsoleUI::printColoredText("  1. ", ConsoleUI::YELLOW);
    ConsoleUI::printColoredText("Human", ConsoleUI::WHITE);
    cout << " - Balanced, +10% gold gain\n";
    ConsoleUI::printColoredText("  2. ", ConsoleUI::YELLOW);
    ConsoleUI::printColoredText("Elf", ConsoleUI::GREEN);
    cout << " - High magic & speed, lower HP\n";
    ConsoleUI::printColoredText("  3. ", ConsoleUI::YELLOW);
    ConsoleUI::printColoredText("Dwarf", ConsoleUI::DARK_YELLOW);
    cout << " - High HP & defense, lower speed\n";
    ConsoleUI::printColoredText("  4. ", ConsoleUI::YELLOW);
    ConsoleUI::printColoredText("Orc", ConsoleUI::RED);
    cout << " - High strength, lower magic\n";
    ConsoleUI::printColoredText("  5. ", ConsoleUI::YELLOW);
    ConsoleUI::printColoredText("Halfling", ConsoleUI::CYAN);
    cout << " - High speed, lower HP\n";
    ConsoleUI::printSeparator('-', 60);
    ConsoleUI::printColoredText("\n  Choice: ", ConsoleUI::CYAN);
    int originChoice;
    cin >> originChoice;

    ConsoleUI::clearScreen();
    ConsoleUI::printHeader("CHOOSE YOUR CLASS");
    ConsoleUI::printSeparator('-', 60);
    ConsoleUI::printColoredText("  1. ", ConsoleUI::YELLOW);
    ConsoleUI::printColoredText("Warrior", ConsoleUI::RED);
    cout << " - High HP, High Strength, Tank\n";
    ConsoleUI::printColoredText("  2. ", ConsoleUI::YELLOW);
    ConsoleUI::printColoredText("Mage", ConsoleUI::BLUE);
    cout << " - High Magic, Low HP, Spellcaster\n";
    ConsoleUI::printColoredText("  3. ", ConsoleUI::YELLOW);
    ConsoleUI::printColoredText("Rogue", ConsoleUI::GREEN);
    cout << " - Balanced, High Speed, Critical Strikes\n";
    ConsoleUI::printColoredText("  4. ", ConsoleUI::YELLOW);
    ConsoleUI::printColoredText("Cleric", ConsoleUI::YELLOW);
    cout << " - Healer, Balanced Stats, Support\n";
    ConsoleUI::printColoredText("  5. ", ConsoleUI::YELLOW);
    ConsoleUI::printColoredText("Ranger", ConsoleUI::DARK_GREEN);
    cout << " - Ranged Attacks, Pet Companion\n";
    ConsoleUI::printSeparator('-', 60);
    ConsoleUI::printColoredText("\n  Choice: ", ConsoleUI::CYAN);
    
    int classChoice;
    cin >> classChoice;
    
    player = new Player(name, classChoice, originChoice);
    
    ConsoleUI::clearScreen();
    ConsoleUI::printHeader("CHARACTER CREATED");
    player->showStats();
    ConsoleUI::printSuccess("\nYour adventure begins!");
    
    // Add starting quest
    questManager.addQuest("First Steps", "Kill 3 enemies", 100);
    
    ConsoleUI::waitForEnter();
}

void Game::exploreWorld() {
    cout << "\n=== Exploring... ===" << endl;
    
    // 20% chance to encounter a boss
    int encounterChance = rand() % 100;
    
    if (encounterChance < 20) {
        cout << "You feel a powerful presence..." << endl;
        bossEncounter();
    } else {
        cout << "You encounter an enemy!" << endl;
        combat();
    }
}

void Game::showInventory() {
    player->getInventory().equipMenu(*player);
}

void Game::showQuests() {
    questManager.displayQuests();
}

void Game::visitShops() {
    bool shopping = true;
    while (shopping) {
        cout << "\n=== Town Shops ===" << endl;
        cout << "1. Weapon Shop" << endl;
        cout << "2. Armor Shop" << endl;
        cout << "3. Potion Shop" << endl;
        cout << "4. Leave Town" << endl;
        cout << "Choice: ";
        
        int choice;
        cin >> choice;
        
        switch (choice) {
            case 1:
                openWeaponShop(*player);
                break;
            case 2:
                openArmorShop(*player);
                break;
            case 3:
                openPotionShop(*player);
                break;
            case 4:
                shopping = false;
                cout << "You leave the town." << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    }
}

void Game::combat() {
    Enemy enemy = Enemy::generateRandomEnemy(player->getLevel());
    
    cout << "\nA " << enemy.getName() << " appears! (HP: " << enemy.getHP() << ")" << endl;
    
    while (player->isAlive() && enemy.isAlive()) {
        cout << "\n--- Combat ---" << endl;
        cout << "Your HP: " << player->getHP() << "/" << player->getMaxHP() << endl;
        cout << "Enemy HP: " << enemy.getHP() << "/" << enemy.getMaxHP() << endl;
        cout << "\n1. Attack" << endl;
        cout << "2. Use Item" << endl;
        cout << "3. Run Away" << endl;
        cout << "Choice: ";
        
        int choice;
        cin >> choice;
        
        if (choice == 1) {
            int damage = player->attack();
            enemy.takeDamage(damage);
            cout << "You deal " << damage << " damage!" << endl;
            
            if (!enemy.isAlive()) {
                cout << "\nYou defeated " << enemy.getName() << "!" << endl;
                int xp = enemy.getXPReward();
                int gold = enemy.getGoldReward();
                player->gainExperience(xp);
                player->addGold(gold);
                cout << "You gained " << xp << " experience and " << gold << " gold!" << endl;
                
                // Random item drop
                if (rand() % 100 < 30) {
                    Item drop = Item::generateRandomItem();
                    cout << "You found: " << drop.getName() << "!" << endl;
                    player->getInventory().addItem(drop);
                }
                
                questManager.updateProgress("First Steps", 1);
                return;
            }
            
            // Enemy attacks
            int enemyDamage = enemy.attack();
            player->takeDamage(enemyDamage);
            cout << "The enemy deals " << enemyDamage << " damage!" << endl;
            
            if (!player->isAlive()) {
                cout << "\nYou have been defeated..." << endl;
                cout << "Game over!" << endl;
                running = false;
                return;
            }
        } else if (choice == 2) {
            player->getInventory().useItem(*player);
        } else if (choice == 3) {
            cout << "You run away!" << endl;
            return;
        }
    }
}

void Game::bossEncounter() {
    Boss boss = bossManager.getRandomBoss(player->getLevel());
    
    ConsoleUI::clearScreen();
    ConsoleUI::printHeader("!!! BOSS ENCOUNTER !!!");
    ConsoleUI::setColor(ConsoleUI::Color::RED, ConsoleUI::Color::BLACK);
    cout << "\nA legendary enemy appears: " << boss.getName() << "!" << endl;
    ConsoleUI::setColor(ConsoleUI::Color::WHITE, ConsoleUI::Color::BLACK);
    cout << "Level " << boss.getLevel() << " | HP: " << boss.getHP() << "/" << boss.getMaxHP() << endl;
    cout << "\nThis will be a tough battle..." << endl;
    cout << "\nPress Enter to begin...";
    cin.ignore();
    cin.get();
    
    while (player->isAlive() && boss.isAlive()) {
        cout << "\n--- Boss Fight ---" << endl;
        cout << "Your HP: " << player->getHP() << "/" << player->getMaxHP() << endl;
        cout << boss.getName() << " HP: " << boss.getHP() << "/" << boss.getMaxHP() << endl;
        cout << "\n1. Attack" << endl;
        cout << "2. Use Item" << endl;
        cout << "3. Attempt to Run Away (Low Chance)" << endl;
        cout << "Choice: ";
        
        int choice;
        cin >> choice;
        
        if (choice == 1) {
            int damage = player->attack();
            boss.takeDamage(damage);
            cout << "You deal " << damage << " damage to " << boss.getName() << "!" << endl;
            
            if (!boss.isAlive()) {
                cout << "\n*** VICTORY ***" << endl;
                cout << "You have defeated " << boss.getName() << "!" << endl;
                int xp = boss.getXPReward();
                int gold = boss.getGoldReward();
                player->gainExperience(xp);
                player->addGold(gold);
                cout << "You gained " << xp << " experience and " << gold << " gold!" << endl;
                
                // Boss always drops rare items
                Item drop = Item::generateRandomItem();
                cout << "You found a rare item: " << drop.getName() << "!" << endl;
                player->getInventory().addItem(drop);
                
                return;
            }
            
            // Boss attacks (more powerful)
            int bossDamage = boss.attack();
            player->takeDamage(bossDamage);
            cout << boss.getName() << " deals " << bossDamage << " devastating damage!" << endl;
            
            if (!player->isAlive()) {
                cout << "\nYou have been defeated by " << boss.getName() << "..." << endl;
                cout << "Game over!" << endl;
                running = false;
                return;
            }
        } else if (choice == 2) {
            player->getInventory().useItem(*player);
            
            // Boss still attacks after you use item
            int bossDamage = boss.attack();
            player->takeDamage(bossDamage);
            cout << boss.getName() << " attacks while you use an item for " << bossDamage << " damage!" << endl;
            
            if (!player->isAlive()) {
                cout << "\nYou have been defeated by " << boss.getName() << "..." << endl;
                cout << "Game over!" << endl;
                running = false;
                return;
            }
        } else if (choice == 3) {
            // Only 30% chance to escape from boss
            if (rand() % 100 < 30) {
                cout << "You managed to escape from " << boss.getName() << "!" << endl;
                return;
            } else {
                cout << "You failed to escape!" << endl;
                int bossDamage = boss.attack();
                player->takeDamage(bossDamage);
                cout << boss.getName() << " punishes your cowardice with " << bossDamage << " damage!" << endl;
                
                if (!player->isAlive()) {
                    cout << "\nYou have been defeated by " << boss.getName() << "..." << endl;
                    cout << "Games over!" << endl;
                    running = false;
                    return;
                }
            }
        }
    }
}

void Game::initializeTowns() {
    // Create Starting Village
    Town* village = new Town("Willowdale", 
        "A peaceful village surrounded by green fields. The perfect place to begin your journey.",
        TownType::STARTING_VILLAGE);
    
    NPC* elderNPC = new NPC("Elder Thomas", NPCType::QUEST_GIVER, "Willowdale");
    elderNPC->addDialogue("Tell me about this village", 
        "Willowdale has stood for generations. We're simple folk, but lately, dark forces threaten our peace.");
    elderNPC->addDialogue("Any work for an adventurer?", 
        "The forest to the east has become dangerous. Perhaps you could investigate?");
    elderNPC->setQuest("forest_investigation");
    
    NPC* merchantNPC = new NPC("Gareth the Merchant", NPCType::MERCHANT, "Willowdale");
    merchantNPC->addDialogue("What goods do you have?", 
        "I travel far and wide! Visit my shops for the finest weapons, armor, and potions!");
    merchantNPC->addDialogue("Tell me about your travels", 
        "I've been to the grand city of Ironhaven and the mysterious Desert Oasis. Each place has its wonders!");
    
    village->addNPC(elderNPC);
    village->addNPC(merchantNPC);
    towns.push_back(village);
    
    // Create Trading City
    Town* city = new Town("Ironhaven", 
        "A bustling metropolis of trade and commerce. The sounds of merchants and smiths fill the air.",
        TownType::TRADING_CITY);
    
    NPC* guardCaptain = new NPC("Captain Ironsides", NPCType::GUARD, "Ironhaven");
    guardCaptain->addDialogue("What threats face the city?", 
        "Bandits plague our trade routes. We could use someone skilled to deal with them.");
    guardCaptain->addDialogue("Tell me about Ironhaven", 
        "This city is the heart of trade in the realm. Goods from all corners flow through here.");
    guardCaptain->setQuest("bandit_threat");
    
    NPC* sage = new NPC("Sage Luminara", NPCType::SAGE, "Ironhaven");
    sage->addDialogue("Share your wisdom", 
        "Knowledge is power, young one. The ancient texts speak of great evil stirring in the north.");
    sage->addDialogue("What can you tell me about magic?", 
        "Magic flows through all things. Master it, and you master reality itself.");
    
    city->addNPC(guardCaptain);
    city->addNPC(sage);
    towns.push_back(city);
    
    // Create Mountain Fortress
    Town* fortress = new Town("Stonewatch Keep", 
        "An ancient fortress carved into the mountainside. Home to the realm's greatest warriors.",
        TownType::MOUNTAIN_FORTRESS);
    
    NPC* commander = new NPC("Commander Stoneheart", NPCType::GUARD, "Stonewatch Keep");
    commander->addDialogue("What is your mission?", 
        "We guard against the threats from the mountain depths. A dragon has been spotted nearby!");
    commander->addDialogue("Train me in combat", 
        "You have potential, warrior. Face the challenges ahead and prove your worth.");
    commander->setQuest("dragon_threat");
    
    fortress->addNPC(commander);
    towns.push_back(fortress);
    
    // Create Coastal Port
    Town* port = new Town("Seabreeze Harbor", 
        "A lively port town where sailors and merchants gather. The smell of salt air fills your lungs.",
        TownType::COASTAL_PORT);
    
    NPC* sailor = new NPC("Captain Saltbeard", NPCType::VILLAGER, "Seabreeze Harbor");
    sailor->addDialogue("Tell me tales of the sea", 
        "Arr! I've sailed to the edge of the world! There be monsters in the deep, mark me words!");
    sailor->addDialogue("Any dangers here?", 
        "Pirates have been raiding our ships. Someone needs to put an end to their captain!");
    
    port->addNPC(sailor);
    towns.push_back(port);
    
    // Create Desert Oasis
    Town* oasis = new Town("Mirage Haven", 
        "A rare oasis in the vast desert. Palm trees provide shade and cool water sustains life.",
        TownType::DESERT_OASIS);
    
    NPC* nomad = new NPC("Zahara the Wanderer", NPCType::SAGE, "Mirage Haven");
    nomad->addDialogue("What secrets does the desert hold?", 
        "The sands hide ancient tombs and forgotten magic. Only the brave discover the truth.");
    nomad->addDialogue("Tell me about the old ways", 
        "Long ago, a great civilization thrived here. Now only ruins and mysteries remain.");
    
    oasis->addNPC(nomad);
    towns.push_back(oasis);
}

void Game::visitTowns() {
    ConsoleUI::clearScreen();
    ConsoleUI::printHeader("=== TRAVEL ===");
    
    cout << "\nWhere would you like to travel?" << endl;
    for (size_t i = 0; i < towns.size(); i++) {
        cout << (i + 1) << ". " << towns[i]->getName() << endl;
    }
    cout << "0. Stay here" << endl;
    
    cout << "\nChoice: ";
    int choice;
    cin >> choice;
    
    if (choice > 0 && choice <= (int)towns.size()) {
        towns[choice - 1]->visit(*player);
    }
}

void Game::storyBossEncounter() {
    ConsoleUI::clearScreen();
    
    int chapter = (player->getLevel() / 10) + 1;
    if (chapter > 7) chapter = 7;
    
    Boss boss = bossManager.getStoryBoss(chapter, player->getLevel());
    
    ConsoleUI::printHeader("!!! STORY BOSS ENCOUNTER !!!");
    ConsoleUI::setColor(ConsoleUI::Color::RED, ConsoleUI::Color::BLACK);
    cout << "\nChapter " << chapter << " Boss: " << boss.getName() << endl;
    ConsoleUI::setColor(ConsoleUI::Color::WHITE, ConsoleUI::Color::BLACK);
    cout << "Level " << boss.getLevel() << " | HP: " << boss.getHP() << "/" << boss.getMaxHP() << endl;
    
    cout << "\nPress Enter to begin the battle...";
    cin.ignore();
    cin.get();
    
    // Use same boss combat logic
    while (boss.isAlive() && player->isAlive()) {
        ConsoleUI::clearScreen();
        ConsoleUI::printHeader("=== BOSS BATTLE ===");
        
        cout << "\n" << boss.getName() << endl;
        ConsoleUI::setColor(ConsoleUI::Color::RED, ConsoleUI::Color::BLACK);
        cout << "HP: " << boss.getHP() << "/" << boss.getMaxHP() << endl;
        ConsoleUI::setColor(ConsoleUI::Color::WHITE, ConsoleUI::Color::BLACK);
        
        cout << "\n" << player->getName() << " (Level " << player->getLevel() << ")" << endl;
        ConsoleUI::setColor(ConsoleUI::Color::GREEN, ConsoleUI::Color::BLACK);
        cout << "HP: " << player->getHP() << "/" << player->getMaxHP() << endl;
        ConsoleUI::setColor(ConsoleUI::Color::WHITE, ConsoleUI::Color::BLACK);
        
        cout << "\n1. Attack" << endl;
        cout << "2. Use Item" << endl;
        cout << "3. Attempt Escape" << endl;
        cout << "Choice: ";
        
        int choice;
        cin >> choice;
        
        if (choice == 1) {
            int damage = player->attack();
            boss.takeDamage(damage);
            cout << "\nYou deal " << damage << " damage to " << boss.getName() << "!" << endl;
            
            if (!boss.isAlive()) {
                ConsoleUI::printSuccess("\nVictory! You have defeated " + boss.getName() + "!");
                cout << "Chapter " << chapter << " Complete!" << endl;
                player->gainExperience(boss.getXPReward());
                player->addGold(boss.getGoldReward());
                cout << "Gained " << boss.getGoldReward() << " gold!" << endl;
                cout << "\nPress Enter to continue...";
                cin.ignore();
                cin.get();
                return;
            }
            
            int bossDamage = boss.attack();
            player->takeDamage(bossDamage);
            cout << boss.getName() << " retaliates for " << bossDamage << " damage!" << endl;
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
            
            if (!player->isAlive()) {
                ConsoleUI::printError("\nYou have been defeated by " + boss.getName() + "...");
                cout << "Game over!" << endl;
                running = false;
                return;
            }
        } else if (choice == 2) {
            player->getInventory().useItem(*player);
            
            int bossDamage = boss.attack();
            player->takeDamage(bossDamage);
            cout << boss.getName() << " attacks while you use an item for " << bossDamage << " damage!" << endl;
            
            if (!player->isAlive()) {
                ConsoleUI::printError("\nYou have been defeated by " + boss.getName() + "...");
                running = false;
                return;
            }
        } else if (choice == 3) {
            ConsoleUI::printWarning("You cannot escape from a story boss!");
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
    }
}
