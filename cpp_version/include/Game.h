#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Console.h"
#include "GameOver.h"
#include "TitleScreen.h"
#include <string>
#include <map>
#include <functional>

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
    
    void enterRoom(Room room);
    Room getCurrentRoom() const { return currentRoom; }
    int getPosition() const { return static_cast<int>(currentRoom); }
    void setPosition(int p) { currentRoom = static_cast<Room>(p); }
    const std::map<std::string, std::string>& getItems() const { return items; }
    const std::string& getDescription() const { return desc; }
    Player* getPlayer() { return &player; }
    
    // Game state
    std::string elevStatus = "";
    bool shouldExit = false;
    
private:
    struct RoomData {
        std::string description;
        std::map<std::string, Room> exits;
        std::map<std::string, std::string> items;
        std::function<void()> onEnter;
    };

    Room currentRoom;
    std::map<Room, RoomData> roomData;
    std::string desc;
    std::map<std::string, std::string> items;
    Player player;
    
    void clearScreen() const;
    void initRooms();
    void handleInput(const std::string& move);
    bool moveDirection(const std::string& direction);
    std::string roomName(Room room) const;
    void printNavInfo() const;
};

#endif
