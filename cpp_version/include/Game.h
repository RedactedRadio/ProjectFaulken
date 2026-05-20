#ifndef GAME_H
#define GAME_H

#include "IGameUI.h"
#include "Player.h"
#include "Console.h"
#include "GameOver.h"
#include "TitleScreen.h"
#include <string>
#include <map>
#include <functional>
#include <vector>
#include <deque>

class Game {
public:
    enum class Room {
        ZeroCentral = 1,
        ZeroWest,
        ZeroEast,
        ComputerSouth,
        ComputerNorth,
        Security,
        Elevator,
        OfficeSpace,
        Stairwell,
        Corridor,
        OfficeNorth,
        OfficeSouth,
        Storage,
        Control
    };

    // GameState struct to centralize state
    struct GameState {
        Room currentRoom = Room::ZeroCentral;
        std::map<std::string, std::string> inventory;
        std::string playerName;
        bool elevatorPowered = false;
        bool switchesLocked = true;
        bool shouldExit = false;
        bool controlAccessPending = false;
        std::deque<std::string> commandHistory;
        size_t historyIndex = 0;
        bool enableSound = true;
    };

    Game(IGameUI* ui);
    
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
    
    void enterRoom(Room room);
    Room getCurrentRoom() const { return gameState.currentRoom; }
    int getPosition() const { return static_cast<int>(gameState.currentRoom); }
    void setPosition(int p) { gameState.currentRoom = static_cast<Room>(p); }
    const std::map<std::string, std::string>& getItems() const { return items; }
    const std::string& getDescription() const { return desc; }
    Player* getPlayer() { return &player; }
    
    // New methods for enhanced UX
    std::string normalizeCommand(const std::string& cmd) const;
    std::vector<std::string> getCommandSuggestions(const std::string& partial) const;
    void handleInvalidCommand(const std::string& cmd);
    void addToCommandHistory(const std::string& cmd);
    std::string getPreviousCommand();
    std::string getNextCommand();
    void playSound(const std::string& soundType) const;
    void loadTitanPointe();
    
private:
    struct RoomData {
        std::string description;
        std::map<std::string, Room> exits;
        std::map<std::string, std::string> items;
        std::function<void()> onEnter;
    };

    GameState gameState;
    std::map<Room, RoomData> roomData;
    std::string desc;
    std::map<std::string, std::string> items;
    IGameUI* ui;
    Player player;
    
    // Command aliases for better UX
    std::map<std::string, std::string> commandAliases = {
        {"n", "north"}, {"s", "south"}, {"e", "east"}, {"w", "west"},
        {"i", "inv"}, {"inventory", "inv"}, {"l", "look"},
        {"m", "map"}, {"h", "help"}, {"q", "quit"},
        {"t", "take"}, {"u", "use term"}, {"un", "unlock"},
        {"en", "energize"}, {"sc", "scan id"}, {"na", "nav"},
        {"sa", "save"}, {"lo", "load"}
    };
    
    void initRooms();
    void handleInput(const std::string& move);
    bool moveDirection(const std::string& direction);
    std::string roomName(Room room) const;
    void printRoomHeader(Room room) const;
    void printNavInfo() const;
    void printRoomNavInfo() const;
    void printCompactRoomNavInfo() const;
};

#endif
