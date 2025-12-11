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
    int enemyLevel = playerLevel + 5;
    if (enemyLevel < 1) enemyLevel = 1;
    
    string names[] = {"Malaker the Corruptor", "The Black Emperor", "Ironjaw Behemoth", "Frostvein", "Nightshade Overlord", "Malice, the World-Eater", "Void Serpent"};
    string name = names[rand() % 7];
    
    int hp = 100 + (enemyLevel * 10);
    int strength = 6 + (enemyLevel * 2);
    int defense = 5 + (enemyLevel * 2);
    
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
