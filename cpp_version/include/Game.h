#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Console.h"
#include "GameOver.h"
#include "TitleScreen.h"
#include <string>
#include <map>

class Game {
public:
    Game();
    
    void startGame();
    void actions();
    
    // Room transitions
    void zeroCentral();
    void zeroWest();
    void zeroEast();
    void terminalA();
    void terminalB();
    void security();
    void elevatorRoom();
    void officeSpace();
    void stairwell();
    void corridor();
    void officeNorth();
    void officeSouth();
    void storage();
    void control();
    
    // Getters/Setters
    int getPosition() const { return pos; }
    void setPosition(int p) { pos = p; }
    const std::map<std::string, std::string>& getItems() const { return items; }
    const std::string& getDescription() const { return desc; }
    Player* getPlayer() { return &player; }
    
    // Game state
    std::string elevStatus = "";
    bool shouldExit = false;
    
private:
    int pos;
    std::string desc;
    std::map<std::string, std::string> items;
    Player player;
    
    void clearScreen() const;
    void handleInput(const std::string& move);
    void printNavInfo() const;
};

#endif
