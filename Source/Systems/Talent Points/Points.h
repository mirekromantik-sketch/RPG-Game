#ifndef POINTS_H
#define POINTS_H

class Player;  // Forward declaration

enum class AttributeType {
    STRENGTH,
    MAGIC,
    DEFENSE,
    SPEED
};

class AttributePoints {
private:
    int availablePoints;
    int spentStrength;
    int spentMagic;
    int spentDefense;
    int spentSpeed;

public:
    AttributePoints();
    
    void addPoints(int points);
    bool spendPoint(AttributeType type);
    void displayPoints() const;
    int getBonus(AttributeType type) const;
    void distributePoints(Player& player);
    void autoAllocate(Player& player);
    
    int getAvailablePoints() const { return availablePoints; }
    int getSpentStrength() const { return spentStrength; }
    int getSpentMagic() const { return spentMagic; }
    int getSpentDefense() const { return spentDefense; }
    int getSpentSpeed() const { return spentSpeed; }
    void setAvailablePoints(int points) { availablePoints = points; }
    void setSpentPoints(int str, int mag, int def, int spd) {
        spentStrength = str;
        spentMagic = mag;
        spentDefense = def;
        spentSpeed = spd;
    }
};

#endif
