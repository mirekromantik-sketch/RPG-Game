#ifndef BOSS_H
#define BOSS_H

#include <string>

class Boss {
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
    Boss(std::string name, int level, int hp, int strength, int defense);

    static Boss generateRandomBoss(int playerLevel);
    
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
