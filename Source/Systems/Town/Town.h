#ifndef TOWN_H
#define TOWN_H

#include <string>
#include <vector>
#include "../NPC/NPC.h"

class Player;

enum class TownType {
    STARTING_VILLAGE,
    TRADING_CITY,
    MOUNTAIN_FORTRESS,
    COASTAL_PORT,
    DESERT_OASIS,
    FOREST_HAVEN
};

class Town {
private:
    std::string name;
    std::string description;
    TownType type;
    std::vector<NPC*> npcs;
    bool hasWeaponShop;
    bool hasArmorShop;
    bool hasPotionShop;
    bool hasBackpackShop;
    bool hasInn;
    int innCost;

public:
    Town(std::string name, std::string description, TownType type);
    ~Town();
    
    void addNPC(NPC* npc);
    void visit(Player& player);
    void showTownMenu(Player& player);
    void talkToNPCs();
    void restAtInn(Player& player);
    
    std::string getName() const { return name; }
    std::string getDescription() const { return description; }
    TownType getType() const { return type; }
};

#endif
