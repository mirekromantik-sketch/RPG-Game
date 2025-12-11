#ifndef QUESTMANAGER_H
#define QUESTMANAGER_H

#include "Quest.h"
#include <vector>

class QuestManager {
private:
    std::vector<Quest> quests;

public:
    void addQuest(std::string title, std::string description, int goal);
    void updateProgress(std::string title, int amount);
    void displayQuests() const;
};

#endif
