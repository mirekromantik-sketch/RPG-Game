#include "SaveManager.h"
#include <iostream>
#include <sstream>
#include <windows.h>

using namespace std;

SaveManager::SaveManager(const string& filePath) : saveFilePath(filePath) {}

string SaveManager::getSaveFilePath(const string& saveName) const {
    if (saveName.empty()) {
        return saveFilePath;
    }
    
    // Check if it's a root directory save (legacy)
    if (saveName.length() > 5 && saveName.substr(0, 5) == "root:") {
        string cleanName = saveName.substr(5); // Remove "root:" prefix
        if (cleanName.length() > 5 && cleanName.substr(cleanName.length() - 5) == ".json") {
            return cleanName;
        }
        return cleanName + ".json";
    }
    
    // Remove .json if present and add it back
    string cleanName = saveName;
    if (cleanName.length() > 5 && cleanName.substr(cleanName.length() - 5) == ".json") {
        cleanName = cleanName.substr(0, cleanName.length() - 5);
    }
    return "saves/" + cleanName + ".json";
}

void SaveManager::setSaveFile(const string& saveName) {
    saveFilePath = getSaveFilePath(saveName);
}

vector<string> SaveManager::listSaveFiles() const {
    vector<string> saveFiles;
    
    // Check root directory for legacy saves
    WIN32_FIND_DATA findData;
    HANDLE hFind = FindFirstFile("*.json", &findData);
    
    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            string fileName = findData.cFileName;
            if (fileName != "." && fileName != ".." && fileName.length() > 5) {
                // Remove .json extension for display
                string displayName = fileName.substr(0, fileName.length() - 5);
                saveFiles.push_back("root:" + displayName);
            }
        } while (FindNextFile(hFind, &findData) != 0);
        FindClose(hFind);
    }
    
    // Check saves directory for new saves
    hFind = FindFirstFile("saves/*.json", &findData);
    
    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            string fileName = findData.cFileName;
            if (fileName != "." && fileName != ".." && fileName.length() > 5) {
                // Remove .json extension for display
                string displayName = fileName.substr(0, fileName.length() - 5);
                saveFiles.push_back(displayName);
            }
        } while (FindNextFile(hFind, &findData) != 0);
        FindClose(hFind);
    }
    
    return saveFiles;
}

string SaveManager::escapeString(const string& str) const {
    string result;
    for (char c : str) {
        if (c == '"') result += "\\\"";
        else if (c == '\\') result += "\\\\";
        else if (c == '\n') result += "\\n";
        else if (c == '\r') result += "\\r";
        else if (c == '\t') result += "\\t";
        else result += c;
    }
    return result;
}

string SaveManager::readFile(const string& path) const {
    ifstream file(path);
    if (!file.is_open()) return "";
    
    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void SaveManager::writeFile(const string& path, const string& content) const {
    // Create saves directory if it doesn't exist
    CreateDirectory("saves", NULL);
    
    ofstream file(path);
    if (file.is_open()) {
        file << content;
        file.close();
    }
}

bool SaveManager::saveGame(const Player& player, const string& saveName) {
    string filePath = saveName.empty() ? saveFilePath : getSaveFilePath(saveName);
    
    stringstream json;
    json << "{\n";
    json << "  \"version\": \"3.0\",\n";
    json << "  \"player\": {\n";
    json << "    \"name\": \"" << escapeString(player.getName()) << "\",\n";
    json << "    \"className\": \"" << escapeString(player.getClassName()) << "\",\n";
    json << "    \"originName\": \"" << escapeString(player.getOriginName()) << "\",\n";
    json << "    \"level\": " << player.getLevel() << ",\n";
    json << "    \"experience\": " << player.getExperience() << ",\n";
    json << "    \"experienceToNextLevel\": " << player.getExperienceToNextLevel() << ",\n";
    json << "    \"hp\": " << player.getHP() << ",\n";
    json << "    \"maxHP\": " << player.getMaxHP() << ",\n";
    json << "    \"strength\": " << player.getStrength() << ",\n";
    json << "    \"magic\": " << player.getMagic() << ",\n";
    json << "    \"defense\": " << player.getDefense() << ",\n";
    json << "    \"speed\": " << player.getSpeed() << ",\n";
    json << "    \"gold\": " << player.getGold() << ",\n";
    
    // Attribute points
    json << "    \"attributePoints\": {\n";
    json << "      \"available\": " << player.getAttributePoints().getAvailablePoints() << ",\n";
    json << "      \"spentStrength\": " << player.getAttributePoints().getSpentStrength() << ",\n";
    json << "      \"spentMagic\": " << player.getAttributePoints().getSpentMagic() << ",\n";
    json << "      \"spentDefense\": " << player.getAttributePoints().getSpentDefense() << ",\n";
    json << "      \"spentSpeed\": " << player.getAttributePoints().getSpentSpeed() << "\n";
    json << "    },\n";
    
    // Talent tree
    json << "    \"talents\": {\n";
    json << "      \"available\": " << player.getTalentTree().getAvailablePoints() << ",\n";
    json << "      \"ranks\": {\n";
    const auto& talents = player.getTalentTree().getTalents();
    bool first = true;
    for (const auto& pair : talents) {
        if (pair.second.currentRank > 0) {
            if (!first) json << ",\n";
            json << "        \"" << escapeString(pair.first) << "\": " << pair.second.currentRank;
            first = false;
        }
    }
    json << "\n      }\n";
    json << "    },\n";
    
    // Inventory
    json << "    \"inventory\": [\n";
    const auto& items = player.getInventory().getItems();
    for (size_t i = 0; i < items.size(); i++) {
        json << "      {\n";
        json << "        \"name\": \"" << escapeString(items[i].getName()) << "\",\n";
        json << "        \"description\": \"" << escapeString(items[i].getDescription()) << "\",\n";
        json << "        \"type\": " << (int)items[i].getType() << ",\n";
        json << "        \"value\": " << items[i].getValue() << ",\n";
        json << "        \"strBonus\": " << items[i].getStrengthBonus() << ",\n";
        json << "        \"magBonus\": " << items[i].getMagicBonus() << ",\n";
        json << "        \"defBonus\": " << items[i].getDefenseBonus() << ",\n";
        json << "        \"spdBonus\": " << items[i].getSpeedBonus() << ",\n";
        json << "        \"reqClass\": " << (int)items[i].getRequiredClass() << "\n";
        json << "      }";
        if (i < items.size() - 1) json << ",";
        json << "\n";
    }
    json << "    ],\n";
    
    // Save equipped items
    json << "    \"equipped\": {\n";
    
    // Save equipped weapon
    json << "      \"weapon\": ";
    if (player.getEquippedWeapon() != nullptr) {
        const Item* weapon = player.getEquippedWeapon();
        json << "{\n";
        json << "        \"name\": \"" << escapeString(weapon->getName()) << "\",\n";
        json << "        \"description\": \"" << escapeString(weapon->getDescription()) << "\",\n";
        json << "        \"type\": " << (int)weapon->getType() << ",\n";
        json << "        \"value\": " << weapon->getValue() << ",\n";
        json << "        \"strBonus\": " << weapon->getStrengthBonus() << ",\n";
        json << "        \"magBonus\": " << weapon->getMagicBonus() << ",\n";
        json << "        \"defBonus\": " << weapon->getDefenseBonus() << ",\n";
        json << "        \"spdBonus\": " << weapon->getSpeedBonus() << ",\n";
        json << "        \"reqClass\": " << (int)weapon->getRequiredClass() << "\n";
        json << "      }";
    } else {
        json << "null";
    }
    json << ",\n";
    
    // Save equipped armor
    json << "      \"armor\": ";
    if (player.getEquippedArmor() != nullptr) {
        const Item* armor = player.getEquippedArmor();
        json << "{\n";
        json << "        \"name\": \"" << escapeString(armor->getName()) << "\",\n";
        json << "        \"description\": \"" << escapeString(armor->getDescription()) << "\",\n";
        json << "        \"type\": " << (int)armor->getType() << ",\n";
        json << "        \"value\": " << armor->getValue() << ",\n";
        json << "        \"strBonus\": " << armor->getStrengthBonus() << ",\n";
        json << "        \"magBonus\": " << armor->getMagicBonus() << ",\n";
        json << "        \"defBonus\": " << armor->getDefenseBonus() << ",\n";
        json << "        \"spdBonus\": " << armor->getSpeedBonus() << ",\n";
        json << "        \"reqClass\": " << (int)armor->getRequiredClass() << "\n";
        json << "      }";
    } else {
        json << "null";
    }
    json << "\n";
    json << "    }\n";
    
    json << "  }\n";
    json << "}\n";
    
    writeFile(filePath, json.str());
    
    // Update current save file path
    saveFilePath = filePath;
    
    return true;
}

bool SaveManager::loadGame(Player*& player, const string& saveName) {
    string filePath = saveName.empty() ? saveFilePath : getSaveFilePath(saveName);
    string content = readFile(filePath);
    if (content.empty()) return false;
    
    // Simple JSON parsing for our structured format
    try {
        string name, className, originName;
        int level, experience, expToNext, hp, maxHP, strength, magic, defense, speed, gold, attrPoints, talentPoints;
        
        // Helper lambda to extract string value
        auto extractString = [&content](const string& key) -> string {
            size_t pos = content.find("\"" + key + "\"");
            if (pos == string::npos) return "";
            pos = content.find("\"", pos + key.length() + 2);
            if (pos == string::npos) return "";
            size_t endPos = content.find("\"", pos + 1);
            return content.substr(pos + 1, endPos - pos - 1);
        };
        
        // Helper lambda to extract int value
        auto extractInt = [&content](const string& key) -> int {
            size_t pos = content.find("\"" + key + "\"");
            if (pos == string::npos) return 0;
            pos = content.find(":", pos);
            if (pos == string::npos) return 0;
            pos = content.find_first_of("0123456789-", pos);
            if (pos == string::npos) return 0;
            return stoi(content.substr(pos));
        };
        
        // Extract all values
        name = extractString("name");
        className = extractString("className");
        originName = extractString("originName");
        level = extractInt("level");
        experience = extractInt("experience");
        expToNext = extractInt("experienceToNextLevel");
        hp = extractInt("hp");
        maxHP = extractInt("maxHP");
        strength = extractInt("strength");
        magic = extractInt("magic");
        defense = extractInt("defense");
        speed = extractInt("speed");
        gold = extractInt("gold");
        attrPoints = extractInt("attributePoints");
        talentPoints = extractInt("talentPoints");
        
        // Map class and origin names to their indices
        int classChoice = 1; // Default to Warrior
        if (className == "Mage") classChoice = 2;
        else if (className == "Rogue") classChoice = 3;
        else if (className == "Cleric") classChoice = 4;
        else if (className == "Ranger") classChoice = 5;
        
        int originChoice = 1; // Default to Human
        if (originName == "Elf") originChoice = 2;
        else if (originName == "Dwarf") originChoice = 3;
        else if (originName == "Orc") originChoice = 4;
        else if (originName == "Halfling") originChoice = 5;
        
        // Create new player with saved values
        if (player) delete player;
        player = new Player(name, classChoice, originChoice);
        
        // Restore saved stats
        player->setLevel(level);
        player->setExperience(experience);
        player->setHP(hp);
        player->setMaxHP(maxHP);
        player->setStrength(strength);
        player->setMagic(magic);
        player->setDefense(defense);
        player->setSpeed(speed);
        player->setGold(gold);
        
        // Restore attribute points (check if new format exists)
        size_t attrSection = content.find("\"attributePoints\"");
        if (attrSection != string::npos && content.find("{", attrSection) != string::npos) {
            // New format with detailed attribute data
            int availableAttr = extractInt("available");
            int spentStr = extractInt("spentStrength");
            int spentMag = extractInt("spentMagic");
            int spentDef = extractInt("spentDefense");
            int spentSpd = extractInt("spentSpeed");
            player->getAttributePoints().setAvailablePoints(availableAttr);
            player->getAttributePoints().setSpentPoints(spentStr, spentMag, spentDef, spentSpd);
        } else {
            // Old format - just available points
            player->getAttributePoints().setAvailablePoints(attrPoints);
        }
        
        // Restore talent points and ranks
        size_t talentSection = content.find("\"talents\"");
        if (talentSection != string::npos) {
            // Extract talent available points
            size_t availPos = content.find("\"available\"", talentSection);
            if (availPos != string::npos) {
                size_t colonPos = content.find(":", availPos);
                size_t numStart = content.find_first_of("0123456789", colonPos);
                if (numStart != string::npos) {
                    int availTalents = stoi(content.substr(numStart));
                    player->getTalentTree().setAvailablePoints(availTalents);
                }
            }
            
            // Extract talent ranks
            size_t ranksPos = content.find("\"ranks\"", talentSection);
            if (ranksPos != string::npos) {
                size_t openBrace = content.find("{", ranksPos);
                size_t closeBrace = content.find("}", openBrace);
                if (openBrace != string::npos && closeBrace != string::npos) {
                    string ranksSection = content.substr(openBrace + 1, closeBrace - openBrace - 1);
                    
                    // Parse each talent rank
                    size_t pos = 0;
                    while (pos < ranksSection.length()) {
                        size_t quoteStart = ranksSection.find("\"", pos);
                        if (quoteStart == string::npos) break;
                        size_t quoteEnd = ranksSection.find("\"", quoteStart + 1);
                        if (quoteEnd == string::npos) break;
                        
                        string talentName = ranksSection.substr(quoteStart + 1, quoteEnd - quoteStart - 1);
                        size_t colonPos = ranksSection.find(":", quoteEnd);
                        if (colonPos == string::npos) break;
                        
                        size_t numStart = ranksSection.find_first_of("0123456789", colonPos);
                        if (numStart == string::npos) break;
                        
                        size_t numEnd = ranksSection.find_first_not_of("0123456789", numStart);
                        int rank = stoi(ranksSection.substr(numStart, numEnd - numStart));
                        
                        player->getTalentTree().setTalentRank(talentName, rank);
                        pos = numEnd;
                    }
                }
            }
        } else {
            // Old format - just talent points
            player->getTalentTree().setAvailablePoints(talentPoints);
        }
        
        // Restore inventory items (if present in save)
        size_t invSection = content.find("\"inventory\"");
        if (invSection != string::npos) {
            size_t arrayStart = content.find("[", invSection);
            size_t arrayEnd = content.find("]", arrayStart);
            if (arrayStart != string::npos && arrayEnd != string::npos) {
                string invData = content.substr(arrayStart + 1, arrayEnd - arrayStart - 1);
                
                // Parse each item
                size_t pos = 0;
                while (pos < invData.length()) {
                    size_t itemStart = invData.find("{", pos);
                    if (itemStart == string::npos) break;
                    size_t itemEnd = invData.find("}", itemStart);
                    if (itemEnd == string::npos) break;
                    
                    string itemData = invData.substr(itemStart, itemEnd - itemStart + 1);
                    
                    // Extract item properties
                    auto extractItemString = [&itemData](const string& key) -> string {
                        size_t keyPos = itemData.find("\"" + key + "\"");
                        if (keyPos == string::npos) return "";
                        size_t valStart = itemData.find("\"", keyPos + key.length() + 2);
                        if (valStart == string::npos) return "";
                        size_t valEnd = itemData.find("\"", valStart + 1);
                        return itemData.substr(valStart + 1, valEnd - valStart - 1);
                    };
                    
                    auto extractItemInt = [&itemData](const string& key) -> int {
                        size_t keyPos = itemData.find("\"" + key + "\"");
                        if (keyPos == string::npos) return 0;
                        size_t colonPos = itemData.find(":", keyPos);
                        if (colonPos == string::npos) return 0;
                        size_t numStart = itemData.find_first_of("-0123456789", colonPos);
                        if (numStart == string::npos) return 0;
                        return stoi(itemData.substr(numStart));
                    };
                    
                    string itemName = extractItemString("name");
                    string itemDesc = extractItemString("description");
                    int itemType = extractItemInt("type");
                    int itemValue = extractItemInt("value");
                    int strBonus = extractItemInt("strBonus");
                    int magBonus = extractItemInt("magBonus");
                    int defBonus = extractItemInt("defBonus");
                    int spdBonus = extractItemInt("spdBonus");
                    int reqClass = extractItemInt("reqClass");
                    
                    Item item(itemName, itemDesc, (ItemType)itemType, itemValue, 
                             strBonus, magBonus, defBonus, spdBonus, (EquipmentClass)reqClass);
                    player->getInventory().addItem(item);
                    
                    pos = itemEnd + 1;
                }
            }
        }
        
        // Restore equipped items (if present in save)
        size_t equippedSection = content.find("\"equipped\"");
        if (equippedSection != string::npos) {
            // Helper to extract equipped item name and type
            auto getEquippedItemInfo = [&content, equippedSection](const string& slotName, string& outName, int& outType) -> bool {
                size_t slotPos = content.find("\"" + slotName + "\"", equippedSection);
                if (slotPos == string::npos) return false;
                
                size_t colonPos = content.find(":", slotPos);
                if (colonPos == string::npos) return false;
                
                // Check if it's null
                size_t nullPos = content.find("null", colonPos);
                size_t bracePos = content.find("{", colonPos);
                if (nullPos != string::npos && (bracePos == string::npos || nullPos < bracePos)) {
                    return false;
                }
                
                if (bracePos == string::npos) return false;
                size_t closeBrace = content.find("}", bracePos);
                if (closeBrace == string::npos) return false;
                
                string itemData = content.substr(bracePos, closeBrace - bracePos + 1);
                
                // Extract name
                size_t namePos = itemData.find("\"name\"");
                if (namePos != string::npos) {
                    size_t valStart = itemData.find("\"", namePos + 6);
                    if (valStart != string::npos) {
                        size_t valEnd = itemData.find("\"", valStart + 1);
                        if (valEnd != string::npos) {
                            outName = itemData.substr(valStart + 1, valEnd - valStart - 1);
                        }
                    }
                }
                
                // Extract type
                size_t typePos = itemData.find("\"type\"");
                if (typePos != string::npos) {
                    size_t colonPos2 = itemData.find(":", typePos);
                    if (colonPos2 != string::npos) {
                        size_t numStart = itemData.find_first_of("0123456789", colonPos2);
                        if (numStart != string::npos) {
                            outType = stoi(itemData.substr(numStart));
                        }
                    }
                }
                
                return !outName.empty();
            };
            
            // Load equipped weapon
            string weaponName;
            int weaponType = 0;
            if (getEquippedItemInfo("weapon", weaponName, weaponType)) {
                // Find this item in inventory and equip it
                for (size_t i = 0; i < player->getInventory().getItems().size(); i++) {
                    Item* invItem = player->getInventory().getItem(i);
                    if (invItem != nullptr && invItem->getName() == weaponName && 
                        invItem->getType() == (ItemType)weaponType) {
                        player->equipItem(invItem);
                        break;
                    }
                }
            }
            
            // Load equipped armor
            string armorName;
            int armorType = 0;
            if (getEquippedItemInfo("armor", armorName, armorType)) {
                // Find this item in inventory and equip it
                for (size_t i = 0; i < player->getInventory().getItems().size(); i++) {
                    Item* invItem = player->getInventory().getItem(i);
                    if (invItem != nullptr && invItem->getName() == armorName && 
                        invItem->getType() == (ItemType)armorType) {
                        player->equipItem(invItem);
                        break;
                    }
                }
            }
        }
        
        // Update current save file path
        saveFilePath = filePath;
        
        return true;
    } catch (...) {
        return false;
    }
}

bool SaveManager::saveExists(const string& saveName) const {
    string filePath = saveName.empty() ? saveFilePath : getSaveFilePath(saveName);
    ifstream file(filePath);
    return file.good();
}

void SaveManager::deleteSave(const string& saveName) {
    string filePath = saveName.empty() ? saveFilePath : getSaveFilePath(saveName);
    remove(filePath.c_str());
}
