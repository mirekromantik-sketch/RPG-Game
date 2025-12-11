#include "Points.h"
#include "../../Entities/Player/Player.h"
#include <iostream>
#include <string>

using namespace std;

AttributePoints::AttributePoints() : availablePoints(0), spentStrength(0), spentMagic(0), spentDefense(0), spentSpeed(0) {}

void AttributePoints::addPoints(int points) {
    availablePoints += points;
}

bool AttributePoints::spendPoint(AttributeType type) {
    if (availablePoints <= 0) {
        cout << "No available points to spend!" << endl;
        return false;
    }
    
    switch (type) {
        case AttributeType::STRENGTH:
            spentStrength++;
            break;
        case AttributeType::MAGIC:
            spentMagic++;
            break;
        case AttributeType::DEFENSE:
            spentDefense++;
            break;
        case AttributeType::SPEED:
            spentSpeed++;
            break;
    }
    
    availablePoints--;
    return true;
}

void AttributePoints::displayPoints() const {
    cout << "\n=== Attribute Points ===" << endl;
    cout << "Available Points: " << availablePoints << endl;
    cout << "\nPoints Spent:" << endl;
    cout << "  Strength: +" << spentStrength << endl;
    cout << "  Magic: +" << spentMagic << endl;
    cout << "  Defense: +" << spentDefense << endl;
    cout << "  Speed: +" << spentSpeed << endl;
}

int AttributePoints::getBonus(AttributeType type) const {
    switch (type) {
        case AttributeType::STRENGTH:
            return spentStrength;
        case AttributeType::MAGIC:
            return spentMagic;
        case AttributeType::DEFENSE:
            return spentDefense;
        case AttributeType::SPEED:
            return spentSpeed;
        default:
            return 0;
    }
}

void AttributePoints::distributePoints(Player& player) {
    while (availablePoints > 0) {
        displayPoints();
        cout << "\nDistribute points to:" << endl;
        cout << "1. Strength (+3 per point)" << endl;
        cout << "2. Magic (+3 per point)" << endl;
        cout << "3. Defense (+2 per point)" << endl;
        cout << "4. Speed (+2 per point)" << endl;
        cout << "5. Finish distributing" << endl;
        cout << "Choice: ";
        
        int choice;
        cin >> choice;
        
        if (choice == 5) break;
        
        AttributeType type;
        string attributeName;
        int bonus;
        
        switch (choice) {
            case 1:
                type = AttributeType::STRENGTH;
                attributeName = "Strength";
                bonus = 3;
                break;
            case 2:
                type = AttributeType::MAGIC;
                attributeName = "Magic";
                bonus = 3;
                break;
            case 3:
                type = AttributeType::DEFENSE;
                attributeName = "Defense";
                bonus = 2;
                break;
            case 4:
                type = AttributeType::SPEED;
                attributeName = "Speed";
                bonus = 2;
                break;
            default:
                cout << "Invalid choice!" << endl;
                continue;
        }
        
        if (spendPoint(type)) {
            player.addStatBonus(type, bonus);
            cout << attributeName << " increased by " << bonus << "!" << endl;
        }
    }
    
    if (availablePoints == 0) {
        cout << "\nAll points distributed!" << endl;
    }
}

void AttributePoints::autoAllocate(Player& player) {
    if (availablePoints == 0) {
        cout << "\nNo attribute points available to allocate!" << endl;
        return;
    }
    
    int initialPoints = availablePoints;
    
    // Get player class to determine optimal stat distribution
    string className = player.getClassName();
    
    // Define allocation strategy based on class
    int strPoints = 0, magPoints = 0, defPoints = 0, spdPoints = 0;
    
    if (className == "Warrior") {
        // Warrior: 50% STR, 30% DEF, 20% SPD
        strPoints = (availablePoints * 5) / 10;
        defPoints = (availablePoints * 3) / 10;
        spdPoints = availablePoints - strPoints - defPoints;
    } else if (className == "Mage") {
        // Mage: 60% MAG, 20% DEF, 20% SPD
        magPoints = (availablePoints * 6) / 10;
        defPoints = (availablePoints * 2) / 10;
        spdPoints = availablePoints - magPoints - defPoints;
    } else if (className == "Rogue") {
        // Rogue: 40% SPD, 40% STR, 20% DEF
        spdPoints = (availablePoints * 4) / 10;
        strPoints = (availablePoints * 4) / 10;
        defPoints = availablePoints - spdPoints - strPoints;
    } else if (className == "Cleric") {
        // Cleric: 40% MAG, 40% DEF, 20% STR
        magPoints = (availablePoints * 4) / 10;
        defPoints = (availablePoints * 4) / 10;
        strPoints = availablePoints - magPoints - defPoints;
    } else if (className == "Ranger") {
        // Ranger: 40% STR, 40% SPD, 20% DEF
        strPoints = (availablePoints * 4) / 10;
        spdPoints = (availablePoints * 4) / 10;
        defPoints = availablePoints - strPoints - spdPoints;
    } else {
        // Default: balanced distribution
        strPoints = availablePoints / 4;
        magPoints = availablePoints / 4;
        defPoints = availablePoints / 4;
        spdPoints = availablePoints - strPoints - magPoints - defPoints;
    }
    
    // Apply the points
    for (int i = 0; i < strPoints; i++) {
        if (spendPoint(AttributeType::STRENGTH)) {
            player.addStatBonus(AttributeType::STRENGTH, 3);
        }
    }
    
    for (int i = 0; i < magPoints; i++) {
        if (spendPoint(AttributeType::MAGIC)) {
            player.addStatBonus(AttributeType::MAGIC, 3);
        }
    }
    
    for (int i = 0; i < defPoints; i++) {
        if (spendPoint(AttributeType::DEFENSE)) {
            player.addStatBonus(AttributeType::DEFENSE, 2);
        }
    }
    
    for (int i = 0; i < spdPoints; i++) {
        if (spendPoint(AttributeType::SPEED)) {
            player.addStatBonus(AttributeType::SPEED, 2);
        }
    }
    
    cout << "\n=== Auto-Allocated Attribute Points ===" << endl;
    cout << "Total points spent: " << (initialPoints - availablePoints) << endl;
    cout << "  Strength: +" << (strPoints * 3) << " (from " << strPoints << " points)" << endl;
    cout << "  Magic: +" << (magPoints * 3) << " (from " << magPoints << " points)" << endl;
    cout << "  Defense: +" << (defPoints * 2) << " (from " << defPoints << " points)" << endl;
    cout << "  Speed: +" << (spdPoints * 2) << " (from " << spdPoints << " points)" << endl;
    cout << "Points remaining: " << availablePoints << endl;
}
