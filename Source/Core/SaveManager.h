#ifndef SAVEMANAGER_H
#define SAVEMANAGER_H

#include <string>
#include <fstream>
#include <vector>
#include "../Entities/Player/Player.h"

class SaveManager {
private:
    std::string saveFilePath;

public:
    SaveManager(const std::string& filePath = "savegame.json");
    
    bool saveGame(const Player& player, const std::string& saveName = "");
    bool loadGame(Player*& player, const std::string& saveName = "");
    bool saveExists(const std::string& saveName = "") const;
    void deleteSave(const std::string& saveName = "");
    std::vector<std::string> listSaveFiles() const;
    void setSaveFile(const std::string& saveName);
    std::string getCurrentSaveFile() const { return saveFilePath; }
    
private:
    std::string escapeString(const std::string& str) const;
    std::string readFile(const std::string& path) const;
    void writeFile(const std::string& path, const std::string& content) const;
    std::string getSaveFilePath(const std::string& saveName) const;
};

#endif
