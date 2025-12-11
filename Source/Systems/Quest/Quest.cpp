#include "Quest.h"
#include <iostream>

using namespace std;

Quest::Quest(string title, string description, int goal, int rewardXP): 
    title(title), 
    description(description), 
    goal(goal), 
    rewardXP(rewardXP),
    progress(0), 
    status(QuestStatus::ACTIVE) {}

void Quest::updateProgress(int amount) {
    if (status != QuestStatus::ACTIVE) return;
    
    progress += amount;
    
    cout << "Quest Progress: " << title << " (" << progress << "/" << goal << ")" << endl;
    
    if (progress >= goal) {
        complete();
    }
}

void Quest::complete() {
    status = QuestStatus::COMPLETED;
    cout << "\n*** QUEST COMPLETED: " << title << " ***" << endl;
    cout << "Reward: " << rewardXP << " XP!" << endl;
}
