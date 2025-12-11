#ifndef TALENTS_H
#define TALENTS_H

#include <string>
#include <vector>
#include <map>

// Talent node represents a single talent in the tree
struct TalentNode {
    std::string name;
    std::string description;
    int maxRank;
    int currentRank;
    int cost;  // Points needed per rank
    std::vector<std::string> prerequisites;  // Names of required talents
    
    TalentNode() : maxRank(1), currentRank(0), cost(1) {}
    TalentNode(std::string n, std::string desc, int max, int c) 
        : name(n), description(desc), maxRank(max), currentRank(0), cost(c) {}
    
    bool isMaxed() const { return currentRank >= maxRank; }
    bool canUpgrade() const { return currentRank < maxRank; }
};

// TalentTree manages all talents for a specific class
class TalentTree {
private:
    std::string className;
    std::map<std::string, TalentNode> talents;
    int availablePoints;

public:
    TalentTree();
    TalentTree(std::string className);
    
    void initializeWarriorTree();
    void initializeMageTree();
    void initializeRogueTree();
    void initializeClericTree();
    void initializeRangerTree();
    
    bool upgradeTalent(const std::string& talentName);
    void addPoints(int points);
    void displayTalents() const;
    void autoAllocate();
    bool hasTalent(const std::string& talentName) const;
    int getTalentRank(const std::string& talentName) const;
    int getAvailablePoints() const { return availablePoints; }
    const std::map<std::string, TalentNode>& getTalents() const { return talents; }
    void setAvailablePoints(int points) { availablePoints = points; }
    void setTalentRank(const std::string& talentName, int rank);
    
private:
    bool checkPrerequisites(const TalentNode& talent) const;
};

#endif
