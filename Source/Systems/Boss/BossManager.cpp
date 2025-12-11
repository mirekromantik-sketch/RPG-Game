#include "BossManager.h"
#include <cstdlib>

using namespace std;

BossManager::BossManager() {}

string BossManager::getBossTitle(BossType type) {
    switch (type) {
        case BossType::DRAGON: return "Ancient Dragon";
        case BossType::DEMON_LORD: return "Demon Lord";
        case BossType::ANCIENT_LICH: return "Ancient Lich";
        case BossType::GIANT_BEAST: return "Colossal Beast";
        case BossType::DARK_KNIGHT: return "Dark Knight Commander";
        case BossType::VOID_ENTITY: return "Void Entity";
        case BossType::CORRUPTED_GUARDIAN: return "Corrupted Guardian";
        default: return "Unknown Boss";
    }
}

string BossManager::getBossDescription(BossType type) {
    switch (type) {
        case BossType::DRAGON: 
            return "A massive dragon with scales harder than steel and breath that melts stone.";
        case BossType::DEMON_LORD: 
            return "A demon lord from the depths of the abyss, wielding unholy magic.";
        case BossType::ANCIENT_LICH: 
            return "An undead sorcerer who has mastered death itself.";
        case BossType::GIANT_BEAST: 
            return "A monstrous creature of immense size and strength.";
        case BossType::DARK_KNIGHT: 
            return "A fallen knight consumed by darkness and rage.";
        case BossType::VOID_ENTITY: 
            return "A being from beyond reality, incomprehensible and terrifying.";
        case BossType::CORRUPTED_GUARDIAN: 
            return "Once a protector, now twisted by dark magic.";
        default: 
            return "A powerful enemy.";
    }
}

Boss BossManager::createBoss(BossType type, int playerLevel) {
    string prefix[] = {"Dreadful", "Infernal", "Cursed", "Eternal", "Malevolent", "Ruthless"};
    string suffix[] = {"of Doom", "the Destroyer", "the Merciless", "Bane of Heroes", "the Immortal"};
    
    string baseName = getBossTitle(type);
    string fullName = prefix[rand() % 6] + " " + baseName + " " + suffix[rand() % 5];
    
    int levelBoost = 5 + (playerLevel / 5);
    int bossLevel = playerLevel + levelBoost;
    
    // Type-specific stats
    int hpMultiplier = 15;
    int strMultiplier = 3;
    int defMultiplier = 2;
    
    switch (type) {
        case BossType::DRAGON:
            hpMultiplier = 20;
            strMultiplier = 4;
            defMultiplier = 4;
            break;
        case BossType::DEMON_LORD:
            hpMultiplier = 18;
            strMultiplier = 5;
            defMultiplier = 2;
            break;
        case BossType::ANCIENT_LICH:
            hpMultiplier = 12;
            strMultiplier = 6;
            defMultiplier = 3;
            break;
        case BossType::GIANT_BEAST:
            hpMultiplier = 25;
            strMultiplier = 4;
            defMultiplier = 1;
            break;
        case BossType::DARK_KNIGHT:
            hpMultiplier = 16;
            strMultiplier = 4;
            defMultiplier = 5;
            break;
        case BossType::VOID_ENTITY:
            hpMultiplier = 15;
            strMultiplier = 7;
            defMultiplier = 2;
            break;
        case BossType::CORRUPTED_GUARDIAN:
            hpMultiplier = 18;
            strMultiplier = 3;
            defMultiplier = 4;
            break;
    }
    
    int hp = 100 + (bossLevel * hpMultiplier);
    int strength = 8 + (bossLevel * strMultiplier);
    int defense = 5 + (bossLevel * defMultiplier);
    
    return Boss(fullName, bossLevel, hp, strength, defense);
}

Boss BossManager::getRandomBoss(int playerLevel) {
    BossType types[] = {
        BossType::DRAGON, BossType::DEMON_LORD, BossType::ANCIENT_LICH,
        BossType::GIANT_BEAST, BossType::DARK_KNIGHT, BossType::VOID_ENTITY,
        BossType::CORRUPTED_GUARDIAN
    };
    
    BossType randomType = types[rand() % 7];
    return createBoss(randomType, playerLevel);
}

Boss BossManager::getStoryBoss(int chapter, int playerLevel) {
    BossType chapterBoss;
    
    switch (chapter) {
        case 1: chapterBoss = BossType::CORRUPTED_GUARDIAN; break;
        case 2: chapterBoss = BossType::DARK_KNIGHT; break;
        case 3: chapterBoss = BossType::GIANT_BEAST; break;
        case 4: chapterBoss = BossType::ANCIENT_LICH; break;
        case 5: chapterBoss = BossType::DEMON_LORD; break;
        case 6: chapterBoss = BossType::DRAGON; break;
        case 7: chapterBoss = BossType::VOID_ENTITY; break;
        default: chapterBoss = BossType::CORRUPTED_GUARDIAN; break;
    }
    
    return createBoss(chapterBoss, playerLevel + (chapter * 5));
}
