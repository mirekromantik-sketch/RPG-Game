#ifndef BOSS_MANAGER_H
#define BOSS_MANAGER_H

#include "../../Entities/Enemies/boss.h"
#include <vector>
#include <string>

enum class BossType {
    DRAGON,
    DEMON_LORD,
    ANCIENT_LICH,
    GIANT_BEAST,
    DARK_KNIGHT,
    VOID_ENTITY,
    CORRUPTED_GUARDIAN
};

class BossManager {
private:
    std::vector<Boss> availableBosses;
    
public:
    BossManager();
    
    Boss createBoss(BossType type, int playerLevel);
    Boss getRandomBoss(int playerLevel);
    Boss getStoryBoss(int chapter, int playerLevel);
    
    static std::string getBossTitle(BossType type);
    static std::string getBossDescription(BossType type);
};

#endif
