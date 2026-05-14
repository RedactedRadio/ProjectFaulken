#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <map>
#include <vector>

class Game;  // Forward declaration

class Player {
public:
    Player();
    
    // Game actions
    void actions(Game* game);
    void inventory() const;
    void take(const std::map<std::string, std::string>& items);
    void map(int pos) const;
    void help() const;
    void look(int pos, const std::map<std::string, std::string>& items, const std::map<std::string, std::string>& playerLoot) const;
    
    // Save/Load
    void newGame();
    void saveGame(int position);
    void loadGame(Game* game);
    
    // Getters
    const std::map<std::string, std::string>& getLoot() const { return loot; }
    const std::string& getLastReadData() const { return readData; }
    
    // State management (will be moved to GameState later)
    std::string swStatus = "locked";
    std::string elevStatus = "";
    
private:
    std::map<std::string, std::string> loot;
    std::string name;
    std::string saveData;
    std::string readData;
    
    void printSlowText(const std::string& text, double delayMs = 0.009) const;
};

#endif
