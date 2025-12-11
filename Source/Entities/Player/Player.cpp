#include "Player.h"
#include <iostream>

using namespace std;

Player::Player(string name, int classType) 
    : name(name), level(1), experience(0), experienceToNextLevel(100), gold(50) {
    
    switch (classType) {
        case 1: // Warrior
            maxHP = 120;
            strength = 15;
            magic = 5;
            defense = 12;
            speed = 8;
            break;
        case 2: // Mage
            maxHP = 80;
            strength = 6;
            magic = 18;
            defense = 6;
            speed = 10;
            break;
        case 3: // Rogue
            maxHP = 100;
            strength = 12;
            magic = 8;
            defense = 8;
            speed = 15;
            break;
        default:
            maxHP = 100;
            strength = 10;
            magic = 10;
            defense = 10;
            speed = 10;
    }
    
    hp = maxHP;
    
    // Add starting items
    inventory.addItem(Item("Health Potion", "Restores 50 HP", ItemType::CONSUMABLE, 50));
    inventory.addItem(Item("Health Potion", "Restores 50 HP", ItemType::CONSUMABLE, 50));
}

void Player::showStats() {
    cout << "\n=== Character Stats ===" << endl;
    cout << "Name: " << name << endl;
    cout << "Level: " << level << endl;
    cout << "XP: " << experience << "/" << experienceToNextLevel << endl;
    cout << "HP: " << hp << "/" << maxHP << endl;
    cout << "Strength: " << strength << endl;
    cout << "Magic: " << magic << endl;
    cout << "Defense: " << defense << endl;
    cout << "Speed: " << speed << endl;
    cout << "Gold: " << gold << endl;
}

int Player::attack() {
    int damage = strength + (rand() % 5);
    return damage;
}

void Player::takeDamage(int damage) {
    int actualDamage = damage - (defense / 2);
    if (actualDamage < 1) actualDamage = 1;
    hp -= actualDamage;
    if (hp < 0) hp = 0;
}

void Player::heal(int amount) {
    hp += amount;
    if (hp > maxHP) hp = maxHP;
}

void Player::gainExperience(int xp) {
    experience += xp;
    cout << "Gained " << xp << " experience!" << endl;
    
    while (experience >= experienceToNextLevel) {
        levelUp();
    }
}

void Player::levelUp() {
    level++;
    experience -= experienceToNextLevel;
    experienceToNextLevel = level * 100;
    
    // Increase stats
    maxHP += 20;
    hp = maxHP;
    strength += 3;
    magic += 3;
    defense += 2;
    speed += 2;
    
    cout << "\n*** LEVEL UP! You are now level " << level << " ***" << endl;
    cout << "All stats have increased!" << endl;
}

void Player::rest() {
    hp = maxHP;
}
