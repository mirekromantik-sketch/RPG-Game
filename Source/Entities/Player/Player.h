#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "../../Systems/Inventory/Inventory.h"
#include "../../Systems/Talent Points/Talents.h"
#include "../../Systems/Talent Points/Points.h"

enum class PlayerClass {
    WARRIOR,
    MAGE,
    ROGUE,
    CLERIC,
    RANGER
};

enum class Origin {
    HUMAN,
    ELF,
    DWARF,
    ORC,
    HALFLING
};

class Player {
private:
    std::string name;
    int level;
    int experience;
    int experienceToNextLevel;
    
    // Stats
    int hp;
    int maxHP;
    int strength;
    int magic;
    int defense;
    int speed;
    
    int gold;
    Inventory inventory;
    
    // Equipment slots
    Item* equippedWeapon;
    Item* equippedArmor;
    
    // New systems
    PlayerClass playerClass;
    Origin origin;
    TalentTree talentTree;
    AttributePoints attributePoints;
    std::string className;
    std::string originName;

public:
    Player(std::string name, int classChoice, int originChoice);
    
    void showStats();
    int attack();
    void takeDamage(int damage);
    void heal(int amount);
    void gainExperience(int xp);
    void levelUp();
    void rest();
    
    // New methods
    void addStatBonus(AttributeType type, int amount);
    void openTalentTree();
    void distributeAttributePoints();
    
    // Equipment methods
    bool equipItem(Item* item);
    void unequipWeapon();
    void unequipArmor();
    void showEquipment();
    bool canEquip(const Item* item) const;
    int getTotalStrength() const;
    int getTotalMagic() const;
    int getTotalDefense() const;
    int getTotalSpeed() const;
    
    // Getters
    std::string getName() const { return name; }
    std::string getClassName() const { return className; }
    std::string getOriginName() const { return originName; }
    TalentTree& getTalentTree() { return talentTree; }
    const TalentTree& getTalentTree() const { return talentTree; }
    AttributePoints& getAttributePoints() { return attributePoints; }
    const AttributePoints& getAttributePoints() const { return attributePoints; }
    
    bool isAlive() const { return hp > 0; }
    int getHP() const { return hp; }
    int getMaxHP() const { return maxHP; }
    int getLevel() const { return level; }
    int getExperience() const { return experience; }
    int getExperienceToNextLevel() const { return experienceToNextLevel; }
    int getStrength() const { return strength; }
    int getMagic() const { return magic; }
    int getDefense() const { return defense; }
    int getSpeed() const { return speed; }
    void addGold(int amount) { gold += amount; }
    int getGold() const { return gold; }
    Inventory& getInventory() { return inventory; }
    const Inventory& getInventory() const { return inventory; }
    Item* getEquippedWeapon() const { return equippedWeapon; }
    Item* getEquippedArmor() const { return equippedArmor; }
    
    // Setters for loading saves
    void setLevel(int lvl) { level = lvl; }
    void setExperience(int exp) { experience = exp; }
    void setHP(int health) { hp = health; }
    void setMaxHP(int maxHealth) { maxHP = maxHealth; }
    void setStrength(int str) { strength = str; }
    void setMagic(int mag) { magic = mag; }
    void setDefense(int def) { defense = def; }
    void setSpeed(int spd) { speed = spd; }
    void setGold(int g) { gold = g; }
};

#endif
