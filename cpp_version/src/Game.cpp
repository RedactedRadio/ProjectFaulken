#include "Game.h"
#include "Console.h"
#include "GameOver.h"
#include "TitleScreen.h"
#include <iostream>
#include <cstdlib>

Game::Game()
    : currentRoom(Room::ZeroCentral) {
    player = Player();
    initRooms();
}

void Game::initRooms() {
    roomData[Room::ZeroCentral] = {
        "You are in Zero Central.",
        {
            {"north", Room::ComputerSouth},
            {"east", Room::ZeroEast},
            {"west", Room::ZeroWest}
        },
        {{"ID badge", "Your metal ID badge is made from the latest technology."}},
        nullptr
    };

    roomData[Room::ZeroWest] = {
        "You're in Zero West.",
        {
            {"east", Room::ZeroCentral},
            {"west", Room::Security}
        },
        {},
        nullptr
    };

    roomData[Room::ZeroEast] = {
        "You're in Zero East.",
        {
            {"west", Room::ZeroCentral},
            {"east", Room::OfficeSpace}
        },
        {{"flashlight", "automatically turns on in low light."}},
        nullptr
    };

    roomData[Room::ComputerSouth] = {
        "Computer Room South",
        {
            {"north", Room::ComputerNorth},
            {"west", Room::Storage},
            {"south", Room::ZeroCentral},
            {"east", Room::Corridor}
        },
        {},
        nullptr
    };

    roomData[Room::ComputerNorth] = {
        "Computer Room North",
        {
            {"south", Room::ComputerSouth},
            {"west", Room::Control}
        },
        {},
        nullptr
    };

    roomData[Room::Security] = {
        "You're in the Security Office.",
        {
            {"east", Room::ZeroWest},
            {"north", Room::Elevator}
        },
        {{"key", "A small brass key"}},
        nullptr
    };

    roomData[Room::Elevator] = {
        "The Elevator Room",
        {
            {"south", Room::Security},
            {"north", Room::Control}
        },
        {},
        [this]() {
            if (elevStatus != "juiced") {
                std::cout << "The elevator is dark and lifeless. The power must be out.\n";
                std::cout << "You can't use the elevator without power.\n";
                std::cout << "Let's go back and find a way to turn it on.\n\n";
                enterRoom(Room::Security);
            } else {
                std::cout << "The elevator lights are on! The power is working.\n";
                std::cout << "You can now access the upper floors.\n";
                std::cout << "**LEVEL 1 COMPLETE!**\n";
            }
        }
    };

    roomData[Room::OfficeSpace] = {
        "Office Space",
        {
            {"west", Room::ZeroEast},
            {"north", Room::Stairwell}
        },
        {{"paper", "A small piece of paper with notes"}},
        nullptr
    };

    roomData[Room::Stairwell] = {
        "The Stairwell",
        {
            {"south", Room::OfficeSpace},
            {"west", Room::Corridor}
        },
        {},
        nullptr
    };

    roomData[Room::Corridor] = {
        "The Corridor",
        {
            {"east", Room::Stairwell},
            {"north", Room::OfficeNorth},
            {"south", Room::OfficeSouth},
            {"west", Room::ComputerSouth}
        },
        {},
        nullptr
    };

    roomData[Room::OfficeNorth] = {
        "Office North",
        {
            {"south", Room::Corridor}
        },
        {},
        nullptr
    };

    roomData[Room::OfficeSouth] = {
        "Office South",
        {
            {"north", Room::Corridor}
        },
        {},
        nullptr
    };

    roomData[Room::Storage] = {
        "Storage Room",
        {
            {"east", Room::ComputerSouth}
        },
        {{"batteries", "A pack of batteries. These might be useful for the flashlight."}},
        nullptr
    };

    roomData[Room::Control] = {
        "Control Room",
        {
            {"east", Room::ComputerNorth}
        },
        {},
        [this]() {
            std::cout << "As you enter, you see that this is a mechanical room\n";
            std::cout << "with two large electrical switches secured by large padlocks.\n";
        }
    };
}

void Game::clearScreen() const {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void Game::startGame() {
    TitleScreen titleScreen;
    int choice = titleScreen.display();

    if (choice == 0) {
        return;
    } else if (choice == 1) {
        player.newGame();
        enterRoom(Room::ZeroCentral);
        actions();
    } else if (choice == 2) {
        player.loadGame(this);
        actions();
    }
}

void Game::enterRoom(Room room) {
    currentRoom = room;
    const RoomData& roomInfo = roomData.at(room);
    desc = roomInfo.description;
    items = roomInfo.items;

    clearScreen();
    std::cout << desc << "\n";
    if (roomInfo.onEnter) {
        roomInfo.onEnter();
    }
}

void Game::zeroCentral() {
    enterRoom(Room::ZeroCentral);
}

void Game::zeroWest() {
    enterRoom(Room::ZeroWest);
}

void Game::zeroEast() {
    enterRoom(Room::ZeroEast);
}

void Game::terminalA() {
    enterRoom(Room::ComputerSouth);
}

void Game::terminalB() {
    enterRoom(Room::ComputerNorth);
}

void Game::security() {
    enterRoom(Room::Security);
}

void Game::elevatorRoom() {
    enterRoom(Room::Elevator);
}

void Game::officeSpace() {
    enterRoom(Room::OfficeSpace);
}

void Game::stairwell() {
    enterRoom(Room::Stairwell);
}

void Game::corridor() {
    enterRoom(Room::Corridor);
}

void Game::officeNorth() {
    enterRoom(Room::OfficeNorth);
}

void Game::officeSouth() {
    enterRoom(Room::OfficeSouth);
}

void Game::storage() {
    enterRoom(Room::Storage);
}

void Game::control() {
    enterRoom(Room::Control);
}

void Game::actions() {
    while (!shouldExit) {
        std::string move;
        std::cout << "ACTION:>";
        std::getline(std::cin, move);
        handleInput(move);
    }
}

void Game::handleInput(const std::string& move) {
    if (move == "north" || move == "south" || move == "east" || move == "west") {
        moveDirection(move);
        return;
    }

    if (move == "map") {
        player.map(getPosition());
        return;
    }

    if (move == "take") {
        player.take(items);
        return;
    }

    if (move == "inv") {
        player.inventory();
        return;
    }

    if (move == "help") {
        player.help();
        return;
    }

    if (move == "look") {
        player.look(getPosition(), items, player.getLoot());
        return;
    }

    if (move == "save") {
        player.saveGame(getPosition());
        return;
    }

    if (move == "load") {
        player.loadGame(this);
        return;
    }

    if (move == "use term") {
        if (currentRoom == Room::ComputerSouth || currentRoom == Room::ComputerNorth) {
            Console console;
            console.startTerminal();
        } else {
            std::cout << "There's no terminal here.\n";
        }
        return;
    }

    if (move == "unlock") {
        if (player.swStatus == "locked") {
            if (player.getLoot().find("key") != player.getLoot().end()) {
                std::cout << "You have unlocked the switches! Now, <energize> them!\n";
                player.swStatus = "unlocked";
            } else {
                std::cout << "You need the key to unlock the switches.\n";
            }
        }
        return;
    }

    if (move == "energize") {
        if (player.swStatus == "unlocked") {
            elevStatus = "juiced";
            std::cout << "As you throw the switches on, you can feel the power flowing through the lines.\n";
            std::cout << "The emergency lighting is now on. Let's check the elevator!\n";
        } else {
            std::cout << "These switches are locked. You must <unlock> them first.\n";
        }
        return;
    }

    if (move == "scan id") {
        std::cout << "You hold your badge up to the scanner...\n";
        return;
    }

    if (move == "quit") {
        GameOver go;
        std::string choice;
        std::cout << "Save before quitting? <y><n>:>";
        std::getline(std::cin, choice);
        
        if (choice == "y") {
            player.saveGame(getPosition());
            go.gameOverTxt();
            shouldExit = true;
        } else if (choice == "n") {
            std::cout << "Are you sure?:>";
            std::getline(std::cin, choice);
            if (choice == "y") {
                go.gameOverTxt();
                shouldExit = true;
            }
        } else {
            std::cout << "Invalid command.\n";
        }
        return;
    }

    if (move == "nav") {
        printNavInfo();
        return;
    }

    std::cout << "Invalid command. Type <help> for available commands.\n";
}

bool Game::moveDirection(const std::string& direction) {
    const auto& exits = roomData.at(currentRoom).exits;
    auto it = exits.find(direction);
    if (it == exits.end()) {
        std::cout << "You can't go " << direction << " from here.\n";
        return false;
    }

    Room nextRoom = it->second;
    if (nextRoom == Room::Elevator && elevStatus != "juiced") {
        std::cout << "The elevator is still powered off. I need to find a way to turn it on.\n";
        return false;
    }

    enterRoom(nextRoom);
    return true;
}

std::string Game::roomName(Room room) const {
    switch (room) {
        case Room::ZeroCentral: return "Zero Central";
        case Room::ZeroWest: return "Zero West";
        case Room::ZeroEast: return "Zero East";
        case Room::ComputerSouth: return "Computer Room South";
        case Room::ComputerNorth: return "Computer Room North";
        case Room::Security: return "Security Office";
        case Room::Elevator: return "Elevator";
        case Room::OfficeSpace: return "Office Space";
        case Room::Stairwell: return "Stairwell";
        case Room::Corridor: return "Corridor";
        case Room::OfficeNorth: return "Office North";
        case Room::OfficeSouth: return "Office South";
        case Room::Storage: return "Storage Room";
        case Room::Control: return "Control Room";
        default: return "Unknown Location";
    }
}

void Game::printNavInfo() const {
    std::cout << "\n=== Navigation Information ===\n\n";
    std::cout << roomName(currentRoom) << ":\n";
    const auto& exits = roomData.at(currentRoom).exits;

    for (const auto& [direction, room] : exits) {
        std::cout << "  <" << direction << "> - " << roomName(room) << "\n";
    }

    if (currentRoom == Room::ComputerNorth) {
        std::cout << "  <use term> - Use the terminal here\n";
    }

    if (currentRoom == Room::OfficeNorth || currentRoom == Room::OfficeSouth) {
        std::cout << "  [This room is currently locked]\n";
    }

    std::cout << "\n";
}
