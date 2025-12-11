#include "boss.h"
#include <cstdlib>

using namespace std;

Boss::Boss(string name, int level, int hp, int strength, int defense):
    name(name), 
    level(level), 
    hp(hp), 
    maxHP(hp), 
    strength(strength), 
    defense(defense) {
    xpReward = level * 50;
    goldReward = level * 10 + (rand() % 20);
}

Boss Boss::generateRandomBoss(int playerLevel) {
    int enemyLevel;

    // Difficulty scaling based on player level
    if (playerLevel >= 30) {
        enemyLevel = playerLevel + 20;
    }
    else if (playerLevel >= 20) {
        enemyLevel = playerLevel + 15;
    }
    else if (playerLevel >= 10) {
        enemyLevel = playerLevel + 10;
    }
    else {
        enemyLevel = playerLevel + 5;
    }

    if (enemyLevel < 1) enemyLevel = 1;

    // Random boss names
    string names[] = {
        "Malaker the Corruptor", "The Black Emperor", "Ironjaw Behemoth",
        "Frostvein", "Nightshade Overlord", "Malice, the World-Eater", "Void Serpent"
    };
    string name = names[rand() % 7];

    // Stats scaled with enemyLevel
    int hp     = 100 + (enemyLevel * (playerLevel >= 30 ? 25 : playerLevel >= 20 ? 20 : playerLevel >= 10 ? 15 : 10));
    int strength = 6 + (enemyLevel * (playerLevel >= 30 ? 5 : playerLevel >= 20 ? 4 : playerLevel >= 10 ? 3 : 2));
    int defense  = 5 + (enemyLevel * (playerLevel >= 30 ? 5 : playerLevel >= 20 ? 4 : playerLevel >= 10 ? 3 : 2));

    return Boss(name, enemyLevel, hp, strength, defense);
}


int Boss::attack() {
    int damage = strength + (rand() % 4);
    return damage;
}

void Boss::takeDamage(int damage) {
    int actualDamage = damage - (defense / 2);
    if (actualDamage < 1) actualDamage = 1;
    hp -= actualDamage;
    if (hp < 0) hp = 0;
}
