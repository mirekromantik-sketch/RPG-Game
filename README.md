# RPG Game - Simple C++ Text-Based RPG

## Project Structure

### Core Files
- **main.cpp** - Entry point, initializes the game
- **Game.h/cpp** - Main game loop, menu system, and game flow

### Entities
- **Player.h/cpp** - Player character with stats, leveling, inventory, talents, and attribute points
- **Enemy.h/cpp** - Enemy generation and combat AI
- **Boss.h/cpp** - Powerful boss encounters

### Systems
- **Inventory/** - Item management system
  - Item.h/cpp - Item definitions and types
  - Inventory.h/cpp - Inventory container and operations
- **Quest/** - Quest tracking system
  - Quest.h/cpp - Individual quest logic
  - QuestManager.h/cpp - Manages all quests
- **Shop/** - Shopping system
  - WeaponShop.h/cpp - Weapon shop with various weapons
  - ArmorShop.h/cpp - Armor shop with various armors
  - PotionShop.h/cpp - Potion shop with consumables
- **Talent Points/** - Character progression systems
  - Talents.h/cpp - Talent tree system for each class
  - Points.h/cpp - Attribute point distribution system

## How to Compile and Run

### Option 1: Using the batch files
1. Run `compile.bat` to compile the game
2. Run `run.bat` to play the game

### Option 2: Manual compilation with CMake
```bash
cd Build
cmake .
cmake --build .
```

### Option 3: Manual compilation with g++
```bash
g++ -std=c++11 Source/main.cpp Source/Core/Game.cpp Source/Entities/Player/Player.cpp Source/Entities/Enemies/Enemy.cpp Source/Entities/Enemies/boss.cpp Source/Systems/Inventory/Item.cpp Source/Systems/Inventory/Inventory.cpp Source/Systems/Quest/Quest.cpp Source/Systems/Quest/QuestManager.cpp "Source/Systems/Shop/WeaponShop.cpp" "Source/Systems/Shop/ArmorShop.cpp" "Source/Systems/Shop/PotionShop.cpp" "Source/Systems/Talent Points/Points.cpp" "Source/Systems/Talent Points/Talents.cpp" -o Build/Output/RPGGame.exe
```

Then run: `Build\Output\RPGGame.exe`

## Features

### Character Creation
- **5 Classes Available:**
  - **Warrior** - High HP and Strength, excellent tank
  - **Mage** - High Magic, low HP, powerful spells
  - **Rogue** - Balanced stats, high speed, critical strikes
  - **Cleric** - Healer with balanced stats and support abilities
  - **Ranger** - Ranged attacks with pet companion

- **5 Origins Available:**
  - **Human** - Balanced stats, +10% gold gain
  - **Elf** - High magic & speed, lower HP
  - **Dwarf** - High HP & defense, lower speed
  - **Orc** - High strength, lower magic
  - **Halfling** - High speed, lower HP

### Talent Tree System
- Each class has a unique talent tree with 6-9 talents
- Earn 1 talent point per level
- Talents have prerequisites and multiple ranks
- **Warrior Talents:** Iron Will, Power Strike, Berserker Rage, Shield Master, etc.
- **Mage Talents:** Arcane Knowledge, Fireball Master, Ice Armor, etc.
- **Rogue Talents:** Agility, Backstab, Poison Blade, Shadow Dance, etc.
- **Cleric Talents:** Divine Power, Resurrection, Holy Smite, Prayer of Mending, etc.
- **Ranger Talents:** Marksmanship, Multi-Shot, Beast Mastery, Trap Master, etc.

### Attribute Point System
- Earn 3 attribute points per level
- Distribute points to:
  - **Strength** (+3 per point) - Increases physical damage
  - **Magic** (+3 per point) - Increases magic damage
  - **Defense** (+2 per point) - Reduces damage taken
  - **Speed** (+2 per point) - Affects turn order and evasion
- Points can be distributed anytime from the main menu

### Shop System
- **Weapon Shop** - Purchase weapons to increase damage (Iron Sword, Steel Sword, Magic Staff, etc.)
- **Armor Shop** - Buy armor to increase defense (Leather Armor, Chainmail, Dragon Scale Armor, etc.)
- **Potion Shop** - Stock up on consumables (Health Potions, Elixirs of Strength/Magic/Defense)
- All items cost gold earned from defeating enemies

### Combat System
- Turn-based combat with enemies and bosses
- Attack, use items, or run away
- Talents affect combat (critical strikes, damage bonuses, damage reduction)
- Boss encounters are more challenging with better rewards
- Gain XP and gold from victories
- Random item drops

### Inventory System
- Collect and use items
- Health potions restore HP during combat
- Equipment system with weapons and armor
- View all items in inventory

### Quest System
- Track quest progress
- Complete quests for rewards
- Starting quest: "First Steps" - Defeat 3 enemies

### Leveling System
- Gain XP from combat
- Level up increases all base stats
- HP fully restored on level up
- Earn attribute points and talent points on level up

## Gameplay Tips

- **Character Building:**
  - Choose an origin and class that complement each other
  - Plan your talent tree path early
  - Distribute attribute points to enhance your class strengths

- **Combat:**
  - Use potions during difficult battles
  - Talents can give significant combat advantages
  - Boss encounters require preparation - stock up on potions

- **Economy:**
  - Save gold for important purchases
  - Weapons and armor provide permanent stat increases
  - Health potions are essential for survival

- **Progression:**
  - Check your talent tree and attribute points after leveling up
  - Don't forget to distribute points before difficult encounters
  - Visit shops regularly to upgrade equipment

## Expansion Guide

The game is designed to be easily expandable:

### Adding New Classes
1. Add new enum to `PlayerClass` in Player.h
2. Add case in Player constructor for class stats
3. Create new talent tree in Talents.cpp (`initializeYourClassTree()`)
4. Update character creation menu in Game.cpp

### Adding New Origins
1. Add new enum to `Origin` in Player.h
2. Add case in Player constructor for origin bonuses
3. Update character creation menu in Game.cpp

### Adding New Talents
1. In respective `initialize[Class]Tree()` function in Talents.cpp
2. Create TalentNode with name, description, max ranks, and cost
3. Set prerequisites if needed
4. Add talent effects in Player::attack() or Player::takeDamage()

### Adding New Shops
1. Create new shop header and source files in Systems/Shop/
2. Implement shop function similar to existing shops
3. Add shop option in Game::visitShops()

### Adding New Items
1. Add items to shop vectors in shop .cpp files
2. Implement item effects if special (beyond HP restoration)

## Version History

### Version 1.0
- Basic game functionality

### Version 2.0 (Current)
- Added 2 new classes (Cleric, Ranger)
- Expanded origins from 3 to 5 (added Orc, Halfling)
- Origins now properly affect stats
- Implemented talent tree system for all 5 classes
- Added attribute point distribution system
- Created 3 functional shops (Weapon, Armor, Potion)
- Integrated all systems into main game loop
- Talents affect combat mechanics
- Level-up rewards include attribute and talent points


