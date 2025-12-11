#include "ArmorShop.h"
#include "../../Core/ConsoleUI.h"
#include <iostream>
#include <vector>

using namespace std;

struct ArmorShopItem {
    string name;
    string description;
    int price;
    int strBonus;
    int magBonus;
    int defBonus;
    int spdBonus;
    EquipmentClass reqClass;
};

void openArmorShop(Player& player) {
    vector<ArmorShopItem> armors = {
        // WARRIOR ARMOR (sorted by cost)
        {"Iron Plate", "Heavy warrior protection", 120, 3, 0, 8, -2, EquipmentClass::WARRIOR},
        {"Steel Plate Armor", "Superior plate protection", 400, 5, 0, 18, -3, EquipmentClass::WARRIOR},
        {"Titanium Warlord Plate", "Near-indestructible heavy plate", 700, 10, 0, 25, -2, EquipmentClass::WARRIOR},
        {"Obsidian Plate", "Dark rock-hard protection", 1200, 15, 0, 35, -1, EquipmentClass::WARRIOR},
        {"Dragonheart Armor", "Legendary heavy armor", 1600, 15, 0, 40, 0, EquipmentClass::WARRIOR},
        {"Thunderstrike Armor", "Shocks enemies on contact", 1800, 18, 0, 40, 1, EquipmentClass::WARRIOR},
        {"Ironclad Bastion", "Ultimate defensive armor", 2200, 25, 0, 50, 0, EquipmentClass::WARRIOR},
        {"Moltenheart Armor", "Forged in dragonfire", 2500, 20, 0, 55, 0, EquipmentClass::WARRIOR},
        {"Warbringer Plate", "Conqueror's legacy", 3500, 30, 0, 60, 2, EquipmentClass::WARRIOR},
        {"Dragonbone Armor", "Bones of ancient dragons", 4000, 32, 0, 65, 3, EquipmentClass::WARRIOR},
        {"Goliath Plate", "Makes wearer nearly unstoppable", 5000, 40, 0, 80, 5, EquipmentClass::WARRIOR},
        {"Colossus Exosuit", "Absurdly OP heavy armor", 10000, 40, 0, 110, 2, EquipmentClass::WARRIOR},
        {"Armageddon Suit", "Ultimate WARRIOR armor", 15000, 70, 0, 150, 10, EquipmentClass::WARRIOR},
        {"Berserker's Rage Plate", "Increase damage when low HP", 6500, 45, 0, 90, 8, EquipmentClass::WARRIOR},
        {"Volcanic Fortress", "Burns attackers", 7200, 48, 0, 95, 6, EquipmentClass::WARRIOR},
        {"Frostguard Armor", "Freezes melee attackers", 7800, 50, 0, 100, 7, EquipmentClass::WARRIOR},
        {"Blood Knight Plate", "Heals from damage dealt", 8500, 52, 0, 105, 9, EquipmentClass::WARRIOR},
        {"Enchanted Titan Armor +10", "Enhanced protection", 11000, 55, 5, 120, 12, EquipmentClass::WARRIOR},
        {"Demon Slayer Plate", "Massive vs demons", 9500, 58, 0, 110, 10, EquipmentClass::WARRIOR},
        {"Lightning Emperor Armor", "Shocks all nearby enemies", 12500, 62, 0, 135, 15, EquipmentClass::WARRIOR},
        {"Enchanted Dragonscale +15", "Dragon-blessed protection", 14000, 68, 10, 145, 18, EquipmentClass::WARRIOR},
        {"Immortal Warlord Plate", "Near invincibility", 16000, 75, 0, 160, 20, EquipmentClass::WARRIOR},
        {"Chaos Breaker Armor", "Absorbs magic attacks", 18000, 80, 15, 170, 22, EquipmentClass::WARRIOR},
        {"Enchanted God Plate +20", "Divine warrior protection", 22000, 90, 20, 190, 28, EquipmentClass::WARRIOR},
        {"Apocalypse Fortress", "Reflects all damage", 28000, 105, 25, 220, 35, EquipmentClass::WARRIOR},
        {"Enchanted Titan King +25", "Unstoppable force", 35000, 125, 30, 260, 45, EquipmentClass::WARRIOR},
        {"Ultimate Destroyer Suit", "Maximum warrior power", 45000, 150, 40, 320, 60, EquipmentClass::WARRIOR},
        {"Omega Tank Armor", "Indestructible", 70000, 220, 60, 450, 100, EquipmentClass::WARRIOR},
        {"Corrupted Demon Plate", "Dark power consumes you", 5800, 42, 0, 85, 4, EquipmentClass::WARRIOR},
        {"Cursed Warlord Armor", "Damage boost but lose HP", 7500, 55, 0, 95, 6, EquipmentClass::WARRIOR},
        {"Infernal Tyrant Plate", "Hell's power flows through", 9200, 60, 5, 115, 11, EquipmentClass::WARRIOR},
        {"Enchanted Bloodlust Armor +12", "Stronger with each kill", 10500, 58, 8, 125, 14, EquipmentClass::WARRIOR},
        {"Corrupted Soul Plate", "Absorbs enemy souls", 12000, 65, 0, 130, 16, EquipmentClass::WARRIOR},
        {"Void Emperor Armor", "Channels void energy", 15500, 72, 12, 155, 22, EquipmentClass::WARRIOR},
        {"Enchanted Chaos Knight +18", "Random powerful effects", 17000, 78, 18, 165, 25, EquipmentClass::WARRIOR},
        {"Corrupted Dragon King Plate", "Dragon's dark power", 19000, 85, 15, 180, 28, EquipmentClass::WARRIOR},
        {"Death Knight Armor", "Undead power surges", 21000, 92, 0, 195, 32, EquipmentClass::WARRIOR},
        {"Enchanted Nightmare Plate +22", "Enemies fear your presence", 25000, 100, 25, 215, 38, EquipmentClass::WARRIOR},
        {"Abyssal Conqueror Armor", "Power from the abyss", 30000, 115, 30, 245, 48, EquipmentClass::WARRIOR},
        {"Corrupted God Slayer Plate", "Kills gods, corrupts soul", 40000, 140, 35, 290, 65, EquipmentClass::WARRIOR},
        {"Enchanted Destruction +30", "Pure annihilation", 55000, 175, 50, 360, 85, EquipmentClass::WARRIOR},
        {"Primordial Chaos Armor", "Ancient chaotic power", 75000, 230, 70, 480, 120, EquipmentClass::WARRIOR},
        {"Corrupted Infinity Plate", "Infinite dark power", 100000, 300, 90, 650, 180, EquipmentClass::WARRIOR},

        // MAGE ARMOR (sorted by cost)
        {"Apprentice Robes", "Basic magic robes", 100, 0, 6, 2, 3, EquipmentClass::MAGE},
        {"Enchanted Robes", "Magically enhanced robes", 380, 0, 15, 5, 5, EquipmentClass::MAGE},
        {"Voidweave Silk", "Absorbs arcane attacks", 650, 0, 18, 8, 6, EquipmentClass::MAGE},
        {"Mystic Shroud", "Protects against magic", 1200, 0, 25, 10, 8, EquipmentClass::MAGE},
        {"Archmage Vestments", "Ultimate mage armor", 1500, 0, 35, 12, 10, EquipmentClass::MAGE},
        {"Arcane Vestments", "Empowered with ancient runes", 2000, 0, 35, 12, 12, EquipmentClass::MAGE},
        {"Celestial Mantle", "Starlight-infused robe", 2300, 0, 40, 15, 14, EquipmentClass::MAGE},
        {"Sorcerer's Cloak", "Boosts spell casting", 2500, 0, 45, 15, 15, EquipmentClass::MAGE},
        {"Ethereal Robes", "Lightweight magical protection", 3000, 0, 50, 18, 18, EquipmentClass::MAGE},
        {"Stormweaver Mantle", "Harnesses elemental fury", 3500, 0, 60, 20, 20, EquipmentClass::MAGE},
        {"Archon Robes", "Blessed by cosmic forces", 5000, 0, 75, 25, 22, EquipmentClass::MAGE},
        {"Astral Ascendant Robes", "Ridiculously OP", 9500, 0, 95, 30, 25, EquipmentClass::MAGE},
        {"Infinity Shroud", "The ultimate mage armor", 20000, 0, 150, 50, 40, EquipmentClass::MAGE},
        {"Spellweave Mantle", "Doubles mana regeneration", 6000, 0, 80, 22, 20, EquipmentClass::MAGE},
        {"Voidcaller Robes", "Channels void energy", 6800, 0, 85, 24, 22, EquipmentClass::MAGE},
        {"Elemental Master Robes", "All elements protect you", 7500, 0, 90, 26, 24, EquipmentClass::MAGE},
        {"Enchanted Arcane Vestments +10", "Enhanced magic defense", 8200, 0, 98, 28, 26, EquipmentClass::MAGE},
        {"Chronomancer Robes", "Slows enemy attacks", 9000, 0, 105, 32, 28, EquipmentClass::MAGE},
        {"Soul Harvester Cloak", "Absorbs enemy mana", 10500, 0, 115, 35, 32, EquipmentClass::MAGE},
        {"Enchanted Celestial Mantle +15", "Starlight shields", 12000, 0, 130, 40, 36, EquipmentClass::MAGE},
        {"Reality Bender Robes", "Warps space around you", 14000, 0, 145, 45, 40, EquipmentClass::MAGE},
        {"Dimensional Shroud", "Exists in multiple planes", 16500, 0, 160, 50, 45, EquipmentClass::MAGE},
        {"Enchanted Infinity Robes +20", "Limitless magic power", 22000, 0, 190, 60, 52, EquipmentClass::MAGE},
        {"Cosmic Archmage Vestments", "Universe-level protection", 28000, 0, 230, 75, 62, EquipmentClass::MAGE},
        {"Enchanted Omniscient Cloak +25", "All-knowing defense", 38000, 0, 290, 95, 78, EquipmentClass::MAGE},
        {"Ultimate Mage Robes", "Maximum magical defense", 50000, 0, 380, 125, 100, EquipmentClass::MAGE},
        {"Omega Spellcaster Armor", "Infinite mana and protection", 85000, 0, 600, 200, 180, EquipmentClass::MAGE},
        {"Corrupted Arcane Robes", "Dark magic enhances power", 5800, 0, 82, 24, 18, EquipmentClass::MAGE},
        {"Forbidden Knowledge Cloak", "Learn forbidden spells", 6500, 0, 88, 26, 20, EquipmentClass::MAGE},
        {"Cursed Spellweaver Mantle", "More power, less sanity", 7200, 0, 95, 28, 22, EquipmentClass::MAGE},
        {"Enchanted Shadow Mage Robes +12", "Darkness empowers", 8500, 0, 108, 32, 28, EquipmentClass::MAGE},
        {"Corrupted Void Vestments", "Void consumes and empowers", 9800, 0, 120, 36, 30, EquipmentClass::MAGE},
        {"Necromancer's Shroud", "Control undead armies", 11000, 0, 125, 38, 32, EquipmentClass::MAGE},
        {"Enchanted Blood Mage Robes +15", "Life force = magic power", 12500, 0, 140, 42, 36, EquipmentClass::MAGE},
        {"Corrupted Chaos Mantle", "Chaos magic runs wild", 14500, 0, 155, 48, 42, EquipmentClass::MAGE},
        {"Demon Pact Vestments", "Demonic power at a price", 17000, 0, 175, 55, 48, EquipmentClass::MAGE},
        {"Enchanted Eldritch Robes +18", "Ancient horrors' power", 20000, 0, 200, 65, 55, EquipmentClass::MAGE},
        {"Corrupted Time Mage Cloak", "Bend time, lose yourself", 23000, 0, 225, 72, 62, EquipmentClass::MAGE},
        {"Entropy Sorcerer Shroud", "Decay and destruction", 27000, 0, 255, 82, 70, EquipmentClass::MAGE},
        {"Enchanted Abyss Mage +22", "Power from the deep", 33000, 0, 295, 98, 82, EquipmentClass::MAGE},
        {"Corrupted Reality Robes", "Warp reality itself", 42000, 0, 350, 115, 95, EquipmentClass::MAGE},
        {"Mad God's Vestments", "Divine insanity power", 55000, 0, 430, 145, 120, EquipmentClass::MAGE},
        {"Enchanted Oblivion Mantle +28", "Erase all magic", 70000, 0, 530, 180, 150, EquipmentClass::MAGE},
        {"Corrupted Cosmic Horror Robes", "Unknowable power", 95000, 0, 680, 240, 200, EquipmentClass::MAGE},
        {"Primordial Chaos Vestments", "First magic ever", 130000, 0, 900, 330, 280, EquipmentClass::MAGE},

        // ROGUE ARMOR (sorted by cost)
        {"Leather Armor", "Light and flexible", 90, 2, 0, 4, 5, EquipmentClass::ROGUE},
        {"Shadow Suit", "Perfect for stealth", 370, 5, 0, 10, 15, EquipmentClass::ROGUE},
        {"Whispercloak", "Silent as the grave", 620, 6, 0, 12, 18, EquipmentClass::ROGUE},
        {"Nightshade Armor", "Legendary rogue armor", 1450, 12, 0, 22, 30, EquipmentClass::ROGUE},
        {"Shadowveil Suit", "Blend with darkness", 1500, 8, 0, 15, 20, EquipmentClass::ROGUE},
        {"Nightstalker Garb", "Perfect for ambushes", 1800, 10, 0, 20, 22, EquipmentClass::ROGUE},
        {"Eclipse Weave", "Reduces detection risk", 2000, 12, 0, 25, 25, EquipmentClass::ROGUE},
        {"Soulshadow Weave", "Absorbs enemy vision", 2100, 14, 0, 30, 28, EquipmentClass::ROGUE},
        {"Silent Step Armor", "Increases dodge chance", 2200, 14, 0, 30, 28, EquipmentClass::ROGUE},
        {"Duskfang Suit", "Frightens enemies", 2500, 16, 0, 35, 30, EquipmentClass::ROGUE},
        {"Specter Garb", "Move like a shadow", 4000, 22, 0, 45, 40, EquipmentClass::ROGUE},
        {"Phantomstrike Armor", "Legendary assassin gear", 9000, 30, 0, 55, 50, EquipmentClass::ROGUE},
        {"Nightveil", "Ultimate rogue armor", 15000, 40, 0, 80, 60, EquipmentClass::ROGUE},
        {"Assassin's Pride", "Critical damage boost", 5500, 24, 0, 48, 45, EquipmentClass::ROGUE},
        {"Poison Master Suit", "Immune to all poison", 6200, 26, 0, 52, 48, EquipmentClass::ROGUE},
        {"Shadow Dancer Garb", "Dodge chance +50%", 7000, 28, 0, 58, 52, EquipmentClass::ROGUE},
        {"Enchanted Nightshade +10", "Enhanced stealth", 8000, 32, 5, 62, 58, EquipmentClass::ROGUE},
        {"Invisible Death Cloak", "Cannot be detected", 9500, 35, 0, 68, 65, EquipmentClass::ROGUE},
        {"Time Thief Armor", "Move twice as fast", 11000, 38, 0, 75, 72, EquipmentClass::ROGUE},
        {"Enchanted Phantom Suit +15", "Phases through walls", 13000, 42, 10, 85, 80, EquipmentClass::ROGUE},
        {"Dimensional Assassin Gear", "Strike from other realms", 16000, 48, 0, 95, 90, EquipmentClass::ROGUE},
        {"Perfect Shadow Armor", "100% evasion in darkness", 19000, 52, 15, 110, 105, EquipmentClass::ROGUE},
        {"Enchanted Void Cloak +20", "Ultimate stealth power", 24000, 58, 20, 130, 125, EquipmentClass::ROGUE},
        {"Omega Assassin Suit", "Untouchable and deadly", 32000, 68, 25, 160, 150, EquipmentClass::ROGUE},
        {"Enchanted Death's Shadow +25", "Absolute invisibility", 42000, 80, 35, 200, 185, EquipmentClass::ROGUE},
        {"Ultimate Rogue Armor", "Master of stealth", 55000, 95, 45, 250, 230, EquipmentClass::ROGUE},
        {"Beyond Mortal Shadows", "Transcendent assassin", 90000, 150, 70, 400, 380, EquipmentClass::ROGUE},
        {"Corrupted Assassin Suit", "Dark stealth powers", 5800, 26, 0, 50, 50, EquipmentClass::ROGUE},
        {"Cursed Shadow Cloak", "Invisibility with a cost", 6500, 28, 0, 55, 55, EquipmentClass::ROGUE},
        {"Blood Assassin Garb", "Drain life on backstab", 7500, 30, 0, 60, 62, EquipmentClass::ROGUE},
        {"Enchanted Demon Hunter +12", "Hunt demons with dark power", 8500, 34, 8, 68, 70, EquipmentClass::ROGUE},
        {"Corrupted Nightstalker Armor", "Darkness amplifies power", 10000, 36, 0, 75, 78, EquipmentClass::ROGUE},
        {"Venomweave Suit", "Poison everything you touch", 11500, 40, 0, 82, 85, EquipmentClass::ROGUE},
        {"Enchanted Soul Thief +15", "Steal enemy essence", 13500, 44, 12, 92, 95, EquipmentClass::ROGUE},
        {"Corrupted Eclipse Armor", "Total darkness surrounds", 16000, 50, 0, 105, 110, EquipmentClass::ROGUE},
        {"Chaos Assassin Garb", "Random devastating effects", 18500, 54, 15, 115, 120, EquipmentClass::ROGUE},
        {"Enchanted Reaper Cloak +18", "Death walks with you", 22000, 60, 18, 135, 140, EquipmentClass::ROGUE},
        {"Corrupted Void Assassin Suit", "Strike from nowhere", 26000, 66, 22, 150, 160, EquipmentClass::ROGUE},
        {"Nightmare Stalker Armor", "Enemies live in fear", 31000, 72, 28, 170, 180, EquipmentClass::ROGUE},
        {"Enchanted Oblivion Shadow +22", "Erase your existence", 38000, 82, 35, 195, 210, EquipmentClass::ROGUE},
        {"Corrupted Dimensional Killer", "Kill across dimensions", 48000, 92, 42, 230, 245, EquipmentClass::ROGUE},
        {"Abyssal Assassin Gear", "Abyss empowers strikes", 62000, 110, 55, 280, 295, EquipmentClass::ROGUE},
        {"Enchanted Perfect Death +28", "One with death itself", 80000, 135, 68, 350, 360, EquipmentClass::ROGUE},
        {"Corrupted Infinity Shadows", "Infinite stealth power", 120000, 180, 95, 480, 500, EquipmentClass::ROGUE},

        // CLERIC ARMOR (sorted by cost)
        {"Initiate's Vestments", "Basic holy armor", 110, 2, 4, 5, 1, EquipmentClass::CLERIC},
        {"Holy Plate", "Blessed armor", 420, 5, 10, 15, 2, EquipmentClass::CLERIC},
        {"Blessed Radiant Mail", "Glows with holy power", 700, 4, 12, 18, 6, EquipmentClass::CLERIC},
        {"Sanctuary Plate", "Protects the faithful", 1200, 6, 18, 20, 8, EquipmentClass::CLERIC},
        {"Divine Aegis", "Ultimate holy protection", 1550, 15, 25, 35, 5, EquipmentClass::CLERIC},
        {"Paladin's Guard", "Blessed with light", 1800, 10, 25, 28, 10, EquipmentClass::CLERIC},
        {"Holy Sentinel Armor", "Resists dark magic", 2200, 14, 32, 35, 12, EquipmentClass::CLERIC},
        {"Armor of Sacred Valor", "Worn by holy champions", 2500, 12, 28, 40, 10, EquipmentClass::CLERIC},
        {"Divine Radiance Mail", "Shines with holy light", 3000, 18, 40, 40, 14, EquipmentClass::CLERIC},
        {"Seraphic Plate", "Armor of angels", 3500, 20, 45, 45, 15, EquipmentClass::CLERIC},
        {"Celestial Aegis", "Top-tier divine armor", 5000, 25, 60, 60, 18, EquipmentClass::CLERIC},
        {"Lightforged Aegisplate", "Divine-tier protection", 10000, 35, 50, 75, 18, EquipmentClass::CLERIC},
        {"Heavenward Armor", "Ultimate cleric armor", 20000, 50, 120, 120, 30, EquipmentClass::CLERIC},
        {"Exorcist's Mail", "Banishes evil on contact", 6500, 28, 65, 65, 20, EquipmentClass::CLERIC},
        {"Guardian Angel Plate", "Resurrects on death once", 7500, 30, 70, 70, 22, EquipmentClass::CLERIC},
        {"Holy Crusader Armor", "Extra damage to undead", 8200, 32, 75, 75, 24, EquipmentClass::CLERIC},
        {"Enchanted Divine Mail +10", "Enhanced holy power", 9500, 38, 85, 85, 26, EquipmentClass::CLERIC},
        {"Blessed Protector Plate", "Heals allies nearby", 11000, 40, 95, 95, 28, EquipmentClass::CLERIC},
        {"Judgment Armor", "Smites attackers", 12500, 42, 100, 100, 30, EquipmentClass::CLERIC},
        {"Enchanted Seraphic Plate +15", "Angelic protection", 15000, 48, 115, 115, 35, EquipmentClass::CLERIC},
        {"Archangel's Blessing", "Divine shields", 18000, 52, 130, 130, 40, EquipmentClass::CLERIC},
        {"Holy Emperor Armor", "Commands divine power", 22000, 58, 150, 150, 48, EquipmentClass::CLERIC},
        {"Enchanted God's Champion +20", "Ultimate holy warrior", 28000, 68, 180, 180, 58, EquipmentClass::CLERIC},
        {"Divine Intervention Plate", "God protects you", 35000, 80, 220, 220, 70, EquipmentClass::CLERIC},
        {"Enchanted Heaven's Wrath +25", "Apocalyptic protection", 45000, 95, 270, 270, 88, EquipmentClass::CLERIC},
        {"Ultimate Salvation Armor", "Blessed beyond measure", 60000, 120, 350, 350, 115, EquipmentClass::CLERIC},
        {"Omega Holy Plate", "God-tier divine armor", 95000, 180, 550, 550, 200, EquipmentClass::CLERIC},
        {"Corrupted Paladin Armor", "Fallen holy power", 6500, 30, 68, 68, 22, EquipmentClass::CLERIC},
        {"Dark Crusader Plate", "Holy power twisted dark", 7500, 32, 78, 78, 26, EquipmentClass::CLERIC},
        {"Enchanted Zealot Mail +12", "Fanatical divine power", 8800, 36, 88, 88, 28, EquipmentClass::CLERIC},
        {"Corrupted Angel Armor", "Fallen angel's blessing", 10500, 40, 98, 98, 32, EquipmentClass::CLERIC},
        {"Blood Saint Vestments", "Holy power from sacrifice", 12000, 44, 108, 108, 36, EquipmentClass::CLERIC},
        {"Enchanted Judgment Plate +15", "Divine wrath unleashed", 14000, 50, 125, 125, 42, EquipmentClass::CLERIC},
        {"Corrupted Heaven's Gate Armor", "Dark heaven's power", 17000, 55, 140, 140, 48, EquipmentClass::CLERIC},
        {"Heretic's Divine Plate", "Forbidden holy magic", 20000, 60, 160, 160, 55, EquipmentClass::CLERIC},
        {"Enchanted War Saint +18", "Holy warrior supreme", 24000, 68, 185, 185, 65, EquipmentClass::CLERIC},
        {"Corrupted Seraphim Armor", "Dark angelic power", 29000, 75, 210, 210, 75, EquipmentClass::CLERIC},
        {"Chaos Priest Vestments", "Order and chaos combined", 35000, 85, 245, 245, 88, EquipmentClass::CLERIC},
        {"Enchanted Divine Emperor +22", "Rule with holy might", 43000, 100, 290, 290, 105, EquipmentClass::CLERIC},
        {"Corrupted God Armor", "Twisted divine essence", 55000, 115, 340, 340, 125, EquipmentClass::CLERIC},
        {"Abyssal Crusader Plate", "Holy abyss power", 70000, 140, 410, 410, 155, EquipmentClass::CLERIC},
        {"Enchanted Apocalypse Saint +28", "End times champion", 90000, 165, 500, 500, 190, EquipmentClass::CLERIC},
        {"Corrupted Ultimate Divine", "All holy power corrupted", 125000, 210, 650, 650, 250, EquipmentClass::CLERIC},

        // RANGER ARMOR (sorted by cost)
        {"Hunter's Garb", "Light ranger armor", 95, 3, 0, 5, 4, EquipmentClass::RANGER},
        {"Wildwood Armor", "Nature-blessed armor", 390, 8, 3, 12, 10, EquipmentClass::RANGER},
        {"Windrunner Garb", "Swift and silent", 620, 6, 0, 9, 16, EquipmentClass::RANGER},
        {"Shadowwood Cloak", "Blend with forest shadows", 1500, 6, 3, 12, 14, EquipmentClass::RANGER},
        {"Forestlord's Mail", "Legendary ranger armor", 1500, 18, 8, 25, 22, EquipmentClass::RANGER},
        {"Hunter's Vestments", "Increases ranged attack", 1800, 8, 4, 16, 16, EquipmentClass::RANGER},
        {"Elven Hunter Armor", "Crafted by elven smiths", 2000, 10, 5, 20, 18, EquipmentClass::RANGER},
        {"Stormleaf Harness", "Nature's fury made armor", 2100, 12, 5, 22, 18, EquipmentClass::RANGER},
        {"Forestwarden Garb", "Nature-protection", 2200, 12, 6, 25, 20, EquipmentClass::RANGER},
        {"Wildheart Harness", "Boosts agility", 2500, 14, 8, 30, 22, EquipmentClass::RANGER},
        {"Naturelord's Mail", "Legendary ranger armor", 4000, 20, 10, 40, 30, EquipmentClass::RANGER},
        {"Sylvan Warden Mail", "Elite forest guardian gear", 9000, 28, 12, 48, 35, EquipmentClass::RANGER},
        {"Worldtree Plate", "Insanely OP ranger armor", 15000, 45, 20, 90, 50, EquipmentClass::RANGER},
        {"Eagle Eye Vest", "Perfect aim boost", 5500, 22, 8, 42, 32, EquipmentClass::RANGER},
        {"Thunderhawk Armor", "Lightning speed", 6200, 24, 10, 45, 35, EquipmentClass::RANGER},
        {"Beast Master Garb", "Commands animals", 7000, 26, 12, 50, 38, EquipmentClass::RANGER},
        {"Enchanted Forest Mail +10", "Enhanced nature power", 8000, 30, 15, 55, 42, EquipmentClass::RANGER},
        {"Phoenix Feather Cloak", "Fire resistance +100%", 9500, 32, 18, 62, 48, EquipmentClass::RANGER},
        {"Wind Spirit Armor", "Increased movement speed", 11000, 35, 20, 68, 52, EquipmentClass::RANGER},
        {"Enchanted Wildwood +15", "Ultimate forest guardian", 13000, 38, 25, 75, 58, EquipmentClass::RANGER},
        {"Dragon Hunter Vest", "Extra damage to dragons", 16000, 42, 30, 85, 65, EquipmentClass::RANGER},
        {"Perfect Sniper Armor", "Never miss", 19000, 48, 35, 95, 72, EquipmentClass::RANGER},
        {"Enchanted Worldtree Plate +20", "Nature's champion", 24000, 52, 42, 110, 82, EquipmentClass::RANGER},
        {"Elemental Ranger Suit", "All elements aid you", 30000, 58, 50, 130, 95, EquipmentClass::RANGER},
        {"Enchanted Cosmic Hunter +25", "Shoots across space", 40000, 68, 65, 160, 115, EquipmentClass::RANGER},
        {"Ultimate Ranger Armor", "Master of the hunt", 55000, 82, 85, 200, 145, EquipmentClass::RANGER},
        {"Omega Marksman Suit", "Absolute precision", 88000, 125, 130, 320, 230, EquipmentClass::RANGER},
        {"Corrupted Forest Guardian", "Dark nature powers", 6000, 24, 10, 48, 38, EquipmentClass::RANGER},
        {"Cursed Hunter's Pride", "Beast power at a cost", 6800, 26, 12, 52, 42, EquipmentClass::RANGER},
        {"Shadow Ranger Armor", "Blend with any shadow", 7800, 28, 14, 58, 48, EquipmentClass::RANGER},
        {"Enchanted Predator Suit +12", "Hunt anything", 9000, 32, 18, 65, 54, EquipmentClass::RANGER},
        {"Corrupted Druid Vestments", "Twisted nature magic", 10500, 34, 20, 72, 60, EquipmentClass::RANGER},
        {"Blood Hunter Garb", "Track by blood scent", 12000, 38, 24, 78, 66, EquipmentClass::RANGER},
        {"Enchanted Wild King +15", "Command all beasts", 14000, 42, 28, 88, 75, EquipmentClass::RANGER},
        {"Corrupted Phoenix Armor", "Dark flame rebirth", 17000, 46, 32, 98, 82, EquipmentClass::RANGER},
        {"Demon Hunter Vestments", "Slay demons with ease", 20000, 50, 38, 108, 92, EquipmentClass::RANGER},
        {"Enchanted Storm Hunter +18", "Control weather", 24000, 56, 45, 122, 105, EquipmentClass::RANGER},
        {"Corrupted Dragon Slayer Armor", "Dark dragon power", 29000, 62, 52, 140, 120, EquipmentClass::RANGER},
        {"Chaos Ranger Suit", "Random powerful buffs", 35000, 70, 60, 158, 135, EquipmentClass::RANGER},
        {"Enchanted Sniper God +22", "Never miss anything", 43000, 78, 72, 182, 158, EquipmentClass::RANGER},
        {"Corrupted Nature's Wrath", "Corrupted nature fury", 55000, 90, 88, 215, 185, EquipmentClass::RANGER},
        {"Void Hunter Armor", "Hunt across dimensions", 70000, 105, 105, 260, 220, EquipmentClass::RANGER},
        {"Enchanted Perfect Shot +28", "100% critical always", 92000, 130, 135, 330, 270, EquipmentClass::RANGER},
        {"Corrupted Infinity Ranger", "Infinite dark range", 130000, 170, 180, 450, 360, EquipmentClass::RANGER},

        // UNIVERSAL ARMOR (sorted by cost)
        {"Traveler's Cloak", "Good for any adventurer", 180, 3, 2, 6, 3, EquipmentClass::ALL},
        {"Mystic Chain", "Magic enhanced chainmail", 550, 8, 8, 15, 5, EquipmentClass::ALL},
        {"Arcane Chainweave", "Light yet powerful", 700, 6, 8, 18, 8, EquipmentClass::ALL},
        {"Traveler's Armor", "Good for any adventurer", 1000, 8, 10, 20, 10, EquipmentClass::ALL},
        {"Mystic Plate", "Magic-resistant armor", 2200, 12, 20, 30, 15, EquipmentClass::ALL},
        {"Dragonsteel Brigandine", "Forged with draconic magic", 2800, 15, 12, 30, 12, EquipmentClass::ALL},
        {"Eternal Guard", "Durable for all classes", 3000, 18, 25, 40, 18, EquipmentClass::ALL},
        {"Omniguard Suit", "Universal defensive power", 3500, 20, 30, 45, 20, EquipmentClass::ALL},
        {"Celestial Guard", "Blessed for all adventurers", 5000, 25, 35, 55, 25, EquipmentClass::ALL},
        {"Infinity Armor", "Ridiculously OP universal armor", 12000, 40, 80, 100, 40, EquipmentClass::ALL},
        {"Godskin Cloak", "Worn by divine beings", 15000, 40, 35, 55, 25, EquipmentClass::ALL},
        {"Godslayer Plate", "Ultimate universal armor", 25000, 80, 150, 200, 80, EquipmentClass::ALL},
        {"Versatile Champion Armor", "Adapts to playstyle", 8000, 30, 40, 60, 30, EquipmentClass::ALL},
        {"Elemental Fusion Plate", "All elements protect", 10000, 35, 50, 75, 35, EquipmentClass::ALL},
        {"Enchanted Omni-Armor +10", "Enhanced universal defense", 14000, 45, 90, 110, 48, EquipmentClass::ALL},
        {"Soul Guardian Suit", "Protects soul and body", 16000, 50, 100, 125, 52, EquipmentClass::ALL},
        {"Dimensional Protector", "Exists in all dimensions", 19000, 55, 115, 145, 58, EquipmentClass::ALL},
        {"Enchanted Harmony Plate +15", "Perfect balance", 23000, 65, 135, 170, 68, EquipmentClass::ALL},
        {"Cosmic Entity Armor", "Universe-level defense", 28000, 75, 160, 200, 80, EquipmentClass::ALL},
        {"Enchanted God Armor +20", "Divine universal protection", 35000, 90, 190, 240, 95, EquipmentClass::ALL},
        {"Absolute Defense Suit", "Nearly invincible", 45000, 110, 230, 290, 115, EquipmentClass::ALL},
        {"Enchanted Infinity Guard +25", "Limitless protection", 60000, 135, 280, 360, 145, EquipmentClass::ALL},
        {"Omega Universal Armor", "Ultimate defense", 80000, 170, 350, 450, 185, EquipmentClass::ALL},
        {"Existence Shield", "Nothing can harm you", 110000, 220, 450, 600, 250, EquipmentClass::ALL},
        {"Beyond God Tier Armor", "Transcendent protection", 180000, 350, 700, 950, 400, EquipmentClass::ALL},
        {"Corrupted Universal Plate", "Dark all-class power", 16000, 52, 110, 135, 60, EquipmentClass::ALL},
        {"Cursed Omni-Armor", "Powerful but dangerous", 18000, 58, 125, 155, 68, EquipmentClass::ALL},
        {"Enchanted Versatile King +12", "Adapts perfectly", 21000, 68, 145, 180, 78, EquipmentClass::ALL},
        {"Corrupted Chaos Guardian", "Chaotic protection", 26000, 78, 170, 215, 92, EquipmentClass::ALL},
        {"Blood Emperor Armor", "Life force = power", 32000, 92, 200, 250, 108, EquipmentClass::ALL},
        {"Enchanted Demon Lord +15", "Demonic universal power", 39000, 105, 235, 295, 128, EquipmentClass::ALL},
        {"Corrupted Reality Suit", "Bend reality around you", 48000, 125, 275, 345, 155, EquipmentClass::ALL},
        {"Void Emperor Universal", "Void protects all", 58000, 145, 320, 410, 185, EquipmentClass::ALL},
        {"Enchanted Abyssal King +18", "Abyss power for all", 72000, 170, 380, 485, 220, EquipmentClass::ALL},
        {"Corrupted Time Lord Armor", "Control time itself", 88000, 200, 440, 570, 265, EquipmentClass::ALL},
        {"Chaos Incarnate Suit", "Pure chaos power", 105000, 235, 520, 680, 315, EquipmentClass::ALL},
        {"Enchanted Mad God +22", "Insane divine power", 130000, 280, 610, 810, 380, EquipmentClass::ALL},
        {"Corrupted Infinity Armor", "Infinite dark power", 160000, 330, 730, 970, 460, EquipmentClass::ALL},
        {"Primordial Existence Suit", "First armor ever created", 200000, 400, 880, 1200, 560, EquipmentClass::ALL},
        {"Enchanted Oblivion Guard +28", "Erases all damage", 250000, 500, 1100, 1500, 700, EquipmentClass::ALL},
        {"Corrupted Ultimate Reality", "Twisted ultimate power", 350000, 650, 1400, 1900, 900, EquipmentClass::ALL},
        {"Transcendent Universal Armor", "Beyond comprehension", 500000, 900, 2000, 2700, 1300, EquipmentClass::ALL}
    };
    
    bool shopping = true;
    while (shopping) {
        ConsoleUI::clearScreen();
        ConsoleUI::printHeader("=== ARMOR SHOP ===");
        ConsoleUI::setColor(ConsoleUI::Color::YELLOW, ConsoleUI::Color::BLACK);
        cout << "Your Gold: " << player.getGold() << " | Your Class: " << player.getClassName();
        ConsoleUI::setColor(ConsoleUI::Color::WHITE, ConsoleUI::Color::BLACK);
        cout << endl;
        ConsoleUI::printSeparator();
        
        // Filter armor to only show those available to the player's class
        vector<int> availableIndices;
        for (size_t i = 0; i < armors.size(); i++) {
            auto& a = armors[i];
            
            // Check if player can use this armor
            EquipmentClass reqClass = a.reqClass;
            bool canUse = (reqClass == EquipmentClass::ALL);
            if (!canUse) {
                if (player.getClassName() == "Warrior") canUse = (reqClass == EquipmentClass::WARRIOR);
                else if (player.getClassName() == "Mage") canUse = (reqClass == EquipmentClass::MAGE);
                else if (player.getClassName() == "Rogue") canUse = (reqClass == EquipmentClass::ROGUE);
                else if (player.getClassName() == "Cleric") canUse = (reqClass == EquipmentClass::CLERIC);
                else if (player.getClassName() == "Ranger") canUse = (reqClass == EquipmentClass::RANGER);
            }
            
            // Only add to list if player can use it
            if (canUse) {
                availableIndices.push_back(i);
            }
        }
        
        // Display only available armor
        for (size_t idx = 0; idx < availableIndices.size(); idx++) {
            auto& a = armors[availableIndices[idx]];
            
            ConsoleUI::setColor(ConsoleUI::Color::GREEN, ConsoleUI::Color::BLACK);
            cout << (idx + 1) << ". " << a.name << " - " << a.price << " gold";
            ConsoleUI::setColor(ConsoleUI::Color::WHITE, ConsoleUI::Color::BLACK);
            cout << "\n   " << a.description;
            cout << " [";
            if (a.strBonus != 0) cout << (a.strBonus > 0 ? "+" : "") << a.strBonus << " STR ";
            if (a.magBonus != 0) cout << (a.magBonus > 0 ? "+" : "") << a.magBonus << " MAG ";
            if (a.defBonus != 0) cout << (a.defBonus > 0 ? "+" : "") << a.defBonus << " DEF ";
            if (a.spdBonus != 0) cout << (a.spdBonus > 0 ? "+" : "") << a.spdBonus << " SPD ";
            cout << "]\n";
            
            string classReq = "All Classes";
            if (a.reqClass == EquipmentClass::WARRIOR) classReq = "Warrior Only";
            else if (a.reqClass == EquipmentClass::MAGE) classReq = "Mage Only";
            else if (a.reqClass == EquipmentClass::ROGUE) classReq = "Rogue Only";
            else if (a.reqClass == EquipmentClass::CLERIC) classReq = "Cleric Only";
            else if (a.reqClass == EquipmentClass::RANGER) classReq = "Ranger Only";
            
            ConsoleUI::setColor(ConsoleUI::Color::CYAN, ConsoleUI::Color::BLACK);
            cout << "   Class: " << classReq;
            ConsoleUI::setColor(ConsoleUI::Color::WHITE, ConsoleUI::Color::BLACK);
            cout << "\n" << endl;
        }
        
        cout << (availableIndices.size() + 1) << ". Leave Shop" << endl;
        ConsoleUI::printSeparator();
        cout << "Choice: ";
        
        int choice;
        cin >> choice;
        
        if (choice == (int)availableIndices.size() + 1) {
            shopping = false;
            ConsoleUI::printInfo("Thanks for visiting!");
        } else if (choice > 0 && choice <= (int)availableIndices.size()) {
            auto& a = armors[availableIndices[choice - 1]];
            
            if (player.getGold() >= a.price) {
                player.addGold(-a.price);
                Item newItem(a.name, a.description, ItemType::ARMOR, a.price / 2, a.strBonus, a.magBonus, a.defBonus, a.spdBonus, a.reqClass);
                player.getInventory().addItem(newItem);
                ConsoleUI::printSuccess("Purchased " + a.name + "!");
                cout << "\nPress Enter to continue...";
                cin.ignore();
                cin.get();
            } else {
                ConsoleUI::printError("Not enough gold! You need " + to_string(a.price) + " gold.");
                cout << "\nPress Enter to continue...";
                cin.ignore();
                cin.get();
            }
        } else {
            ConsoleUI::printError("Invalid choice!");
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
    }
}
