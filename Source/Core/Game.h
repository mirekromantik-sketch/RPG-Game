#ifndef GAME_H
#define GAME_H

#include "../Entities/Player/Player.h"
#include "../Systems/Quest/QuestManager.h"
#include "../Systems/Town/Town.h"
#include "../Systems/Boss/BossManager.h"
#include "SaveManager.h"
#include <vector>

class Game {
private:
    Player* player;
    QuestManager questManager;
    SaveManager saveManager;
    BossManager bossManager;
    std::vector<Town*> towns;
    bool running;
    
    void initializeTowns();
    void initializeNPCs();

public:
    Game();
    ~Game();
    void run();
    void showStartMenu();
    void showMainMenu();
    void characterCreation();
    void exploreWorld();
    void showInventory();
    void showQuests();
    void visitShops();
    void visitTowns();
    void combat();
    void bossEncounter();
    void storyBossEncounter();
    void saveGame();
    void loadGame();
    void loadSaveMenu();
    void deleteSaveMenu();
};

#endif
