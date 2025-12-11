#ifndef ENEMY_H
#define ENEMY_H

#include <string>

class Enemy {
private:
    std::string name;
    int level;
    int hp;
    int maxHP;
    int strength;
    int defense;
    int xpReward;
    int goldReward;

public:
    Enemy(std::string name, int level, int hp, int strength, int defense);

    static Enemy generateRandomEnemy(int playerLevel);
    
    int attack();
    void takeDamage(int damage);
    
    bool isAlive() const { return hp > 0; }
    std::string getName() const { return name; }
    int getHP() const { return hp; }
    int getMaxHP() const { return maxHP; }
    int getXPReward() const { return xpReward; }
    int getGoldReward() const { return goldReward; }
};



#endif
