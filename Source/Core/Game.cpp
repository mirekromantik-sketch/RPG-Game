#include "Game.h"
#include "../Entities/Enemies/Enemy.h"
#include "../Entities/Enemies/boss.h"
#include <iostream>
#include <cstdlib>

using namespace std;

Game::Game() : player(nullptr), running(true) {}

Game::~Game() {
    if (player) delete player;
}

void Game::run() {
    cout << "=== Welcome to RPG GAME ===" << endl;
    characterCreation();
    
    while (running) {
        showMainMenu();
    }
}

void Game::showMainMenu() {
    cout << "\n=== Main Menu ===" << endl;
    cout << "1. Show Character" << endl;
    cout << "2. Explore World" << endl;
    cout << "3. Show Inventory" << endl;
    cout << "4. Show Quests" << endl;
    cout << "5. Rest (Restore HP)" << endl;
    cout << "6. Exit Game" << endl;
    cout << "Choose an option: ";
    
    int choice;
    cin >> choice;
    
    switch (choice) {
        case 1:
            player->showStats();
            break;
        case 2:
            exploreWorld();
            break;
        case 3:
            showInventory();
            break;
        case 4:
            showQuests();
            break;
        case 5:
            player->rest();
            cout << "You rest and restore health!" << endl;
            break;
        case 6:
            running = false;
            cout << "Thank you for playing!" << endl;
            break;
        default:
            cout << "Invalid choice!" << endl;
    }
}

void Game::characterCreation() {
    cout << "\n=== Character Creation ===" << endl;
    cout << "Enter your character's name: ";
    string name;
    cin.ignore();
    getline(cin, name);

    cout << "\nChoose your origin:" << endl;
    cout << "1. Human" << endl;
    cout << "2. Elf" << endl;
    cout << "3. Dwarf" << endl;
    cout << "Choice: ";
    int originChoice;
    cin >> originChoice;

    
    cout << "\nChoose a class:" << endl;
    cout << "1. Warrior (High HP, High Strength)" << endl;
    cout << "2. Mage (High Magic, Low HP)" << endl;
    cout << "3. Rogue (Balanced, High Speed)" << endl;
    cout << "Choice: ";
    
    int classChoice;
    cin >> classChoice;
    
    player = new Player(name, originChoice);
    player->showStats();
    
    // Add starting quest
    questManager.addQuest("First Steps", "Kill 3 enemies", 100);
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
    player->getInventory().display();
}

void Game::showQuests() {
    questManager.displayQuests();
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
    Boss boss = Boss::generateRandomBoss(player->getLevel());
    
    cout << "\n*** BOSS FIGHT ***" << endl;
    cout << "A legendary enemy appears: " << boss.getName() << "!" << endl;
    cout << "Boss HP: " << boss.getHP() << endl;
    cout << "This will be a tough battle..." << endl;
    
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
