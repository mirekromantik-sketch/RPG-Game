# RPG Game - Simple C++ Text-Based RPG

## Project Structure

### Core Files
- **main.cpp** - Entry point, initializes the game
- **Game.h/cpp** - Main game loop, menu system, and game flow

### Entities
- **Player.h/cpp** - Player character with stats, leveling, and inventory
- **Enemy.h/cpp** - Enemy generation and combat AI

### Systems
- **Inventory/** - Item management system
  - Item.h/cpp - Item definitions and types
  - Inventory.h/cpp - Inventory container and operations
- **Quest/** - Quest tracking system
  - Quest.h/cpp - Individual quest logic
  - QuestManager.h/cpp - Manages all quests

## How to Compile and Run

### Option 1: Using the batch files
1. Run `compile.bat` to compile the game
2. Run `run.bat` to play the game

### Option 2: Manual compilation
```bash
g++ -std=c++11 Source/main.cpp Source/Core/Game.cpp Source/Entities/Player/Player.cpp Source/Entities/Enemies/Enemy.cpp Source/Systems/Inventory/Item.cpp Source/Systems/Inventory/Inventory.cpp Source/Systems/Quest/Quest.cpp Source/Systems/Quest/QuestManager.cpp -o Build/Output/RPGGame.exe
```

Then run: `Build\Output\RPGGame.exe`

## Features

### Character Creation
- Choose from 3 classes: Warrior, Mage, or Rogue
- Each class has unique stats

### Combat System
- Turn-based combat with enemies
- Attack, use items, or run away
- Gain XP and gold from victories
- Random item drops

### Inventory System
- Collect and use items
- Health potions restore HP
- Equipment system (expandable)

### Quest System
- Track quest progress
- Complete quests for rewards
- Starting quest: "First Steps" - Defeat 3 enemies

### Leveling System
- Gain XP from combat
- Level up increases all stats
- HP fully restored on level up

## How to Add Features

### Adding New Enemies
Edit `Enemy.cpp` in `generateRandomEnemy()` function:
```cpp
string names[] = {"Goblin", "Skeleton", "Wolf", "Orc", "Bandit", "Spider", "Zombie", "YOUR_ENEMY"};
```

### Adding New Items
Edit `Item.cpp` in `generateRandomItem()` function or create items directly:
```cpp
Item newItem("Item Name", "Description", ItemType::WEAPON, 25);
```

### Adding New Quests
In `Game.cpp`, add quests in any function:
```cpp
questManager.addQuest("Quest Title", "Quest Description", goalAmount);
```

### Adding New Stats
1. Add the stat variable in `Player.h`
2. Initialize it in `Player.cpp` constructor
3. Display it in `showStats()`
4. Increase it in `levelUp()`

### Adding New Menu Options
Edit `showMainMenu()` in `Game.cpp`:
1. Add a new cout line for the option
2. Add a new case in the switch statement
3. Create the function for that option

## Game Tips

- Rest frequently to restore HP
- Use potions during difficult battles
- Level up by defeating enemies
- Check your quests regularly to track progress

## Future Expansion Ideas

- Save/Load game functionality
- More enemy types with special abilities
- Equipment system (weapons and armor)
- Magic spells system
- NPC dialogue system
- Town/shop system
- Multiple areas/dungeons
- Boss battles
- Status effects (poison, burn, etc.)
- Skill trees

Enjoy your adventure!
