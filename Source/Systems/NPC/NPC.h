#ifndef NPC_H
#define NPC_H

#include <string>
#include <vector>

enum class NPCType {
    MERCHANT,
    QUEST_GIVER,
    INNKEEPER,
    GUARD,
    VILLAGER,
    SAGE
};

class NPC {
private:
    std::string name;
    NPCType type;
    std::string location;
    std::vector<std::string> dialogueOptions;
    std::vector<std::string> responses;
    int dialogueState;
    bool hasQuest;
    std::string questId;

public:
    NPC(std::string name, NPCType type, std::string location);
    
    void addDialogue(const std::string& option, const std::string& response);
    void talk();
    void showDialogueMenu();
    
    std::string getName() const { return name; }
    NPCType getType() const { return type; }
    std::string getLocation() const { return location; }
    bool getHasQuest() const { return hasQuest; }
    void setQuest(const std::string& questId);
    std::string getQuestId() const { return questId; }
};

#endif
