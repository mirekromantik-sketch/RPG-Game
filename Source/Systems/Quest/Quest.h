#ifndef QUEST_H
#define QUEST_H

#include <string>

enum class QuestStatus {
    ACTIVE,
    COMPLETED,
    FAILED
};

class Quest {
private:
    std::string title;
    std::string description;
    int progress;
    int goal;
    int rewardXP;
    QuestStatus status;

public:
    Quest(std::string title, std::string description, int goal, int rewardXP);
    
    void updateProgress(int amount);
    void complete();
    
    std::string getTitle() const { return title; }
    std::string getDescription() const { return description; }
    int getProgress() const { return progress; }
    int getGoal() const { return goal; }
    QuestStatus getStatus() const { return status; }
    int getRewardXP() const { return rewardXP; }
};

#endif
