# Talent System Documentation

## Overview
The talent system provides class-specific progression paths with multiple ranks, prerequisites, and combat effects.

## System Architecture

### Core Components

#### TalentNode
Represents a single talent in the tree.

**Properties:**
- `name` - Display name of the talent
- `description` - What the talent does
- `maxRank` - Maximum number of ranks (1-5 typically)
- `currentRank` - Player's current rank (0 = not learned)
- `cost` - Points required per rank
- `prerequisites` - List of required talents

#### TalentTree
Manages all talents for a specific class.

**Properties:**
- `className` - The class this tree belongs to
- `talents` - Map of talent name to TalentNode
- `availablePoints` - Unspent talent points

**Methods:**
- `upgradeTalent(name)` - Attempt to upgrade a talent
- `displayTalents()` - Show all talents with status
- `addPoints(count)` - Grant talent points
- `hasTalent(name)` - Check if player has talent
- `getTalentRank(name)` - Get talent rank

## Complete Talent Lists

### Warrior Talents

#### Tier 1 (No Prerequisites)
```
Iron Will
- Max Rank: 3
- Cost: 1 point per rank
- Effect: +20 max HP per rank
- Total: +60 HP at rank 3
```

```
Power Strike
- Max Rank: 5
- Cost: 1 point per rank
- Effect: +2 strength per rank
- Total: +10 strength at rank 5
```

```
Tough Skin
- Max Rank: 3
- Cost: 1 point per rank
- Effect: +2 defense per rank
- Total: +6 defense at rank 3
```

#### Tier 2 (Requires Prerequisites)
```
Berserker Rage
- Max Rank: 1
- Cost: 2 points
- Prerequisites: Power Strike
- Effect: Deal 50% more damage when HP below 30%
```

```
Shield Master
- Max Rank: 1
- Cost: 2 points
- Prerequisites: Tough Skin
- Effect: Reduce all damage taken by 15%
```

```
Endurance
- Max Rank: 3
- Cost: 1 point per rank
- Prerequisites: Iron Will
- Effect: Passive HP regeneration
```

**Warrior Build Paths:**
1. **Tank Build:** Iron Will → Endurance, Tough Skin → Shield Master
2. **DPS Build:** Power Strike → Berserker Rage
3. **Balanced:** Mix of defense and offense talents

---

### Mage Talents

#### Tier 1
```
Arcane Knowledge
- Max Rank: 5
- Cost: 1 point per rank
- Effect: +3 magic per rank
- Total: +15 magic at rank 5
```

```
Mana Shield
- Max Rank: 3
- Cost: 1 point per rank
- Effect: +1 defense per rank
- Total: +3 defense at rank 3
```

```
Spell Focus
- Max Rank: 3
- Cost: 1 point per rank
- Effect: Increases magic critical chance
- Total: +15% crit chance at rank 3
```

#### Tier 2
```
Fireball Master
- Max Rank: 1
- Cost: 2 points
- Prerequisites: Arcane Knowledge
- Effect: Unlocks powerful fireball attack
```

```
Ice Armor
- Max Rank: 1
- Cost: 2 points
- Prerequisites: Mana Shield
- Effect: Reduces damage taken and slows attackers
```

```
Arcane Missiles
- Max Rank: 2
- Cost: 2 points per rank
- Prerequisites: Spell Focus
- Effect: +20% magic damage per rank
- Total: +40% magic damage at rank 2
```

**Mage Build Paths:**
1. **Pure DPS:** Arcane Knowledge → Fireball Master, Spell Focus → Arcane Missiles
2. **Defensive:** Mana Shield → Ice Armor
3. **Balanced:** Mix of damage and survival

---

### Rogue Talents

#### Tier 1
```
Agility
- Max Rank: 5
- Cost: 1 point per rank
- Effect: +2 speed per rank
- Total: +10 speed at rank 5
```

```
Precision
- Max Rank: 3
- Cost: 1 point per rank
- Effect: +10% critical strike chance per rank
- Total: +30% crit chance at rank 3
```

```
Stealth
- Max Rank: 3
- Cost: 1 point per rank
- Effect: Increases evasion
- Total: +15% evasion at rank 3
```

#### Tier 2
```
Backstab
- Max Rank: 1
- Cost: 2 points
- Prerequisites: Stealth
- Effect: Deal double damage from stealth
```

```
Poison Blade
- Max Rank: 1
- Cost: 2 points
- Prerequisites: Precision
- Effect: Attacks apply damage over time
```

```
Shadow Dance
- Max Rank: 2
- Cost: 2 points per rank
- Prerequisites: Agility
- Effect: Greatly increases evasion
```

**Rogue Build Paths:**
1. **Crit Build:** Precision → Poison Blade
2. **Evasion Build:** Stealth → Backstab, Agility → Shadow Dance
3. **Speed Build:** Focus on Agility

---

### Cleric Talents

#### Tier 1
```
Divine Power
- Max Rank: 5
- Cost: 1 point per rank
- Effect: +2 magic per rank
- Total: +10 magic at rank 5
```

```
Holy Protection
- Max Rank: 3
- Cost: 1 point per rank
- Effect: +2 defense per rank
- Total: +6 defense at rank 3
```

```
Healing Touch
- Max Rank: 3
- Cost: 1 point per rank
- Effect: +10 healing per rank
- Total: +30 healing at rank 3
```

#### Tier 2
```
Resurrection
- Max Rank: 1
- Cost: 3 points
- Prerequisites: Holy Protection
- Effect: Revive with 50% HP when defeated (once per rest)
```

```
Holy Smite
- Max Rank: 2
- Cost: 2 points per rank
- Prerequisites: Divine Power
- Effect: Deal bonus damage to evil enemies
```

```
Prayer of Mending
- Max Rank: 3
- Cost: 1 point per rank
- Prerequisites: Healing Touch
- Effect: Passive HP regeneration
- Total: +3 HP per turn at rank 3
```

**Cleric Build Paths:**
1. **Support:** Healing Touch → Prayer of Mending
2. **Offensive:** Divine Power → Holy Smite
3. **Tank:** Holy Protection → Resurrection

---

### Ranger Talents

#### Tier 1
```
Marksmanship
- Max Rank: 5
- Cost: 1 point per rank
- Effect: +2 strength per rank
- Total: +10 strength at rank 5
```

```
Animal Companion
- Max Rank: 3
- Cost: 1 point per rank
- Effect: +15 max HP per rank
- Total: +45 HP at rank 3
```

```
Wilderness Survival
- Max Rank: 3
- Cost: 1 point per rank
- Effect: +1 defense per rank
- Total: +3 defense at rank 3
```

#### Tier 2
```
Multi-Shot
- Max Rank: 1
- Cost: 2 points
- Prerequisites: Marksmanship
- Effect: Attack hits multiple enemies
```

```
Trap Master
- Max Rank: 2
- Cost: 2 points per rank
- Prerequisites: Wilderness Survival
- Effect: Set traps to damage enemies
```

```
Beast Mastery
- Max Rank: 3
- Cost: 1 point per rank
- Prerequisites: Animal Companion
- Effect: Your companion is stronger
```

**Ranger Build Paths:**
1. **Damage:** Marksmanship → Multi-Shot
2. **Pet Build:** Animal Companion → Beast Mastery
3. **Utility:** Wilderness Survival → Trap Master

---

## Talent Point Earning

### Level-Up Rewards
- 1 talent point per level
- Granted automatically on level up
- No maximum cap

### Point Spending
- Can spend points anytime from main menu
- Must meet prerequisites
- Cannot exceed max rank
- Cannot refund points (permanent choices)

## Prerequisite System

### How It Works
1. Some talents require other talents
2. Must have at least 1 rank in prerequisite
3. Checked when attempting to upgrade
4. Displayed in talent description

### Example Chain
```
Power Strike (Tier 1)
    ↓
Berserker Rage (Tier 2)
```

Must have Power Strike before learning Berserker Rage.

## Combat Integration

### Damage Modifications

**Warrior:**
```cpp
// Power Strike: Direct damage increase
if (talentTree.hasTalent("Power Strike")) {
    baseDamage += getTalentRank("Power Strike") * 2;
}
```

**Mage:**
```cpp
// Arcane Knowledge: Magic damage scaling
if (talentTree.hasTalent("Arcane Knowledge")) {
    baseDamage += getTalentRank("Arcane Knowledge") * 3;
}
```

**Rogue:**
```cpp
// Precision: Critical strike chance
if (talentTree.hasTalent("Precision")) {
    int critChance = 20 + getTalentRank("Precision") * 10;
    if (rand() % 100 < critChance) {
        baseDamage *= 2;  // Critical hit!
    }
}
```

### Defense Modifications

**Warrior:**
```cpp
// Shield Master: Damage reduction
if (talentTree.hasTalent("Shield Master")) {
    actualDamage *= 0.85;  // 15% reduction
}
```

**Cleric:**
```cpp
// Holy Protection: Flat damage reduction
if (talentTree.hasTalent("Holy Protection")) {
    actualDamage -= getTalentRank("Holy Protection") * 2;
}
```

## UI/UX

### Displaying Talents
```
=== Warrior Talent Tree ===
Available Points: 3

--- Talents ---

Iron Will [1/3]
  Increases max HP by 20 per rank
  Cost: 1 points per rank

Power Strike [3/5]
  Increases strength by 2 per rank
  Cost: 1 points per rank

Berserker Rage [0/1]
  Deal 50% more damage below 30% HP
  Cost: 2 points per rank
  Requires: Power Strike
```

### Upgrading Talents
```
Enter talent name to upgrade (or 'exit' to leave): Power Strike
Upgraded Power Strike to rank 4/5!
```

### Error Messages
```
"Talent not found!"
"This talent is already maxed out!"
"You don't meet the prerequisites for this talent!"
"Not enough talent points! Need 2, have 1"
```

## Implementation Details

### Data Structure
```cpp
std::map<std::string, TalentNode> talents;
```
- O(log n) lookup time
- Sorted by name
- Easy iteration for display

### Memory Usage
- ~50 bytes per TalentNode
- ~400 bytes per TalentTree
- Minimal overhead

### Thread Safety
- Not thread-safe (single-threaded game)
- No concurrent access needed

## Balance Considerations

### Point Costs
- Tier 1: 1 point per rank
- Tier 2: 2-3 points per rank
- Ultimate talents: 3 points

### Max Ranks
- Basic talents: 3-5 ranks
- Advanced talents: 1-2 ranks
- Ultimate talents: 1 rank

### Total Points Available
- Level 1-10: 9 talent points
- Level 1-20: 19 talent points
- Allows ~2 complete talent paths by level 20

## Testing Recommendations

### Unit Tests
1. Prerequisite validation
2. Point spending/refunding
3. Max rank limits
4. Combat effect application

### Integration Tests
1. Level up grants points correctly
2. Talents persist through combat
3. Effects stack properly
4. UI displays correct information

### Balance Testing
1. Each class competitive at same level
2. No "must-have" talents
3. Multiple viable builds per class
4. Clear progression curve

## Common Issues and Solutions

### Issue: Talent not upgrading
**Causes:**
- Prerequisites not met
- Not enough points
- Already maxed
- Typo in talent name

**Solution:** Check prerequisites, verify spelling

### Issue: Combat effects not applying
**Causes:**
- Talent check missing in combat code
- Wrong talent name in check
- Logic error in effect calculation

**Solution:** Verify talent name matches exactly

### Issue: Points not granted on level up
**Causes:**
- Missing addPoints() call
- Wrong point amount

**Solution:** Check levelUp() function

## Future Enhancements

### Short Term
- [ ] Talent reset/respec functionality
- [ ] Talent tooltips with more detail
- [ ] Visual talent tree display

### Long Term
- [ ] Passive talents (always active)
- [ ] Active talents (usable abilities)
- [ ] Talent synergies between classes
- [ ] Legendary talents (unique, powerful)

---

This system provides a solid foundation for character progression and can be easily expanded with new talents, classes, and mechanics.
