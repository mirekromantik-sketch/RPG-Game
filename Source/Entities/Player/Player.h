#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "../../Systems/Inventory/Inventory.h"

class Player {
private:
    std::string name;
    int level;
    int experience;
    int experienceToNextLevel;
    
    // Stats
    int hp;
    int maxHP;
    int strength;
    int magic;
    int defense;
    int speed;
    
    int gold;
    Inventory inventory;

public:
    Player(std::string name, int classType);
    
    void showStats();
    int attack();
    void takeDamage(int damage);
    void heal(int amount);
    void gainExperience(int xp);
    void levelUp();
    void rest();
    
    bool isAlive() const { return hp > 0; }
    int getHP() const { return hp; }
    int getMaxHP() const { return maxHP; }
    int getLevel() const { return level; }
    void addGold(int amount) { gold += amount; }
    int getGold() const { return gold; }
    Inventory& getInventory() { return inventory; }
};

#endif
