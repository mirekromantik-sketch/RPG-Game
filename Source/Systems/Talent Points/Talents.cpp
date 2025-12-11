#include "Talents.h"
#include <iostream>

using namespace std;

TalentTree::TalentTree() : className("Unknown"), availablePoints(0) {}

TalentTree::TalentTree(string className) : className(className), availablePoints(0) {
    // Initialize tree based on class
    if (className == "Warrior") initializeWarriorTree();
    else if (className == "Mage") initializeMageTree();
    else if (className == "Rogue") initializeRogueTree();
    else if (className == "Cleric") initializeClericTree();
    else if (className == "Ranger") initializeRangerTree();
}

void TalentTree::initializeWarriorTree() {
    // Tier 1
    talents["Iron Will"] = TalentNode("Iron Will", "Increases max HP by 20 per rank", 3, 1);
    talents["Power Strike"] = TalentNode("Power Strike", "Increases strength by 2 per rank", 5, 1);
    talents["Tough Skin"] = TalentNode("Tough Skin", "Increases defense by 2 per rank", 3, 1);
    talents["Battle Instinct"] = TalentNode("Battle Instinct", "Gain 5% dodge chance", 3, 1);
    talents["Weapon Training"] = TalentNode("Weapon Training", "Increase attack speed by 3%", 3, 1);

    // Tier 2
    TalentNode berserk("Berserker Rage", "Deal 50% more damage below 30% HP", 1, 2); berserk.prerequisites.push_back("Power Strike"); talents["Berserker Rage"] = berserk;
    TalentNode shield("Shield Master", "Reduce damage taken by 15%", 1, 2); shield.prerequisites.push_back("Tough Skin"); talents["Shield Master"] = shield;
    TalentNode endurance("Endurance", "Increases HP regeneration", 3, 2); endurance.prerequisites.push_back("Iron Will"); talents["Endurance"] = endurance;
    TalentNode warcry("Warcry", "Increase allies' attack by 10% for 10s", 1, 2); warcry.prerequisites.push_back("Battle Instinct"); talents["Warcry"] = warcry;
    TalentNode heavyblow("Heavy Blow", "Increases damage by 15% for 5s after blocking", 1, 2); heavyblow.prerequisites.push_back("Shield Master"); talents["Heavy Blow"] = heavyblow;

    // Tier 3
    TalentNode juggernaut("Juggernaut", "Immune to crowd control for 5s", 1, 3); juggernaut.prerequisites.push_back("Berserker Rage"); talents["Juggernaut"] = juggernaut;
    TalentNode whirlwind("Whirlwind", "Spin attack hitting all nearby enemies", 1, 3); whirlwind.prerequisites.push_back("Power Strike"); talents["Whirlwind"] = whirlwind;
    TalentNode fortitude("Fortitude", "Increase max HP by 50 and defense by 10", 1, 3); fortitude.prerequisites.push_back("Shield Master"); talents["Fortitude"] = fortitude;
    TalentNode berserkmastery("Berserk Mastery", "Berserker Rage bonus damage increased to 100%", 1, 3); berserkmastery.prerequisites.push_back("Juggernaut"); talents["Berserk Mastery"] = berserkmastery;

    // Tier 4
    TalentNode earthshatter("Earthshatter", "Stun all enemies in front for 3s", 1, 4); earthshatter.prerequisites.push_back("Whirlwind"); talents["Earthshatter"] = earthshatter;
    TalentNode bloodfury("Bloodfury", "Deal 100% bonus damage below 20% HP", 1, 4); bloodfury.prerequisites.push_back("Juggernaut"); talents["Bloodfury"] = bloodfury;

    // Tier 5
    TalentNode unstoppable("Unstoppable Force", "Cannot be killed below 1 HP once per combat", 1, 5); unstoppable.prerequisites.push_back("Fortitude"); talents["Unstoppable Force"] = unstoppable;
}

void TalentTree::initializeMageTree() {
    // Tier 1
    talents["Arcane Knowledge"] = TalentNode("Arcane Knowledge", "Increases magic by 3 per rank", 5, 1);
    talents["Mana Shield"] = TalentNode("Mana Shield", "Increases defense by 1 per rank", 3, 1);
    talents["Spell Focus"] = TalentNode("Spell Focus", "Increases magic critical chance", 3, 1);
    talents["Elemental Affinity"] = TalentNode("Elemental Affinity", "Increases fire, ice, and lightning damage by 2%", 3, 1);
    talents["Meditation"] = TalentNode("Meditation", "Regenerate 1% max mana per second", 3, 1);

    // Tier 2
    TalentNode fireball("Fireball Master", "Unlocks powerful fireball attack", 1, 2); fireball.prerequisites.push_back("Arcane Knowledge"); talents["Fireball Master"] = fireball;
    TalentNode ice("Ice Armor", "Reduces damage and slows attackers", 1, 2); ice.prerequisites.push_back("Mana Shield"); talents["Ice Armor"] = ice;
    TalentNode arcane("Arcane Missiles", "Increases magic damage by 20%", 2, 2); arcane.prerequisites.push_back("Spell Focus"); talents["Arcane Missiles"] = arcane;
    TalentNode teleport("Blink", "Instantly teleport short distance", 2, 2); teleport.prerequisites.push_back("Meditation"); talents["Blink"] = teleport;
    TalentNode lightning("Lightning Bolt", "High damage single target spell", 1, 2); lightning.prerequisites.push_back("Elemental Affinity"); talents["Lightning Bolt"] = lightning;

    // Tier 3
    TalentNode pyroblast("Pyroblast", "Massive fire damage with burn over time", 1, 3); pyroblast.prerequisites.push_back("Fireball Master"); talents["Pyroblast"] = pyroblast;
    TalentNode frostnova("Frost Nova", "Freeze all enemies nearby for 3s", 1, 3); frostnova.prerequisites.push_back("Ice Armor"); talents["Frost Nova"] = frostnova;
    TalentNode arcanestorm("Arcane Storm", "Magic damage to all enemies in area", 1, 3); arcanestorm.prerequisites.push_back("Arcane Missiles"); talents["Arcane Storm"] = arcanestorm;
    TalentNode chainlightning("Chain Lightning", "Lightning jumps to 5 targets for 50% damage", 1, 3); chainlightning.prerequisites.push_back("Lightning Bolt"); talents["Chain Lightning"] = chainlightning;

    // Tier 4
    TalentNode meteor("Meteor Shower", "Rain meteors on enemies for massive AoE", 1, 4); meteor.prerequisites.push_back("Pyroblast"); talents["Meteor Shower"] = meteor;
    TalentNode timewarp("Time Warp", "Slow enemies by 50% and hasten allies for 5s", 1, 4); timewarp.prerequisites.push_back("Blink"); talents["Time Warp"] = timewarp;

    // Tier 5
    TalentNode godspell("Godspell", "Cast a spell that deals 500% damage in a massive area", 1, 5); godspell.prerequisites.push_back("Meteor Shower"); talents["Godspell"] = godspell;
}

void TalentTree::initializeRogueTree() {
    // Tier 1
    talents["Agility"] = TalentNode("Agility", "Increases speed by 2 per rank", 5, 1);
    talents["Precision"] = TalentNode("Precision", "Increases critical strike chance", 3, 1);
    talents["Stealth"] = TalentNode("Stealth", "Increases evasion", 3, 1);
    talents["Dual Wield"] = TalentNode("Dual Wield", "Allows dual wielding for 10% extra damage", 3, 1);
    talents["Acrobatics"] = TalentNode("Acrobatics", "Reduce fall damage and increase dodge", 3, 1);

    // Tier 2
    TalentNode backstab("Backstab", "Deal double damage from stealth", 1, 2); backstab.prerequisites.push_back("Stealth"); talents["Backstab"] = backstab;
    TalentNode poison("Poison Blade", "Attacks apply damage over time", 1, 2); poison.prerequisites.push_back("Precision"); talents["Poison Blade"] = poison;
    TalentNode shadow("Shadow Dance", "Greatly increases evasion", 2, 2); shadow.prerequisites.push_back("Agility"); talents["Shadow Dance"] = shadow;
    TalentNode garrote("Garrote", "Silences target from stealth", 1, 2); garrote.prerequisites.push_back("Stealth"); talents["Garrote"] = garrote;

    // Tier 3
    TalentNode vanish("Vanish", "Enter stealth instantly, even in combat", 1, 3); vanish.prerequisites.push_back("Shadow Dance"); talents["Vanish"] = vanish;
    TalentNode ambush("Ambush", "Deal 300% damage from stealth", 1, 3); ambush.prerequisites.push_back("Backstab"); talents["Ambush"] = ambush;
    TalentNode deadlypoison("Deadly Poison", "Increase Poison Blade damage by 50%", 1, 3); deadlypoison.prerequisites.push_back("Poison Blade"); talents["Deadly Poison"] = deadlypoison;

    // Tier 4
    TalentNode shadowstrike("Shadow Strike", "Strike from shadows, ignores defense", 1, 4); shadowstrike.prerequisites.push_back("Ambush"); talents["Shadow Strike"] = shadowstrike;
    TalentNode evasionmastery("Evasion Mastery", "You cannot be hit for 3s when dodging", 1, 4); evasionmastery.prerequisites.push_back("Shadow Dance"); talents["Evasion Mastery"] = evasionmastery;

    // Tier 5
    TalentNode deathfromabove("Death from Above", "Instantly kill target below 20% HP from stealth", 1, 5); deathfromabove.prerequisites.push_back("Shadow Strike"); talents["Death from Above"] = deathfromabove;
}

void TalentTree::initializeClericTree() {
    // Tier 1
    talents["Divine Power"] = TalentNode("Divine Power", "Increases magic by 2 per rank", 5, 1);
    talents["Holy Protection"] = TalentNode("Holy Protection", "Increases defense by 2 per rank", 3, 1);
    talents["Healing Touch"] = TalentNode("Healing Touch", "Increases healing by 10 per rank", 3, 1);
    talents["Blessed Aura"] = TalentNode("Blessed Aura", "Passive HP regen for nearby allies", 3, 1);
    talents["Faith"] = TalentNode("Faith", "Increase all healing by 5%", 3, 1);

    // Tier 2
    TalentNode resurrect("Resurrection", "Revive with 50% HP when defeated", 1, 2); resurrect.prerequisites.push_back("Holy Protection"); talents["Resurrection"] = resurrect;
    TalentNode smite("Holy Smite", "Deal bonus damage to evil enemies", 2, 2); smite.prerequisites.push_back("Divine Power"); talents["Holy Smite"] = smite;
    TalentNode prayer("Prayer of Mending", "Passive HP regeneration", 3, 2); prayer.prerequisites.push_back("Healing Touch"); talents["Prayer of Mending"] = prayer;
    TalentNode shieldoflight("Shield of Light", "Absorb 50% of damage for 10s", 1, 2); shieldoflight.prerequisites.push_back("Holy Protection"); talents["Shield of Light"] = shieldoflight;

    // Tier 3
    TalentNode divinefury("Divine Fury", "Smite deals 200% damage", 1, 3); divinefury.prerequisites.push_back("Holy Smite"); talents["Divine Fury"] = divinefury;
    TalentNode massheal("Mass Heal", "Heals all allies for 30% HP", 1, 3); massheal.prerequisites.push_back("Prayer of Mending"); talents["Mass Heal"] = massheal;

    // Tier 4
    TalentNode holyavenger("Holy Avenger", "Smite can crit for 500% damage", 1, 4); holyavenger.prerequisites.push_back("Divine Fury"); talents["Holy Avenger"] = holyavenger;
    TalentNode divineprotection("Divine Protection", "Immunity to all debuffs for 5s", 1, 4); divineprotection.prerequisites.push_back("Shield of Light"); talents["Divine Protection"] = divineprotection;

    // Tier 5
    TalentNode godlymiracle("Godly Miracle", "Fully restore HP and mana of all allies", 1, 5); godlymiracle.prerequisites.push_back("Mass Heal"); talents["Godly Miracle"] = godlymiracle;
}

void TalentTree::initializeRangerTree() {
    // Tier 1
    talents["Marksmanship"] = TalentNode("Marksmanship", "Increases strength by 2 per rank", 5, 1);
    talents["Animal Companion"] = TalentNode("Animal Companion", "Increases max HP by 15 per rank", 3, 1);
    talents["Wilderness Survival"] = TalentNode("Wilderness Survival", "Increases defense by 1 per rank", 3, 1);
    talents["Camouflage"] = TalentNode("Camouflage", "Increases stealth in forests by 10%", 3, 1);
    talents["Trapper"] = TalentNode("Trapper", "Increase trap damage by 5%", 3, 1);

    // Tier 2
    TalentNode multishot("Multi-Shot", "Attack hits multiple enemies", 1, 2); multishot.prerequisites.push_back("Marksmanship"); talents["Multi-Shot"] = multishot;
    TalentNode trap("Trap Master", "Set traps to damage enemies", 2, 2); trap.prerequisites.push_back("Wilderness Survival"); talents["Trap Master"] = trap;
    TalentNode beast("Beast Mastery", "Your companion is stronger", 3, 2); beast.prerequisites.push_back("Animal Companion"); talents["Beast Mastery"] = beast;
    TalentNode eagleeye("Eagle Eye", "Increase range and critical chance by 5%", 2, 2); eagleeye.prerequisites.push_back("Marksmanship"); talents["Eagle Eye"] = eagleeye;

    // Tier 3
    TalentNode volley("Volley", "Shoot arrows at all enemies in cone", 1, 3); volley.prerequisites.push_back("Multi-Shot"); talents["Volley"] = volley;
    TalentNode beastfrenzy("Beast Frenzy", "Companion deals 100% bonus damage for 10s", 1, 3); beastfrenzy.prerequisites.push_back("Beast Mastery"); talents["Beast Frenzy"] = beastfrenzy;
    TalentNode deathtrap("Death Trap", "Trap deals massive damage and stuns", 1, 3); deathtrap.prerequisites.push_back("Trap Master"); talents["Death Trap"] = deathtrap;

    // Tier 4
    TalentNode rapidfire("Rapid Fire", "Shoot 10 arrows in 2 seconds", 1, 4); rapidfire.prerequisites.push_back("Volley"); talents["Rapid Fire"] = rapidfire;
    TalentNode predator("Predator", "Your companion can instantly kill small enemies", 1, 4); predator.prerequisites.push_back("Beast Frenzy"); talents["Predator"] = predator;

    // Tier 5
    TalentNode arrowstorm("Arrow Storm", "Rains arrows on all enemies for massive AoE", 1, 5); arrowstorm.prerequisites.push_back("Rapid Fire"); talents["Arrow Storm"] = arrowstorm;
}

bool TalentTree::checkPrerequisites(const TalentNode& talent) const {
    for (const string& prereq : talent.prerequisites) {
        auto it = talents.find(prereq);
        if (it == talents.end() || it->second.currentRank == 0) {
            return false;
        }
    }
    return true;
}

bool TalentTree::upgradeTalent(const string& talentName) {
    auto it = talents.find(talentName);
    if (it == talents.end()) {
        cout << "Talent not found!" << endl;
        return false;
    }
    
    TalentNode& talent = it->second;
    
    if (talent.isMaxed()) {
        cout << "This talent is already maxed out!" << endl;
        return false;
    }
    
    if (!checkPrerequisites(talent)) {
        cout << "You don't meet the prerequisites for this talent!" << endl;
        return false;
    }
    
    if (availablePoints < talent.cost) {
        cout << "Not enough talent points! Need " << talent.cost << ", have " << availablePoints << endl;
        return false;
    }
    
    talent.currentRank++;
    availablePoints -= talent.cost;
    cout << "Upgraded " << talent.name << " to rank " << talent.currentRank << "/" << talent.maxRank << "!" << endl;
    return true;
}

void TalentTree::addPoints(int points) {
    availablePoints += points;
}

void TalentTree::displayTalents() const {
    cout << "\n=== " << className << " Talent Tree ===" << endl;
    cout << "Available Points: " << availablePoints << endl;
    cout << "\n--- Talents ---" << endl;
    
    for (const auto& pair : talents) {
        const TalentNode& talent = pair.second;
        cout << "\n" << talent.name << " [" << talent.currentRank << "/" << talent.maxRank << "]" << endl;
        cout << "  " << talent.description << endl;
        cout << "  Cost: " << talent.cost << " points per rank" << endl;
        
        if (!talent.prerequisites.empty()) {
            cout << "  Requires: ";
            for (size_t i = 0; i < talent.prerequisites.size(); i++) {
                cout << talent.prerequisites[i];
                if (i < talent.prerequisites.size() - 1) cout << ", ";
            }
            cout << endl;
        }
    }
}

bool TalentTree::hasTalent(const string& talentName) const {
    auto it = talents.find(talentName);
    return it != talents.end() && it->second.currentRank > 0;
}

int TalentTree::getTalentRank(const string& talentName) const {
    auto it = talents.find(talentName);
    if (it != talents.end()) {
        return it->second.currentRank;
    }
    return 0;
}

void TalentTree::setTalentRank(const string& talentName, int rank) {
    auto it = talents.find(talentName);
    if (it != talents.end()) {
        it->second.currentRank = rank;
        if (it->second.currentRank > it->second.maxRank) {
            it->second.currentRank = it->second.maxRank;
        }
    }
}

void TalentTree::autoAllocate() {
    if (availablePoints == 0) {
        cout << "\nNo talent points available to allocate!" << endl;
        return;
    }
    
    int pointsSpent = 0;
    bool keepAllocating = true;
    
    // Keep trying to allocate points until we run out or can't upgrade anything
    while (availablePoints > 0 && keepAllocating) {
        keepAllocating = false;
        
        // Try to upgrade talents in order, prioritizing those without prerequisites
        for (auto& pair : talents) {
            if (availablePoints == 0) break;
            
            TalentNode& talent = pair.second;
            
            // Try to upgrade if possible
            if (!talent.isMaxed() && 
                checkPrerequisites(talent) && 
                availablePoints >= talent.cost) {
                
                talent.currentRank++;
                availablePoints -= talent.cost;
                pointsSpent++;
                keepAllocating = true;  // We made progress, keep trying
            }
        }
    }
    
    cout << "\n=== Auto-Allocated Talents ===" << endl;
    cout << "Points spent: " << pointsSpent << endl;
    cout << "Points remaining: " << availablePoints << endl;
    
    if (availablePoints > 0) {
        cout << "\nNote: Some points couldn't be allocated due to prerequisites." << endl;
    }
}
