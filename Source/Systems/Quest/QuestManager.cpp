#include "QuestManager.h"
#include <iostream>

using namespace std;

void QuestManager::addQuest(string title, string description, int goal) {
    quests.push_back(Quest(title, description, goal, goal * 50));
    cout << "\nNew Quest: " << title << endl;
    cout << description << endl;
}

void QuestManager::updateProgress(string title, int amount) {
    for (auto& quest : quests) {
        if (quest.getTitle() == title && quest.getStatus() == QuestStatus::ACTIVE) {
            quest.updateProgress(amount);
            break;
        }
    }
}

void QuestManager::displayQuests() const {
    cout << "\n=== Quest Log ===" << endl;
    
    if (quests.empty()) {
        cout << "No quests available." << endl;
        return;
    }
    
    for (const auto& quest : quests) {
        cout << "\n" << quest.getTitle();
        
        if (quest.getStatus() == QuestStatus::ACTIVE) {
            cout << " [ACTIVE]" << endl;
            cout << quest.getDescription() << endl;
            cout << "Progress: " << quest.getProgress() << "/" << quest.getGoal() << endl;
        } else if (quest.getStatus() == QuestStatus::COMPLETED) {
            cout << " [COMPLETED]" << endl;
        }
    }
}
