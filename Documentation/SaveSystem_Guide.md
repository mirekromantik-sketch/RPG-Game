# Named Save System - Quick Guide

## New Features

### Start Menu
When you launch the game, you'll see:

```
======================================================================
                    START MENU
======================================================================
--------------------------------------------------------------
  1. New Game
  2. Load Game
  3. Delete Save
  0. Exit
--------------------------------------------------------------
[INFO] Found 3 save file(s)

  Choice: _
```

### Creating Named Saves

**Option 1: Auto-Save**
- Game auto-saves when you exit
- Filename: `[YourCharacterName]_autosave.json`
- Location: `saves/` folder

**Option 2: Manual Save (Main Menu → 9)**
```
======================================================================
                    SAVE GAME
======================================================================

  Enter save name (or press Enter for default): _
```

- Enter custom name: `my_warrior_run`
- Press Enter for default: `[YourCharacterName]_save`
- Saves to: `saves/my_warrior_run.json`

### Loading Saves

From Start Menu → 2. Load Game:

```
======================================================================
                    LOAD GAME
======================================================================
--------------------------------------------------------------
  1. Marcel_autosave
  2. my_warrior_run
  3. backup_save
  0. Cancel
--------------------------------------------------------------

  Choose save to load: _
```

- Pick a number to load that save
- 0 to go back

### Deleting Saves

From Start Menu → 3. Delete Save:

```
======================================================================
                    DELETE SAVE
======================================================================
--------------------------------------------------------------
  1. old_character
  2. test_save
  0. Cancel
--------------------------------------------------------------

  Choose save to delete: 1

[WARNING] Are you sure you want to delete 'old_character'? (y/n): y
[SUCCESS] Save file deleted!
```

## Save File Organization

```
RPG-Game/
├── saves/                          # All saves stored here
│   ├── Marcel_autosave.json       # Auto-save
│   ├── Marcel_save.json           # Default manual save
│   ├── warrior_level_30.json      # Custom save
│   └── backup.json                # Another custom save
└── savegame.json                   # Legacy save (still works)
```

## Features

### ✅ Named Save Files
- Create multiple characters
- Keep backups of important progress
- Organize saves by character/build

### ✅ Save Management
- List all available saves
- Load any save from start menu
- Delete old/unwanted saves
- Confirmation before deletion

### ✅ Auto-Save
- Automatic save when exiting game
- Named: `[CharacterName]_autosave`
- Never lose progress!

### ✅ Default Names
- Press Enter during save for default name
- Format: `[CharacterName]_save`
- Quick and easy saving

## Tips

### Save Naming Conventions
- Use descriptive names: `warrior_level_20`, `mage_fire_build`
- Include level or progress: `cleric_lv15_talent_test`
- Keep backups: `main_character_backup`

### Multiple Characters
```
saves/
├── Thorin_autosave.json      # Dwarf Warrior
├── Elara_save.json           # Elf Mage
├── Sneaky_autosave.json      # Halfling Rogue
└── Healer_save.json          # Human Cleric
```

### Best Practices
1. **Save often** - Use manual save (Option 9) for important progress
2. **Use meaningful names** - Makes finding saves easier
3. **Keep backups** - Save before difficult battles
4. **Clean up** - Delete old test characters

## Technical Details

### Save Location
- All saves in `saves/` directory
- Automatically created if doesn't exist
- `.json` extension added automatically

### File Format
```json
{
  "version": "2.0",
  "player": {
    "name": "Marcel",
    "className": "Warrior",
    "originName": "Orc",
    "level": 30,
    ...
  }
}
```

### Compatibility
- Old `savegame.json` still works
- New saves use `saves/` folder
- Can have both old and new saves

## Troubleshooting

### "No save files found"
- Create a new character first
- Save using option 9 in main menu
- Check `saves/` folder exists

### Can't find my save
- Check save name spelling
- Look in `saves/` folder
- Legacy saves in root directory

### Delete didn't work
- Confirm deletion with 'y'
- Check file permissions
- File might be in use

---

Enjoy your organized save management system!
