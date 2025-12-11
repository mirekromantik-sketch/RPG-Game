#include "Enemy.h"
#include <cstdlib>

using namespace std;

Enemy::Enemy(string name, int level, int hp, int strength, int defense):
    name(name), 
    level(level), 
    hp(hp), 
    maxHP(hp), 
    strength(strength), 
    defense(defense) {
    xpReward = level * 25;
    goldReward = level * 10 + (rand() % 20);
}

Enemy Enemy::generateRandomEnemy(int playerLevel) {
    int enemyLevel = playerLevel + (rand() % 3) - 1;
    if (enemyLevel < 1) enemyLevel = 1;
    
    string names[] = {"Goblin", "Skeleton", "Wolf", "Orc", "Bandit", "Spider", "Zombie"};
    string name = names[rand() % 7];
    
    int hp = 50 + (enemyLevel * 15);
    int strength = 8 + (enemyLevel * 2);
    int defense = 5 + enemyLevel;
    
    return Enemy(name, enemyLevel, hp, strength, defense);
}


int Enemy::attack() {
    int damage = strength + (rand() % 4);
    return damage;
}

void Enemy::takeDamage(int damage) {
    int actualDamage = damage - (defense / 2);
    if (actualDamage < 1) actualDamage = 1;
    hp -= actualDamage;
    if (hp < 0) hp = 0;
}
