#ifndef GAME_H
#define GAME_H

#include "../Entities/Player/Player.h"
#include "../Systems/Quest/QuestManager.h"

class Game {
private:
    Player* player;
    QuestManager questManager;
    bool running;

public:
    Game();
    ~Game();
    void run();
    void showMainMenu();
    void characterCreation();
    void exploreWorld();
    void showInventory();
    void showQuests();
    void combat();
    void bossEncounter();
};

#endif
