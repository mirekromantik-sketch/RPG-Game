#include "Player.h"
#include "../../Core/ConsoleUI.h"
#include <iostream>

using namespace std;

Player::Player(string name, int classChoice, int originChoice) 
    : name(name), level(1), experience(0), experienceToNextLevel(100), gold(100) {
    
    // Set origin and apply bonuses
    switch (originChoice) {
        case 1: // Human
            origin = Origin::HUMAN;
            originName = "Human";
            // Balanced, +10% gold gain (handled elsewhere)
            maxHP = 100;
            strength = 10;
            magic = 10;
            defense = 10;
            speed = 10;
            break;
        case 2: // Elf
            origin = Origin::ELF;
            originName = "Elf";
            // High magic and speed, lower HP
            maxHP = 85;
            strength = 8;
            magic = 14;
            defense = 8;
            speed = 13;
            break;
        case 3: // Dwarf
            origin = Origin::DWARF;
            originName = "Dwarf";
            // High HP and defense, lower speed
            maxHP = 115;
            strength = 12;
            magic = 6;
            defense = 14;
            speed = 6;
            break;
        case 4: // Orc
            origin = Origin::ORC;
            originName = "Orc";
            // High strength, lower magic
            maxHP = 110;
            strength = 15;
            magic = 4;
            defense = 11;
            speed = 8;
            break;
        case 5: // Halfling
            origin = Origin::HALFLING;
            originName = "Halfling";
            // High speed and evasion, lower HP
            maxHP = 80;
            strength = 9;
            magic = 11;
            defense = 7;
            speed = 16;
            break;
        default:
            origin = Origin::HUMAN;
            originName = "Human";
            maxHP = 100;
            strength = 10;
            magic = 10;
            defense = 10;
            speed = 10;
    }
    
    // Apply class bonuses on top of origin stats
    switch (classChoice) {
        case 1: // Warrior
            playerClass = PlayerClass::WARRIOR;
            className = "Warrior";
            maxHP += 20;
            strength += 5;
            defense += 3;
            break;
        case 2: // Mage
            playerClass = PlayerClass::MAGE;
            className = "Mage";
            maxHP -= 20;
            magic += 8;
            speed += 2;
            break;
        case 3: // Rogue
            playerClass = PlayerClass::ROGUE;
            className = "Rogue";
            strength += 3;
            speed += 6;
            break;
        case 4: // Cleric
            playerClass = PlayerClass::CLERIC;
            className = "Cleric";
            maxHP += 10;
            magic += 5;
            defense += 3;
            break;
        case 5: // Ranger
            playerClass = PlayerClass::RANGER;
            className = "Ranger";
            maxHP += 5;
            strength += 4;
            speed += 3;
            break;
        default:
            playerClass = PlayerClass::WARRIOR;
            className = "Warrior";
            maxHP += 20;
            strength += 5;
            defense += 3;
    }
    
    hp = maxHP;
    
    // Initialize equipment slots
    equippedWeapon = nullptr;
    equippedArmor = nullptr;
    
    // Initialize talent tree for the class
    talentTree = TalentTree(className);
    
    // Add starting items
    inventory.addItem(Item("Health Potion", "Restores 50 HP", ItemType::CONSUMABLE, 50));
    inventory.addItem(Item("Health Potion", "Restores 50 HP", ItemType::CONSUMABLE, 50));
}

void Player::showStats() {
    ConsoleUI::printHeader("CHARACTER STATS");
    
    ConsoleUI::printStat("Name", name);
    ConsoleUI::printColoredText("  Origin: ", ConsoleUI::MAGENTA);
    cout << originName;
    ConsoleUI::printColoredText("  |  Class: ", ConsoleUI::GREEN);
    cout << className << "\n";
    
    ConsoleUI::printSeparator('-', 60);
    
    ConsoleUI::printColoredText("  Level: ", ConsoleUI::CYAN);
    ConsoleUI::printColoredText(to_string(level), ConsoleUI::YELLOW);
    ConsoleUI::printColoredText("  |  XP: ", ConsoleUI::CYAN);
    cout << experience << "/" << experienceToNextLevel << "\n";
    
    ConsoleUI::printSeparator('-', 60);
    
    ConsoleUI::printColoredText("  HP: ", ConsoleUI::RED);
    cout << hp << "/" << maxHP << "\n";
    ConsoleUI::printColoredText("  Strength: ", ConsoleUI::RED);
    cout << strength;
    if (getTotalStrength() != strength) {
        ConsoleUI::setColor(ConsoleUI::Color::GREEN, ConsoleUI::Color::BLACK);
        cout << " (+" << (getTotalStrength() - strength) << " from equipment)";
        ConsoleUI::setColor(ConsoleUI::Color::WHITE, ConsoleUI::Color::BLACK);
    }
    cout << "\n";
    ConsoleUI::printColoredText("  Magic: ", ConsoleUI::BLUE);
    cout << magic;
    if (getTotalMagic() != magic) {
        ConsoleUI::setColor(ConsoleUI::Color::GREEN, ConsoleUI::Color::BLACK);
        cout << " (+" << (getTotalMagic() - magic) << " from equipment)";
        ConsoleUI::setColor(ConsoleUI::Color::WHITE, ConsoleUI::Color::BLACK);
    }
    cout << "\n";
    ConsoleUI::printColoredText("  Defense: ", ConsoleUI::YELLOW);
    cout << defense;
    if (getTotalDefense() != defense) {
        ConsoleUI::setColor(ConsoleUI::Color::GREEN, ConsoleUI::Color::BLACK);
        cout << " (+" << (getTotalDefense() - defense) << " from equipment)";
        ConsoleUI::setColor(ConsoleUI::Color::WHITE, ConsoleUI::Color::BLACK);
    }
    cout << "\n";
    ConsoleUI::printColoredText("  Speed: ", ConsoleUI::GREEN);
    cout << speed;
    if (getTotalSpeed() != speed) {
        ConsoleUI::setColor(ConsoleUI::Color::GREEN, ConsoleUI::Color::BLACK);
        cout << " (+" << (getTotalSpeed() - speed) << " from equipment)";
        ConsoleUI::setColor(ConsoleUI::Color::WHITE, ConsoleUI::Color::BLACK);
    }
    cout << "\n";
    
    ConsoleUI::printSeparator('-', 60);
    
    ConsoleUI::printColoredText("  Gold: ", ConsoleUI::YELLOW);
    cout << gold << "\n";
    ConsoleUI::printColoredText("  Attribute Points: ", ConsoleUI::CYAN);
    cout << attributePoints.getAvailablePoints() << "\n";
    ConsoleUI::printColoredText("  Talent Points: ", ConsoleUI::MAGENTA);
    cout << talentTree.getAvailablePoints() << "\n";
}

int Player::attack() {
    int totalStr = getTotalStrength();
    int totalMag = getTotalMagic();
    int baseDamage = totalStr + (rand() % 5);
    
    // Apply talent bonuses
    if (className == "Warrior" && talentTree.hasTalent("Power Strike")) {
        baseDamage += talentTree.getTalentRank("Power Strike") * 2;
    }
    if (className == "Mage") {
        baseDamage = totalMag + (rand() % 8);
        if (talentTree.hasTalent("Arcane Knowledge")) {
            baseDamage += talentTree.getTalentRank("Arcane Knowledge") * 3;
        }
    }
    if (className == "Rogue" && talentTree.hasTalent("Precision")) {
        if (rand() % 100 < 20 + talentTree.getTalentRank("Precision") * 10) {
            cout << "Critical Hit! ";
            baseDamage *= 2;
        }
    }
    
    return baseDamage;
}

void Player::takeDamage(int damage) {
    int totalDef = getTotalDefense();
    int actualDamage = damage - (totalDef / 2);
    
    // Apply talent bonuses
    if (className == "Warrior" && talentTree.hasTalent("Shield Master")) {
        actualDamage -= talentTree.getTalentRank("Shield Master") * 3;
    }
    if (className == "Cleric" && talentTree.hasTalent("Holy Protection")) {
        actualDamage -= talentTree.getTalentRank("Holy Protection") * 2;
    }
    
    if (actualDamage < 1) actualDamage = 1;
    hp -= actualDamage;
    if (hp < 0) hp = 0;
}

void Player::heal(int amount) {
    hp += amount;
    if (hp > maxHP) hp = maxHP;
}

void Player::gainExperience(int xp) {
    experience += xp;
    cout << "Gained " << xp << " experience!" << endl;
    
    while (experience >= experienceToNextLevel) {
        levelUp();
    }
}

void Player::levelUp() {
    level++;
    experience -= experienceToNextLevel;
    experienceToNextLevel = level * 100;
    
    // Increase stats
    maxHP += 35;
    hp = maxHP;
    strength += 5;
    magic += 5;
    defense += 4;
    speed += 4;
    
    // Grant points
    attributePoints.addPoints(3);
    talentTree.addPoints(1);
    
    if(level + 5) {
        talentTree.addPoints(3); // Bonus talent point every 5 levels
    }

    cout << "\n*** LEVEL UP! You are now level " << level << " ***" << endl;
    cout << "All stats have increased!" << endl;
    cout << "You gained 3 attribute points and 1 talent point!" << endl;
}

void Player::rest() {
    hp = maxHP;
}

void Player::addStatBonus(AttributeType type, int amount) {
    switch (type) {
        case AttributeType::STRENGTH:
            strength += amount;
            break;
        case AttributeType::MAGIC:
            magic += amount;
            break;
        case AttributeType::DEFENSE:
            defense += amount;
            break;
        case AttributeType::SPEED:
            speed += amount;
            break;
    }
}

void Player::openTalentTree() {
    bool browsing = true;
    while (browsing) {
        talentTree.displayTalents();
        
        if (talentTree.getAvailablePoints() == 0) {
            cout << "\nNo talent points available. Level up to gain more!" << endl;
            cout << "Press any key to continue...";
            cin.ignore();
            cin.get();
            return;
        }
        
        cout << "\nOptions:" << endl;
        cout << "  - Enter talent name to upgrade" << endl;
        cout << "  - Type 'auto' to auto-allocate all points" << endl;
        cout << "  - Type 'exit' to leave" << endl;
        cout << "\nYour choice: ";
        cin.ignore();
        string talentName;
        getline(cin, talentName);
        
        if (talentName == "exit") {
            browsing = false;
        } else if (talentName == "auto") {
            talentTree.autoAllocate();
            cout << "\nPress any key to continue...";
            cin.get();
        } else {
            talentTree.upgradeTalent(talentName);
        }
    }
}

void Player::distributeAttributePoints() {
    if (attributePoints.getAvailablePoints() == 0) {
        cout << "No attribute points available. Level up to gain more!" << endl;
        return;
    }
    
    cout << "\nDo you want to:" << endl;
    cout << "  1. Distribute points manually" << endl;
    cout << "  2. Auto-allocate all points (optimized for your class)" << endl;
    cout << "\nChoice: ";
    int choice;
    cin >> choice;
    
    if (choice == 2) {
        attributePoints.autoAllocate(*this);
        cout << "\nPress any key to continue...";
        cin.ignore();
        cin.get();
    } else {
        attributePoints.distributePoints(*this);
    }
}

bool Player::canEquip(const Item* item) const {
    if (!item || !item->getIsEquippable()) return false;
    
    EquipmentClass reqClass = item->getRequiredClass();
    if (reqClass == EquipmentClass::ALL) return true;
    
    switch (playerClass) {
        case PlayerClass::WARRIOR: return reqClass == EquipmentClass::WARRIOR;
        case PlayerClass::MAGE: return reqClass == EquipmentClass::MAGE;
        case PlayerClass::ROGUE: return reqClass == EquipmentClass::ROGUE;
        case PlayerClass::CLERIC: return reqClass == EquipmentClass::CLERIC;
        case PlayerClass::RANGER: return reqClass == EquipmentClass::RANGER;
        default: return false;
    }
}

bool Player::equipItem(Item* item) {
    if (!canEquip(item)) {
        ConsoleUI::printError("You cannot equip this item! Class requirement: " + item->getClassRequirement());
        return false;
    }
    
    if (item->getType() == ItemType::WEAPON) {
        if (equippedWeapon) {
            unequipWeapon();
        }
        equippedWeapon = item;
        ConsoleUI::printSuccess("Equipped: " + item->getName());
        return true;
    } else if (item->getType() == ItemType::ARMOR) {
        if (equippedArmor) {
            unequipArmor();
        }
        equippedArmor = item;
        ConsoleUI::printSuccess("Equipped: " + item->getName());
        return true;
    }
    
    return false;
}

void Player::unequipWeapon() {
    if (equippedWeapon) {
        ConsoleUI::printInfo("Unequipped: " + equippedWeapon->getName());
        equippedWeapon = nullptr;
    }
}

void Player::unequipArmor() {
    if (equippedArmor) {
        ConsoleUI::printInfo("Unequipped: " + equippedArmor->getName());
        equippedArmor = nullptr;
    }
}

void Player::showEquipment() {
    ConsoleUI::clearScreen();
    ConsoleUI::printHeader("=== EQUIPMENT ===");
    
    cout << "\nWeapon Slot: ";
    if (equippedWeapon) {
        ConsoleUI::setColor(ConsoleUI::Color::YELLOW, ConsoleUI::Color::BLACK);
        cout << equippedWeapon->getName();
        ConsoleUI::setColor(ConsoleUI::Color::WHITE, ConsoleUI::Color::BLACK);
        cout << "\n  " << equippedWeapon->getDescription();
        if (equippedWeapon->getStrengthBonus() > 0) cout << "\n  +" << equippedWeapon->getStrengthBonus() << " Strength";
        if (equippedWeapon->getMagicBonus() > 0) cout << "\n  +" << equippedWeapon->getMagicBonus() << " Magic";
        if (equippedWeapon->getSpeedBonus() > 0) cout << "\n  +" << equippedWeapon->getSpeedBonus() << " Speed";
    } else {
        ConsoleUI::setColor(ConsoleUI::Color::DARK_GRAY, ConsoleUI::Color::BLACK);
        cout << "Empty";
        ConsoleUI::setColor(ConsoleUI::Color::WHITE, ConsoleUI::Color::BLACK);
    }
    
    cout << "\n\nArmor Slot: ";
    if (equippedArmor) {
        ConsoleUI::setColor(ConsoleUI::Color::YELLOW, ConsoleUI::Color::BLACK);
        cout << equippedArmor->getName();
        ConsoleUI::setColor(ConsoleUI::Color::WHITE, ConsoleUI::Color::BLACK);
        cout << "\n  " << equippedArmor->getDescription();
        if (equippedArmor->getDefenseBonus() > 0) cout << "\n  +" << equippedArmor->getDefenseBonus() << " Defense";
        if (equippedArmor->getStrengthBonus() > 0) cout << "\n  +" << equippedArmor->getStrengthBonus() << " Strength";
        if (equippedArmor->getMagicBonus() > 0) cout << "\n  +" << equippedArmor->getMagicBonus() << " Magic";
        if (equippedArmor->getSpeedBonus() > 0) cout << "\n  +" << equippedArmor->getSpeedBonus() << " Speed";
    } else {
        ConsoleUI::setColor(ConsoleUI::Color::DARK_GRAY, ConsoleUI::Color::BLACK);
        cout << "Empty";
        ConsoleUI::setColor(ConsoleUI::Color::WHITE, ConsoleUI::Color::BLACK);
    }
    
    cout << "\n\n";
    ConsoleUI::printSeparator();
    cout << "Total Bonuses:\n";
    int totalStr = (equippedWeapon ? equippedWeapon->getStrengthBonus() : 0) + (equippedArmor ? equippedArmor->getStrengthBonus() : 0);
    int totalMag = (equippedWeapon ? equippedWeapon->getMagicBonus() : 0) + (equippedArmor ? equippedArmor->getMagicBonus() : 0);
    int totalDef = (equippedWeapon ? equippedWeapon->getDefenseBonus() : 0) + (equippedArmor ? equippedArmor->getDefenseBonus() : 0);
    int totalSpd = (equippedWeapon ? equippedWeapon->getSpeedBonus() : 0) + (equippedArmor ? equippedArmor->getSpeedBonus() : 0);
    
    cout << "Strength: +" << totalStr << " | Magic: +" << totalMag << " | Defense: +" << totalDef << " | Speed: +" << totalSpd << endl;
}

int Player::getTotalStrength() const {
    int bonus = 0;
    if (equippedWeapon) bonus += equippedWeapon->getStrengthBonus();
    if (equippedArmor) bonus += equippedArmor->getStrengthBonus();
    return strength + bonus;
}

int Player::getTotalMagic() const {
    int bonus = 0;
    if (equippedWeapon) bonus += equippedWeapon->getMagicBonus();
    if (equippedArmor) bonus += equippedArmor->getMagicBonus();
    return magic + bonus;
}

int Player::getTotalDefense() const {
    int bonus = 0;
    if (equippedWeapon) bonus += equippedWeapon->getDefenseBonus();
    if (equippedArmor) bonus += equippedArmor->getDefenseBonus();
    return defense + bonus;
}

int Player::getTotalSpeed() const {
    int bonus = 0;
    if (equippedWeapon) bonus += equippedWeapon->getSpeedBonus();
    if (equippedArmor) bonus += equippedArmor->getSpeedBonus();
    return speed + bonus;
}

