#include "WeaponShop.h"
#include "../../Core/ConsoleUI.h"
#include <iostream>
#include <vector>

using namespace std;

struct WeaponShopItem {
    string name;
    string description;
    int price;
    int strBonus;
    int magBonus;
    int defBonus;
    int spdBonus;
    EquipmentClass reqClass;
};

void openWeaponShop(Player& player) {
    vector<WeaponShopItem> weapons = {
        // WARRIOR WEAPONS (sorted by cost)
        {"Rusty Sword", "Seen better days", 50, 8, 0, 0, 0, EquipmentClass::WARRIOR},
        {"Iron Sword", "A basic warrior's blade", 100, 5, 0, 0, 0, EquipmentClass::WARRIOR},
        {"Iron Longsword", "Reliable warrior blade", 150, 18, 0, 0, 0, EquipmentClass::WARRIOR},
        {"Steel Greatsword", "A heavy warrior weapon", 300, 12, 0, 0, -2, EquipmentClass::WARRIOR},
        {"Steel Greatsword", "Heavy two-handed blade", 450, 35, 0, 0, -1, EquipmentClass::WARRIOR},
        {"Titanium Warhammer", "Crushes armor like paper", 800, 45, 0, 0, 1, EquipmentClass::WARRIOR},
        {"Legendary Claymore", "Ultimate warrior blade", 1500, 35, 0, 0, 5, EquipmentClass::WARRIOR},
        {"Bloodmoon Cleaver", "Grows stronger with kills", 1500, 55, 0, 10, 3, EquipmentClass::WARRIOR},
        {"Frostbite Blade", "Freezes enemies solid", 1600, 58, 0, 8, 4, EquipmentClass::WARRIOR},
        {"Bloodfang Greatsword", "Drains life with each hit", 1600, 42, 0, 0, 6, EquipmentClass::WARRIOR},
        {"Dragonslayer", "Forged to kill dragons", 1800, 65, 0, 0, 2, EquipmentClass::WARRIOR},
        {"Ragnarok Cleaver", "Cleave enemies like gods", 1800, 38, 0, 0, 4, EquipmentClass::WARRIOR},
        {"Volcanic Cleaver", "Burns with inner fire", 1900, 62, 0, 10, 5, EquipmentClass::WARRIOR},
        {"Earthsplitter", "Smashes the ground and foes", 2000, 48, 0, 0, -1, EquipmentClass::WARRIOR},
        {"Hammer of the Fallen", "Empowered by fallen warriors", 2100, 45, 0, 0, 3, EquipmentClass::WARRIOR},
        {"Doomhammer", "Legendary weapon of conquest", 2200, 68, 0, 12, 6, EquipmentClass::WARRIOR},
        {"Titan Hammer", "Weight of a mountain", 2200, 50, 0, 0, 2, EquipmentClass::WARRIOR},
        {"Stormbreaker Axe", "Summons lightning strikes", 2500, 72, 0, 15, 8, EquipmentClass::WARRIOR},
        {"Soulreaver Axe", "Steals life force", 2800, 75, 0, 15, 5, EquipmentClass::WARRIOR},
        {"Colossus Fang", "Massive crushing power", 2900, 55, 0, 0, 0, EquipmentClass::WARRIOR},
        {"Executioner's Edge", "One-hit critical chance", 3000, 80, 0, 20, 10, EquipmentClass::WARRIOR},
        {"Infernal Blade", "Burns enemies to ash", 3200, 65, 0, 0, 7, EquipmentClass::WARRIOR},
        {"Colossus Fist", "Gauntlet weapon of titans", 3500, 88, 0, 25, 12, EquipmentClass::WARRIOR},
        {"Titanforge Sword", "Forged in divine fire", 3500, 72, 0, 0, 8, EquipmentClass::WARRIOR},
        {"Oblivion Axe", "Chops through reality itself", 4000, 70, 0, 0, 10, EquipmentClass::WARRIOR},
        {"Ragnarok Blade", "Brings the end of days", 5000, 110, 0, 35, 18, EquipmentClass::WARRIOR},
        {"Infinity Edge", "Cuts through dimensions", 8000, 150, 0, 50, 25, EquipmentClass::WARRIOR},
        {"Doombringer", "Legendary end-of-all weapon", 10000, 120, 0, 0, 20, EquipmentClass::WARRIOR},
        {"Worldbreaker Maul", "ABSURDLY OP hammer", 12000, 180, 0, 30, 15, EquipmentClass::WARRIOR},
        {"Godkiller Greatsword", "Slays divine beings", 15000, 220, 0, 80, 40, EquipmentClass::WARRIOR},
        {"Apocalypse Blade", "The ultimate warrior weapon", 25000, 350, 0, 150, 75, EquipmentClass::WARRIOR},
        {"Soulforge Destroyer", "Absorbs enemy souls", 6500, 125, 0, 40, 22, EquipmentClass::WARRIOR},
        {"Chaos Reaver", "Spreads destruction", 7500, 140, 0, 45, 28, EquipmentClass::WARRIOR},
        {"Berserker's Rage", "Increases damage when low HP", 5500, 115, 0, 38, 20, EquipmentClass::WARRIOR},
        {"Flamebrand Axe", "Ignites on every strike", 4500, 95, 0, 28, 16, EquipmentClass::WARRIOR},
        {"Frostbane Hammer", "Freezes and shatters", 4800, 102, 0, 32, 18, EquipmentClass::WARRIOR},
        {"Thundercrash Maul", "Lightning AOE on impact", 6000, 118, 0, 42, 24, EquipmentClass::WARRIOR},
        {"Voidblade Greatsword", "Cuts through dimensions", 8500, 155, 0, 55, 30, EquipmentClass::WARRIOR},
        {"Dragon's Wrath", "Breathes fire with strikes", 9500, 165, 0, 60, 35, EquipmentClass::WARRIOR},
        {"Enchanted Warblade +10", "Magically enhanced power", 11000, 175, 10, 65, 38, EquipmentClass::WARRIOR},
        {"Hellfire Claymore", "Burns with eternal flames", 13000, 195, 0, 75, 42, EquipmentClass::WARRIOR},
        {"Moonlight Greatsword", "Holy damage at night", 14000, 205, 15, 70, 45, EquipmentClass::WARRIOR},
        {"Vampire Lord's Blade", "Drains life massively", 16000, 230, 0, 85, 50, EquipmentClass::WARRIOR},
        {"Enchanted Titan Axe +15", "Overwhelming strength", 18000, 260, 20, 95, 55, EquipmentClass::WARRIOR},
        {"Cosmic Annihilator Sword", "Erases existence", 22000, 300, 25, 120, 65, EquipmentClass::WARRIOR},
        {"God Slayer Axe", "Kills immortals", 28000, 380, 30, 140, 80, EquipmentClass::WARRIOR},
        {"Eternal Damnation", "Curses enemies permanently", 32000, 420, 40, 160, 90, EquipmentClass::WARRIOR},
        {"Omni-Destroyer", "Ultimate destruction weapon", 45000, 600, 80, 250, 150, EquipmentClass::WARRIOR},

        // MAGE WEAPONS (sorted by cost)
        {"Wooden Staff", "Apprentice's first staff", 80, 0, 12, 0, 2, EquipmentClass::MAGE},
        {"Wooden Staff", "A simple magical staff", 100, 0, 8, 0, 2, EquipmentClass::MAGE},
        {"Crystal Wand", "Channels arcane energy", 200, 0, 25, 0, 5, EquipmentClass::MAGE},
        {"Crystal Staff", "A staff of pure magic", 400, 0, 18, 0, 3, EquipmentClass::MAGE},
        {"Archmage's Staff", "Powerful magical focus", 600, 0, 50, 0, 12, EquipmentClass::MAGE},
        {"Celestial Rod", "Starlight incarnate", 900, 0, 60, 0, 15, EquipmentClass::MAGE},
        {"Phoenix Wand", "Resurrects from ashes", 1400, 0, 65, 0, 18, EquipmentClass::MAGE},
        {"Archmage Scepter", "Staff of ultimate power", 1500, 0, 40, 0, 8, EquipmentClass::MAGE},
        {"Stormcaller Staff", "Commands the weather", 1800, 0, 70, 0, 20, EquipmentClass::MAGE},
        {"Soulbinder Wand", "Traps souls for power", 1800, 0, 42, 0, 10, EquipmentClass::MAGE},
        {"Voidstar Scepter", "Harnesses void magic", 2000, 0, 80, 0, 20, EquipmentClass::MAGE},
        {"Netherbane Scepter", "Destroys dark magic", 2200, 0, 78, 0, 22, EquipmentClass::MAGE},
        {"Phoenix Rod", "Rebirth through fire", 2200, 0, 48, 0, 9, EquipmentClass::MAGE},
        {"Netherflare Staff", "Flames from another dimension", 2500, 0, 55, 0, 12, EquipmentClass::MAGE},
        {"Timewarp Rod", "Bends time itself", 2800, 0, 88, 0, 26, EquipmentClass::MAGE},
        {"Voidcaster", "Channels void energy", 3000, 0, 60, 0, 15, EquipmentClass::MAGE},
        {"Infinity Orb", "Reality-bending artifact", 3000, 0, 95, 0, 28, EquipmentClass::MAGE},
        {"Astral Devastator", "Channels cosmic power", 3500, 0, 100, 0, 32, EquipmentClass::MAGE},
        {"Eclipse Wand", "Shadow and light combined", 3600, 0, 65, 0, 18, EquipmentClass::MAGE},
        {"Astral Scepter", "Manipulates stars", 4000, 0, 70, 0, 20, EquipmentClass::MAGE},
        {"Voidheart Orb", "Consumes magic itself", 4200, 0, 115, 0, 38, EquipmentClass::MAGE},
        {"Stormcaller Rod", "Unleashes tempests", 4200, 0, 68, 0, 22, EquipmentClass::MAGE},
        {"Chronomancer Staff", "Bends time", 5000, 0, 80, 0, 25, EquipmentClass::MAGE},
        {"Celestial Wand", "Taps pure cosmic energy", 5500, 0, 90, 0, 30, EquipmentClass::MAGE},
        {"Singularity Staff", "Creates black holes", 6000, 0, 140, 0, 50, EquipmentClass::MAGE},
        {"Eternity Wand", "Infinite magical power", 9000, 0, 175, 0, 65, EquipmentClass::MAGE},
        {"Cosmic Annihilator", "RIDICULOUSLY OP staff", 13000, 0, 200, 0, 60, EquipmentClass::MAGE},
        {"Reality Shaper", "Rewrites existence", 18000, 0, 280, 0, 110, EquipmentClass::MAGE},
        {"Infinity Scepter", "The ultimate mage weapon", 20000, 0, 200, 0, 50, EquipmentClass::MAGE},
        {"Omniscient Eye", "Knows all spells", 30000, 0, 450, 0, 200, EquipmentClass::MAGE},
        {"Arcane Amplifier Rod", "Doubles spell power", 5500, 0, 125, 0, 45, EquipmentClass::MAGE},
        {"Frostfire Staff", "Fire and ice combined", 6500, 0, 135, 0, 52, EquipmentClass::MAGE},
        {"Shadow Weaver Wand", "Manipulates darkness", 7000, 0, 145, 0, 55, EquipmentClass::MAGE},
        {"Lightning Conduit", "Pure electrical energy", 7800, 0, 155, 0, 58, EquipmentClass::MAGE},
        {"Enchanted Arcane Staff +10", "Enhanced magic flow", 8500, 0, 165, 10, 62, EquipmentClass::MAGE},
        {"Chaos Orb", "Random devastating spells", 9500, 0, 180, 0, 68, EquipmentClass::MAGE},
        {"Soul Harvester Staff", "Steals enemy mana", 10500, 0, 190, 0, 72, EquipmentClass::MAGE},
        {"Elemental Fusion Wand", "All elements at once", 11500, 0, 205, 0, 78, EquipmentClass::MAGE},
        {"Enchanted Voidstar +15", "Reality warping power", 14000, 0, 240, 15, 88, EquipmentClass::MAGE},
        {"Dimensional Rift Staff", "Opens portals to power", 16000, 0, 260, 0, 95, EquipmentClass::MAGE},
        {"Infinite Mana Crystal", "Never runs out of mana", 19000, 0, 300, 20, 105, EquipmentClass::MAGE},
        {"Archmage's Legacy", "Knowledge of ancients", 21000, 0, 330, 25, 115, EquipmentClass::MAGE},
        {"Enchanted Cosmic Rod +20", "Universe-bending magic", 25000, 0, 380, 30, 130, EquipmentClass::MAGE},
        {"Big Bang Staff", "Creates new universes", 35000, 0, 500, 50, 180, EquipmentClass::MAGE},
        {"Omega Spell Caster", "Casts all spells instantly", 50000, 0, 700, 100, 300, EquipmentClass::MAGE},

        // ROGUE WEAPONS (sorted by cost)
        {"Rusty Dagger", "Better than nothing", 60, 10, 0, 0, 8, EquipmentClass::ROGUE},
        {"Iron Dagger", "A swift assassin's blade", 80, 4, 0, 0, 4, EquipmentClass::ROGUE},
        {"Steel Daggers", "Dual wielding blades", 180, 22, 0, 0, 15, EquipmentClass::ROGUE},
        {"Shadow Blade", "Strikes from the darkness", 350, 10, 0, 0, 12, EquipmentClass::ROGUE},
        {"Shadow Blades", "Invisible in darkness", 500, 42, 0, 0, 28, EquipmentClass::ROGUE},
        {"Venom Fangs", "Coated in deadly poison", 850, 48, 0, 5, 32, EquipmentClass::ROGUE},
        {"Whisper Knives", "Silent kill guaranteed", 1200, 55, 0, 8, 38, EquipmentClass::ROGUE},
        {"Nightfall", "Legendary rogue weapon", 1400, 25, 0, 0, 25, EquipmentClass::ROGUE},
        {"Venomfang Dagger", "Poisons with each strike", 1500, 20, 0, 0, 25, EquipmentClass::ROGUE},
        {"Backstabber's Edge", "Critical from behind", 1600, 62, 0, 10, 42, EquipmentClass::ROGUE},
        {"Night Whisper", "Silent, deadly, unseen", 1800, 24, 0, 0, 28, EquipmentClass::ROGUE},
        {"Nightbane Daggers", "Legendary assassin weapons", 1900, 70, 0, 0, 45, EquipmentClass::ROGUE},
        {"Dagger of Shadows", "Absorbs light and HP", 2000, 28, 0, 0, 30, EquipmentClass::ROGUE},
        {"Deathmark Daggers", "Marks targets for death", 2000, 72, 0, 12, 48, EquipmentClass::ROGUE},
        {"Twinfangs", "Dual daggers of havoc", 2200, 32, 0, 0, 35, EquipmentClass::ROGUE},
        {"Eclipse Blades", "Darkest of weapons", 2400, 78, 0, 15, 52, EquipmentClass::ROGUE},
        {"Soulthief Blades", "Steals enemy essence", 2800, 82, 0, 15, 52, EquipmentClass::ROGUE},
        {"Assassin's Edge", "One strike, instant death", 3000, 40, 0, 0, 38, EquipmentClass::ROGUE},
        {"Shadowstrike Knives", "Never miss in shadows", 3000, 88, 0, 20, 58, EquipmentClass::ROGUE},
        {"Viperfang", "Fastest dagger in existence", 3200, 45, 0, 0, 42, EquipmentClass::ROGUE},
        {"Nightfall Daggers", "Brings eternal night", 3800, 98, 0, 25, 65, EquipmentClass::ROGUE},
        {"Specter Blades", "Pass through walls", 4000, 50, 0, 0, 45, EquipmentClass::ROGUE},
        {"Spectre Blades", "Phase through armor", 5500, 120, 0, 35, 78, EquipmentClass::ROGUE},
        {"Shadowfang Twinblades", "Double your damage", 5000, 60, 0, 0, 55, EquipmentClass::ROGUE},
        {"Phantom Claws", "Rip through reality", 7000, 75, 0, 0, 70, EquipmentClass::ROGUE},
        {"Oblivion Edge", "Erases enemies", 8500, 155, 0, 50, 92, EquipmentClass::ROGUE},
        {"Phantomblade Infinity", "INSANELY OP daggers", 11000, 165, 0, 35, 95, EquipmentClass::ROGUE},
        {"Death's Kiss", "Ultimate rogue weapon", 15000, 150, 0, 0, 100, EquipmentClass::ROGUE},
        {"Dimensional Knives", "Strike from other realms", 16000, 240, 0, 85, 125, EquipmentClass::ROGUE},
        {"Void Assassin Blades", "Ultimate rogue weapons", 28000, 380, 0, 150, 180, EquipmentClass::ROGUE},
        {"Poisoned Fang", "Deadly venom coating", 6000, 125, 0, 40, 85, EquipmentClass::ROGUE},
        {"Shadow Dancer Blades", "Move like wind", 6800, 135, 0, 45, 90, EquipmentClass::ROGUE},
        {"Backstab King", "Guaranteed critical from behind", 7500, 145, 0, 50, 95, EquipmentClass::ROGUE},
        {"Enchanted Shadow Knife +10", "Enhanced stealth power", 8200, 160, 5, 55, 102, EquipmentClass::ROGUE},
        {"Bleeding Edge Daggers", "Causes massive bleeding", 9000, 170, 0, 60, 108, EquipmentClass::ROGUE},
        {"Chaos Fangs", "Random devastating effects", 10000, 185, 0, 65, 115, EquipmentClass::ROGUE},
        {"Time Thief Blades", "Slows enemies on hit", 11500, 200, 0, 70, 122, EquipmentClass::ROGUE},
        {"Enchanted Phantom Edge +15", "Phases through armor", 13000, 220, 10, 80, 135, EquipmentClass::ROGUE},
        {"Soul Stealer Daggers", "Absorbs enemy essence", 15000, 245, 0, 90, 145, EquipmentClass::ROGUE},
        {"Invisible Death", "Cannot be seen or blocked", 17000, 270, 0, 100, 155, EquipmentClass::ROGUE},
        {"Enchanted Void Claw +20", "Dimensional assassination", 20000, 310, 15, 120, 170, EquipmentClass::ROGUE},
        {"Perfect Assassin", "100% critical rate", 24000, 350, 20, 140, 190, EquipmentClass::ROGUE},
        {"Nightmare Blades", "Enemies fear your presence", 30000, 420, 30, 170, 220, EquipmentClass::ROGUE},
        {"Omega Strike Daggers", "One-shot everything", 55000, 750, 80, 300, 400, EquipmentClass::ROGUE},

        // CLERIC WEAPONS (sorted by cost)
        {"Wooden Mace", "Basic holy weapon", 90, 12, 8, 5, 0, EquipmentClass::CLERIC},
        {"Holy Mace", "Blessed by the gods", 120, 3, 5, 5, 1, EquipmentClass::CLERIC},
        {"Blessed Hammer", "Smites the unholy", 220, 24, 18, 12, 2, EquipmentClass::CLERIC},
        {"Divine Hammer", "Smites evil", 450, 8, 12, 12, 2, EquipmentClass::CLERIC},
        {"Divine Flail", "Channels holy power", 620, 45, 35, 25, 5, EquipmentClass::CLERIC},
        {"Radiant Morningstar", "Blazes with divine light", 950, 52, 42, 30, 8, EquipmentClass::CLERIC},
        {"Sanctified Mace", "Heals allies on hit", 1400, 58, 48, 35, 10, EquipmentClass::CLERIC},
        {"Heaven's Judgement", "Ultimate holy weapon", 1600, 20, 30, 45, 5, EquipmentClass::CLERIC},
        {"Paladin's Warhammer", "Crushes evil", 1800, 65, 55, 42, 12, EquipmentClass::CLERIC},
        {"Sanctified Mace", "Blessed with holy wrath", 1800, 12, 32, 35, 4, EquipmentClass::CLERIC},
        {"Hammer of Light", "Shines on evil", 2100, 18, 38, 42, 5, EquipmentClass::CLERIC},
        {"Lightbringer", "Legendary holy weapon", 2100, 75, 60, 45, 12, EquipmentClass::CLERIC},
        {"Holy Avenger", "Protects the innocent", 2200, 72, 62, 48, 15, EquipmentClass::CLERIC},
        {"Radiant Scepter", "Emits blinding light", 2200, 15, 42, 35, 6, EquipmentClass::CLERIC},
        {"Divine Lance", "Pierces darkness", 2500, 22, 45, 45, 7, EquipmentClass::CLERIC},
        {"Seraphic Flail", "Blessed by angels", 2800, 82, 70, 55, 18, EquipmentClass::CLERIC},
        {"Blessed Morningstar", "Crushes evil hearts", 2800, 28, 55, 55, 9, EquipmentClass::CLERIC},
        {"Celestial Warhammer", "Power of heavens", 3000, 25, 50, 60, 8, EquipmentClass::CLERIC},
        {"Judgment Hammer", "God's wrath incarnate", 3200, 92, 75, 60, 18, EquipmentClass::CLERIC},
        {"Divine Retribution", "Punishes the wicked", 3500, 95, 80, 65, 22, EquipmentClass::CLERIC},
        {"Purity Hammer", "Exorcises demons", 3500, 40, 70, 70, 12, EquipmentClass::CLERIC},
        {"Holy Avenger", "Massive holy damage", 4000, 35, 60, 60, 10, EquipmentClass::CLERIC},
        {"Celestial Hammer", "Forged in heaven", 4500, 110, 95, 75, 28, EquipmentClass::CLERIC},
        {"Godforge Mace", "Created by deity", 6500, 135, 115, 90, 35, EquipmentClass::CLERIC},
        {"Divine Retribution", "Massive smite power", 8000, 75, 120, 120, 20, EquipmentClass::CLERIC},
        {"Eternal Light", "Never-ending radiance", 10000, 170, 145, 115, 48, EquipmentClass::CLERIC},
        {"Heaven's Wrath", "EXTREME OP holy weapon", 14000, 190, 160, 110, 45, EquipmentClass::CLERIC},
        {"Archangel's Judgment", "Ultimate divine power", 20000, 270, 230, 180, 80, EquipmentClass::CLERIC},
        {"Heavenfall", "OP holy relic", 20000, 150, 250, 300, 50, EquipmentClass::CLERIC},
        {"Omnipotent Smiter", "God's own weapon", 35000, 420, 380, 300, 150, EquipmentClass::CLERIC},
        {"Blessed Warhammer +10", "Enhanced holy power", 9000, 180, 150, 125, 50, EquipmentClass::CLERIC},
        {"Angel's Fury", "Summons angelic wrath", 11000, 200, 165, 140, 58, EquipmentClass::CLERIC},
        {"Exorcist's Flail", "Banishes demons instantly", 12500, 215, 180, 150, 65, EquipmentClass::CLERIC},
        {"Divine Smite Hammer", "Massive holy damage", 15000, 240, 200, 170, 72, EquipmentClass::CLERIC},
        {"Enchanted Lightbringer +15", "Ultimate radiance", 17000, 265, 220, 185, 80, EquipmentClass::CLERIC},
        {"Holy Judgment Mace", "Judges the unworthy", 19000, 290, 240, 200, 88, EquipmentClass::CLERIC},
        {"Resurrection Rod", "Brings allies back to life", 22000, 320, 270, 220, 95, EquipmentClass::CLERIC},
        {"Enchanted Heaven's Touch +20", "Healing and smiting", 25000, 360, 300, 250, 105, EquipmentClass::CLERIC},
        {"Seraphim's Wrath", "Power of highest angels", 28000, 400, 340, 280, 120, EquipmentClass::CLERIC},
        {"Divine Intervention", "God protects the wielder", 32000, 450, 380, 310, 135, EquipmentClass::CLERIC},
        {"Enchanted Godforce +25", "Divine power unleashed", 40000, 550, 480, 380, 180, EquipmentClass::CLERIC},
        {"Apocalypse Judgment", "Brings end times", 48000, 650, 600, 450, 220, EquipmentClass::CLERIC},
        {"Ultimate Salvation", "Saves or destroys all", 60000, 850, 800, 600, 300, EquipmentClass::CLERIC},

        // RANGER WEAPONS (sorted by cost)
        {"Hunting Bow", "Basic ranger weapon", 85, 15, 0, 0, 6, EquipmentClass::RANGER},
        {"Hunting Bow", "A reliable ranger's bow", 90, 5, 0, 0, 3, EquipmentClass::RANGER},
        {"Longbow", "Increased range", 190, 28, 0, 0, 12, EquipmentClass::RANGER},
        {"Elven Longbow", "Crafted by elven masters", 400, 12, 2, 0, 8, EquipmentClass::RANGER},
        {"Elven Bow", "Ancient craftsmanship", 550, 52, 5, 0, 22, EquipmentClass::RANGER},
        {"Thornwood Longbow", "Nature's vengeance", 880, 58, 8, 0, 28, EquipmentClass::RANGER},
        {"Eagle Eye Bow", "Never misses", 1300, 65, 10, 0, 32, EquipmentClass::RANGER},
        {"Stormbow", "Legendary ranger weapon", 1500, 28, 5, 0, 18, EquipmentClass::RANGER},
        {"Stormshot Longbow", "Lightning-infused arrows", 1700, 72, 12, 0, 36, EquipmentClass::RANGER},
        {"Windpiercer Bow", "Arrows fly like wind", 1800, 30, 5, 0, 15, EquipmentClass::RANGER},
        {"Windcaller Bow", "Arrows ride the wind", 1850, 80, 12, 0, 38, EquipmentClass::RANGER},
        {"Moonshadow Longbow", "Silent as the night", 2000, 35, 7, 0, 18, EquipmentClass::RANGER},
        {"Wildfire Bow", "Ignites targets", 2100, 82, 15, 0, 42, EquipmentClass::RANGER},
        {"Falcon Eye", "Never misses a target", 2200, 38, 8, 0, 20, EquipmentClass::RANGER},
        {"Frostwind Longbow", "Freezing arrows", 2500, 88, 18, 0, 46, EquipmentClass::RANGER},
        {"Stormstrike Bow", "Lightning-infused arrows", 2500, 42, 10, 0, 22, EquipmentClass::RANGER},
        {"Skypierce Bow", "Shoots through clouds", 2700, 95, 18, 0, 48, EquipmentClass::RANGER},
        {"Nature's Wrath", "Bow infused with forest power", 2800, 45, 12, 0, 25, EquipmentClass::RANGER},
        {"Shadowvine Bow", "Silent yet deadly", 3000, 48, 10, 0, 26, EquipmentClass::RANGER},
        {"Nature's Fury", "Commands forest power", 3200, 98, 22, 0, 52, EquipmentClass::RANGER},
        {"Thunderhawk Bow", "Calls down storms", 3200, 50, 15, 0, 28, EquipmentClass::RANGER},
        {"Dragonstring Bow", "Stronger than steel", 4000, 60, 18, 0, 35, EquipmentClass::RANGER},
        {"Moonlight Bow", "Glows in darkness", 4000, 110, 28, 0, 58, EquipmentClass::RANGER},
        {"Eagleheart Longbow", "Legendary ranger weapon", 5000, 72, 20, 0, 40, EquipmentClass::RANGER},
        {"Dragon Bone Longbow", "Unbreakable", 5800, 130, 35, 0, 68, EquipmentClass::RANGER},
        {"Infinity Shot Bow", "Unlimited ammo", 9000, 165, 50, 0, 85, EquipmentClass::RANGER},
        {"Worldender Crossbow", "ULTRA OP ranger weapon", 12500, 195, 40, 0, 88, EquipmentClass::RANGER},
        {"Worldbreaker Bow", "Insanely overpowered", 15000, 150, 50, 0, 80, EquipmentClass::RANGER},
        {"Cosmic Quiver", "Shoots stars", 17000, 250, 80, 0, 120, EquipmentClass::RANGER},
        {"Worldtree Greatbow", "Ultimate ranger weapon", 30000, 400, 140, 0, 200, EquipmentClass::RANGER},
        {"Multi-Shot Bow", "Fires 5 arrows at once", 6500, 135, 25, 0, 72, EquipmentClass::RANGER},
        {"Venom Arrow Launcher", "Poison on every hit", 7200, 145, 30, 0, 78, EquipmentClass::RANGER},
        {"Phoenix Feather Bow", "Fire damage arrows", 8000, 158, 35, 0, 85, EquipmentClass::RANGER},
        {"Enchanted Hunter's Mark +10", "Never miss a target", 9200, 172, 42, 5, 92, EquipmentClass::RANGER},
        {"Gale Force Bow", "Arrows pierce multiple enemies", 10500, 188, 48, 0, 100, EquipmentClass::RANGER},
        {"Sniper's Dream", "Infinite range", 12000, 205, 55, 0, 108, EquipmentClass::RANGER},
        {"Enchanted Wildshot +15", "Nature's ultimate power", 14000, 230, 65, 10, 120, EquipmentClass::RANGER},
        {"Dragonheart Bow", "Dragon-powered arrows", 16000, 255, 75, 0, 132, EquipmentClass::RANGER},
        {"Rapid Fire Crossbow", "Attack speed x5", 18500, 280, 85, 0, 145, EquipmentClass::RANGER},
        {"Enchanted Skybreaker +20", "Shoots through anything", 21000, 315, 100, 15, 160, EquipmentClass::RANGER},
        {"Elemental Arrow Bow", "All elements on arrows", 24000, 350, 115, 0, 175, EquipmentClass::RANGER},
        {"Perfect Aim", "100% critical rate", 27000, 390, 130, 20, 190, EquipmentClass::RANGER},
        {"Enchanted Cosmos Bow +25", "Shoots stars from space", 33000, 480, 180, 30, 230, EquipmentClass::RANGER},
        {"Omega Sniper", "One-shot kill from anywhere", 52000, 700, 280, 50, 350, EquipmentClass::RANGER},

        // UNIVERSAL WEAPONS (sorted by cost)
        {"Iron Sword", "Decent for anyone", 140, 20, 8, 5, 5, EquipmentClass::ALL},
        {"Balanced Sword", "Good for any class", 200, 8, 3, 2, 2, EquipmentClass::ALL},
        {"Mystic Blade", "Magic-enhanced weapon", 480, 38, 22, 12, 12, EquipmentClass::ALL},
        {"Enchanted Blade", "Magic enhanced weapon", 600, 15, 8, 5, 5, EquipmentClass::ALL},
        {"Dragonbone Sword", "Powerful hybrid weapon", 750, 55, 35, 18, 18, EquipmentClass::ALL},
        {"Omniweapon", "Adapts to any class", 1200, 65, 45, 25, 22, EquipmentClass::ALL},
        {"Versatile Blade", "Good for all situations", 1800, 72, 52, 30, 26, EquipmentClass::ALL},
        {"Omniblade", "Good for anyone", 2000, 25, 15, 10, 10, EquipmentClass::ALL},
        {"Starblade", "Cosmic power weapon", 2400, 80, 55, 30, 28, EquipmentClass::ALL},
        {"Eternal Edge", "Never breaks", 2800, 85, 65, 38, 32, EquipmentClass::ALL},
        {"Harmony Weapon", "Balanced perfection", 3500, 95, 75, 45, 38, EquipmentClass::ALL},
        {"Eclipse Edge", "Shadow + light", 3500, 40, 25, 15, 15, EquipmentClass::ALL},
        {"Starshard Sword", "Cosmic energy infused", 4500, 55, 30, 20, 20, EquipmentClass::ALL},
        {"Aetherfang", "Pure energy weapon", 5000, 60, 35, 25, 25, EquipmentClass::ALL},
        {"Dragonfang", "Dragon-blooded weapon", 6000, 70, 40, 25, 25, EquipmentClass::ALL},
        {"Titan Edge", "Crushes the unworthy", 7000, 80, 45, 30, 30, EquipmentClass::ALL},
        {"Infinity Blade", "Limitless power", 8000, 90, 50, 30, 30, EquipmentClass::ALL},
        {"Celestial Sword", "Blessed by gods", 9000, 100, 60, 35, 35, EquipmentClass::ALL},
        {"Void Reaper", "Destroys everything", 10000, 120, 60, 40, 40, EquipmentClass::ALL},
        {"Infinity Blade", "Universal destruction", 11000, 145, 120, 75, 60, EquipmentClass::ALL},
        {"Prismatic Edge", "All elements combined", 16000, 160, 110, 65, 55, EquipmentClass::ALL},
        {"Armageddon Blade", "Ridiculously OP universal weapon", 20000, 200, 150, 60, 60, EquipmentClass::ALL},
        {"Absolute Zero", "Ultimate hybrid weapon", 22000, 250, 200, 125, 100, EquipmentClass::ALL},
        {"Reality Ender", "ABSURDLY OP universal", 40000, 500, 400, 300, 200, EquipmentClass::ALL},
        {"Chaos Blade", "Random powerful effects", 12000, 160, 130, 80, 70, EquipmentClass::ALL},
        {"Enchanted Omni-Weapon +10", "Adapts to any situation", 15000, 185, 155, 95, 82, EquipmentClass::ALL},
        {"Soul Reaver Universal", "Steals all enemy stats", 18000, 215, 180, 110, 95, EquipmentClass::ALL},
        {"Elemental Master Blade", "Controls all elements", 21000, 245, 205, 125, 108, EquipmentClass::ALL},
        {"Enchanted Versatile Edge +15", "Perfect for everything", 25000, 280, 240, 145, 125, EquipmentClass::ALL},
        {"Time Warrior", "Slows time around you", 28000, 320, 270, 165, 140, EquipmentClass::ALL},
        {"Dimensional Weapon", "Exists in all dimensions", 32000, 365, 310, 190, 160, EquipmentClass::ALL},
        {"Enchanted Harmony Blade +20", "Perfect balance of power", 38000, 420, 360, 220, 185, EquipmentClass::ALL},
        {"Cosmic Entity", "Wields universe's power", 45000, 480, 420, 260, 215, EquipmentClass::ALL},
        {"Enchanted God Weapon +25", "Divine universal power", 55000, 580, 510, 320, 260, EquipmentClass::ALL},
        {"Existence Eraser", "Deletes anything", 65000, 680, 600, 380, 310, EquipmentClass::ALL},
        {"Enchanted Infinity Edge +30", "Limitless potential", 80000, 850, 750, 480, 400, EquipmentClass::ALL},
        {"Omega Weapon", "The ultimate weapon", 100000, 1000, 900, 600, 500, EquipmentClass::ALL},
        {"Beyond God Tier", "Transcends everything", 150000, 1500, 1300, 900, 750, EquipmentClass::ALL}
    };
    
    bool shopping = true;
    while (shopping) {
        ConsoleUI::clearScreen();
        ConsoleUI::printHeader("=== WEAPON SHOP ===");
        ConsoleUI::setColor(ConsoleUI::Color::YELLOW, ConsoleUI::Color::BLACK);
        cout << "Your Gold: " << player.getGold() << " | Your Class: " << player.getClassName();
        ConsoleUI::setColor(ConsoleUI::Color::WHITE, ConsoleUI::Color::BLACK);
        cout << endl;
        ConsoleUI::printSeparator();
        
        // Filter weapons to only show those available to the player's class
        vector<int> availableIndices;
        for (size_t i = 0; i < weapons.size(); i++) {
            auto& w = weapons[i];
            
            // Check if player can use this weapon
            EquipmentClass reqClass = w.reqClass;
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
        
        // Display only available weapons
        for (size_t idx = 0; idx < availableIndices.size(); idx++) {
            auto& w = weapons[availableIndices[idx]];
            
            ConsoleUI::setColor(ConsoleUI::Color::GREEN, ConsoleUI::Color::BLACK);
            cout << (idx + 1) << ". " << w.name << " - " << w.price << " gold";
            ConsoleUI::setColor(ConsoleUI::Color::WHITE, ConsoleUI::Color::BLACK);
            cout << "\n   " << w.description;
            cout << " [";
            if (w.strBonus != 0) cout << (w.strBonus > 0 ? "+" : "") << w.strBonus << " STR ";
            if (w.magBonus != 0) cout << (w.magBonus > 0 ? "+" : "") << w.magBonus << " MAG ";
            if (w.defBonus != 0) cout << (w.defBonus > 0 ? "+" : "") << w.defBonus << " DEF ";
            if (w.spdBonus != 0) cout << (w.spdBonus > 0 ? "+" : "") << w.spdBonus << " SPD ";
            cout << "]\n";
            
            string classReq = "All Classes";
            if (w.reqClass == EquipmentClass::WARRIOR) classReq = "Warrior Only";
            else if (w.reqClass == EquipmentClass::MAGE) classReq = "Mage Only";
            else if (w.reqClass == EquipmentClass::ROGUE) classReq = "Rogue Only";
            else if (w.reqClass == EquipmentClass::CLERIC) classReq = "Cleric Only";
            else if (w.reqClass == EquipmentClass::RANGER) classReq = "Ranger Only";
            
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
            auto& w = weapons[availableIndices[choice - 1]];
            
            if (player.getGold() >= w.price) {
                player.addGold(-w.price);
                Item newItem(w.name, w.description, ItemType::WEAPON, w.price / 2, w.strBonus, w.magBonus, w.defBonus, w.spdBonus, w.reqClass);
                player.getInventory().addItem(newItem);
                ConsoleUI::printSuccess("Purchased " + w.name + "!");
                cout << "\nPress Enter to continue...";
                cin.ignore();
                cin.get();
            } else {
                ConsoleUI::printError("Not enough gold! You need " + to_string(w.price) + " gold.");
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
