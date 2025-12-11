# Developer Guide - Expanding RPG Game

## Architecture Overview

The game follows a modular architecture with clear separation of concerns:

```
Game Loop (Game.cpp)
    ├── Player System (Player.cpp)
    │   ├── Attribute Points (Points.cpp)
    │   ├── Talent Tree (Talents.cpp)
    │   └── Inventory (Inventory.cpp)
    ├── Combat System
    │   ├── Enemy Generation (Enemy.cpp)
    │   └── Boss Encounters (boss.cpp)
    ├── Shop System
    │   ├── Weapon Shop (WeaponShop.cpp)
    │   ├── Armor Shop (ArmorShop.cpp)
    │   └── Potion Shop (PotionShop.cpp)
    └── Quest System (QuestManager.cpp)
```

## Adding New Features

### 1. Adding a New Class

**Step 1:** Add enum in `Player.h`
```cpp
enum class PlayerClass {
    WARRIOR,
    MAGE,
    ROGUE,
    CLERIC,
    RANGER,
    PALADIN  // New class
};
```

**Step 2:** Add constructor case in `Player.cpp`
```cpp
case 6: // Paladin
    playerClass = PlayerClass::PALADIN;
    className = "Paladin";
    maxHP += 15;
    strength += 4;
    magic += 3;
    defense += 4;
    break;
```

**Step 3:** Create talent tree in `Talents.cpp`
```cpp
void TalentTree::initializePaladinTree() {
    talents["Holy Strike"] = TalentNode("Holy Strike", "Melee attack with holy power", 5, 1);
    talents["Divine Shield"] = TalentNode("Divine Shield", "Increases defense", 3, 1);
    // Add 4-7 more talents...
}
```

**Step 4:** Update talent tree constructor in `Talents.cpp`
```cpp
TalentTree::TalentTree(string className) : className(className), availablePoints(0) {
    if (className == "Warrior") initializeWarriorTree();
    else if (className == "Mage") initializeMageTree();
    else if (className == "Rogue") initializeRogueTree();
    else if (className == "Cleric") initializeClericTree();
    else if (className == "Ranger") initializeRangerTree();
    else if (className == "Paladin") initializePaladinTree();  // Add this
}
```

**Step 5:** Update character creation in `Game.cpp`
```cpp
cout << "6. Paladin (Holy Warrior, Balanced)" << endl;
```

**Step 6:** Add talent effects in `Player.cpp` (attack/takeDamage functions)

### 2. Adding a New Origin

**Step 1:** Add enum in `Player.h`
```cpp
enum class Origin {
    HUMAN,
    ELF,
    DWARF,
    ORC,
    HALFLING,
    DRAGONBORN  // New origin
};
```

**Step 2:** Add case in Player constructor in `Player.cpp`
```cpp
case 6: // Dragonborn
    origin = Origin::DRAGONBORN;
    originName = "Dragonborn";
    maxHP = 105;
    strength = 12;
    magic = 12;
    defense = 10;
    speed = 9;
    break;
```

**Step 3:** Update character creation in `Game.cpp`
```cpp
cout << "6. Dragonborn (Balanced, Fire resistance)" << endl;
```

### 3. Adding New Talents

**Location:** `Talents.cpp` in the appropriate `initialize[Class]Tree()` function

**Basic Talent:**
```cpp
talents["Talent Name"] = TalentNode("Talent Name", "Description", maxRanks, costPerRank);
```

**Talent with Prerequisites:**
```cpp
TalentNode advancedTalent("Advanced Talent", "Powerful ability", 1, 2);
advancedTalent.prerequisites.push_back("Basic Talent");
talents["Advanced Talent"] = advancedTalent;
```

**Implementing Talent Effects:**

In `Player.cpp` attack function:
```cpp
if (className == "YourClass" && talentTree.hasTalent("Your Talent")) {
    int ranks = talentTree.getTalentRank("Your Talent");
    baseDamage += ranks * 5;  // Example: +5 damage per rank
}
```

In `Player.cpp` takeDamage function:
```cpp
if (talentTree.hasTalent("Defensive Talent")) {
    actualDamage = (int)(actualDamage * 0.9);  // 10% reduction
}
```

### 4. Adding a New Shop

**Step 1:** Create header file `Systems/Shop/YourShop.h`
```cpp
#ifndef YOURSHOP_H
#define YOURSHOP_H
#include "../../Entities/Player/Player.h"

void openYourShop(Player& player);

#endif
```

**Step 2:** Create implementation `Systems/Shop/YourShop.cpp`
```cpp
#include "YourShop.h"
#include <iostream>
#include <vector>

using namespace std;

struct YourShopItem {
    string name;
    string description;
    int price;
    ItemType type;
    int value;
};

void openYourShop(Player& player) {
    vector<YourShopItem> items = {
        {"Item 1", "Description", 100, ItemType::WEAPON, 10},
        // Add more items...
    };
    
    bool shopping = true;
    while (shopping) {
        cout << "\n=== Your Shop ===" << endl;
        cout << "Your Gold: " << player.getGold() << endl;
        
        // Display items...
        // Handle purchases...
    }
}
```

**Step 3:** Add to `Game.cpp`
```cpp
#include "../Systems/Shop/YourShop.h"

// In visitShops():
case 4:
    openYourShop(*player);
    break;
```

**Step 4:** Update CMakeLists.txt and compile.bat

### 5. Adding New Items to Existing Shops

**Location:** In respective shop .cpp file

```cpp
vector<ShopItem> weapons = {
    {"Existing Item", "...", 100, ItemType::WEAPON, 10},
    {"New Item", "A powerful new weapon", 500, ItemType::WEAPON, 20},  // Add this
};
```

### 6. Adding Special Item Effects

**Step 1:** Add new ItemType in `Item.h` if needed
```cpp
enum class ItemType {
    WEAPON,
    ARMOR,
    CONSUMABLE,
    QUEST,
    BUFF  // New type
};
```

**Step 2:** Create item effect in `Inventory.cpp` useItem function
```cpp
if (item.getType() == ItemType::BUFF) {
    // Apply temporary buff
    cout << "You feel empowered!" << endl;
}
```

### 7. Adding New Enemy Types

**In Enemy.cpp:** Add to `generateRandomEnemy()`
```cpp
case 4:  // New enemy type
    return Enemy("NewEnemy", hp, strength, defense, xp, gold);
```

### 8. Adding New Quests

**In Game.cpp:** In character creation or exploration
```cpp
questManager.addQuest("Quest Name", "Quest Description", rewardXP);
```

**Updating quest progress:**
```cpp
questManager.updateProgress("Quest Name", 1);
```

## Code Style Guidelines

### Naming Conventions
- Classes: PascalCase (e.g., `TalentTree`)
- Functions: camelCase (e.g., `addPoints`)
- Variables: camelCase (e.g., `availablePoints`)
- Constants: UPPER_SNAKE_CASE (e.g., `MAX_LEVEL`)
- Enums: PascalCase with UPPER values (e.g., `PlayerClass::WARRIOR`)

### File Organization
- Header guards: `#ifndef FILENAME_H`
- Includes in order: system headers, then project headers
- One class per file pair (.h/.cpp)
- Keep functions under 50 lines when possible

### Comments
- Use comments for complex logic
- Document public API in headers
- Explain "why" not "what" in implementation

## Testing New Features

### Basic Test Checklist
- [ ] Code compiles without errors
- [ ] New menu options work
- [ ] Values persist through level ups
- [ ] No memory leaks (valgrind if available)
- [ ] Edge cases handled (0 gold, max level, etc.)

### Integration Testing
1. Create new character with new class/origin
2. Level up and test point systems
3. Buy items from new shops
4. Engage in combat with new talents
5. Save and load (when implemented)

## Common Pitfalls

### 1. Forgetting to Update CMakeLists.txt
Always add new .cpp files to the build system:
```cmake
set(SOURCES
    # ... existing files ...
    ../Source/Systems/YourFolder/YourFile.cpp
)
```

### 2. Not Updating compile.bat
Add new source files to the g++ command:
```batch
"Source/Systems/YourFolder/YourFile.cpp" ^
```

### 3. Include Cycles
Avoid circular includes. Use forward declarations:
```cpp
class Player;  // Forward declaration
```

### 4. Memory Leaks
- Always match `new` with `delete`
- Prefer stack allocation over heap
- Use smart pointers in C++11+

### 5. Integer Overflow
Be careful with damage calculations:
```cpp
int damage = min(strength * multiplier, INT_MAX / 2);
```

## Performance Considerations

### Current Performance
- O(1) stat lookups
- O(log n) talent lookups (map)
- O(n) shop item display
- Minimal memory footprint

### Optimization Tips
1. Use references to avoid copies
2. Reserve vector capacity for shops
3. Cache frequently accessed talent values
4. Use const& for parameters when possible

## Future Enhancement Ideas

### Short Term (Easy)
- [ ] More shop items
- [ ] More talents per class
- [ ] New enemy types
- [ ] More quests
- [ ] Item rarity system

### Medium Term (Moderate)
- [ ] Equipment slots (weapon/armor equipped)
- [ ] Character stats screen improvements
- [ ] Save/Load game functionality
- [ ] Multiple zones/areas
- [ ] Party system (companions)

### Long Term (Complex)
- [ ] Skill system separate from talents
- [ ] Crafting system
- [ ] Random dungeon generation
- [ ] Multiplayer/Trading
- [ ] Graphics/GUI layer

## Build System

### Supported Compilers
- GCC 4.8+ (g++)
- Clang 3.4+
- MSVC 2015+

### CMake Configuration
Minimum version: 3.10
Standard: C++11

### Batch File Compilation
Uses g++ directly, no CMake required

## Version Control Best Practices

### Commit Messages
```
[Feature] Add Paladin class with talent tree
[Fix] Correct attribute point calculation
[Refactor] Simplify shop purchase logic
[Docs] Update README with new features
```

### Branching Strategy
- `main` - Stable releases
- `develop` - Active development
- `feature/feature-name` - New features
- `bugfix/bug-name` - Bug fixes

## Documentation Requirements

When adding features, update:
1. README.md - User-facing changes
2. This file - Developer guidance
3. Code comments - Complex logic
4. Version2.0_Summary.md - Implementation details

## Support and Community

### Reporting Issues
Include:
- OS and compiler version
- Steps to reproduce
- Expected vs actual behavior
- Relevant code snippets

### Contributing
1. Fork repository
2. Create feature branch
3. Implement and test
4. Submit pull request
5. Respond to review feedback

## Resources

### C++ References
- cppreference.com - C++ standard library
- learncpp.com - C++ tutorials
- stackoverflow.com - Q&A

### Game Development
- gamedev.net - Game dev community
- roguebasin.com - Roguelike development
- gamasutra.com - Industry articles

---

Happy coding! The RPG Game is designed to be expanded. Feel free to experiment and add your own creative features!
