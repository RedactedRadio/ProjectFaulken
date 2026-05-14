#include "Game.h"
#include "Console.h"
#include "GameOver.h"
#include "TitleScreen.h"
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <limits>
#include <fstream>
#include <thread>
#include <chrono>
#include <algorithm>
#include <limits>

Game::Game()
    : gameState{} {
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
            if (!gameState.elevatorPowered) {
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
    gameState.currentRoom = room;
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
    while (!gameState.shouldExit) {
        std::string move;
        std::cout << "ACTION:>";
        std::getline(std::cin, move);
        
        // Handle empty input
        if (move.empty()) continue;
        
        // Add to command history
        addToCommandHistory(move);
        
        // Normalize command using aliases
        std::string normalizedCmd = normalizeCommand(move);
        handleInput(normalizedCmd);
    }
}

void Game::handleInput(const std::string& move) {
    if (move == "north" || move == "south" || move == "east" || move == "west") {
        moveDirection(move);
        playSound("move");
        return;
    }

    if (move == "map") {
        player.map(getPosition());
        playSound("ui");
        return;
    }

    if (move == "take") {
        player.take(items);
        playSound("item");
        return;
    }

    if (move == "inv") {
        player.inventory();
        playSound("ui");
        return;
    }

    if (move == "help") {
        player.help();
        playSound("ui");
        return;
    }

    if (move == "look") {
        player.look(getPosition(), items, player.getLoot());
        playSound("ui");
        return;
    }

    if (move == "save") {
        player.saveGame(getPosition());
        playSound("save");
        return;
    }

    if (move == "load") {
        player.loadGame(this);
        playSound("load");
        return;
    }

    if (move == "use term") {
        if (gameState.currentRoom == Room::ComputerSouth || gameState.currentRoom == Room::ComputerNorth) {
            Console console;
            console.startTerminal();
            playSound("terminal");
        } else {
            std::cout << "There's no terminal here.\n";
            playSound("error");
        }
        return;
    }

    if (move == "unlock") {
        if (player.swStatus == "locked") {
            if (player.getLoot().find("key") != player.getLoot().end()) {
                std::cout << "You have unlocked the switches! Now, <energize> them!\n";
                player.swStatus = "unlocked";
                gameState.switchesLocked = false;
                playSound("unlock");
            } else {
                std::cout << "You need the key to unlock the switches.\n";
                playSound("error");
            }
        } else {
            std::cout << "The switches are already unlocked.\n";
            playSound("error");
        }
        return;
    }

    if (move == "energize") {
        if (player.swStatus == "unlocked") {
            gameState.elevatorPowered = true;
            std::cout << "As you throw the switches on, you can feel the power flowing through the lines.\n";
            std::cout << "The emergency lighting is now on. Let's check the elevator!\n";
            playSound("power");
        } else {
            std::cout << "These switches are locked. You must <unlock> them first.\n";
            playSound("error");
        }
        return;
    }

    if (move == "scan id") {
        std::cout << "You hold your badge up to the scanner...\n";
        playSound("scan");
        return;
    }

    if (move == "quit") {
        GameOver go;
        std::string choice;
        std::cout << "Save before quitting? <y><n>:>";
        std::getline(std::cin, choice);
        
        if (choice == "y" || choice == "Y") {
            player.saveGame(getPosition());
            loadTitanPointe(); // Show titan pointe before game over
            go.gameOverTxt();
            gameState.shouldExit = true;
        } else if (choice == "n" || choice == "N") {
            std::cout << "Are you sure?:>";
            std::getline(std::cin, choice);
            if (choice == "y" || choice == "Y") {
                loadTitanPointe(); // Show titan pointe before game over
                go.gameOverTxt();
                gameState.shouldExit = true;
            } else {
                std::cout << "Quit cancelled.\n";
                playSound("ui");
            }
        } else {
            std::cout << "Please enter 'y' or 'n'.\n";
            playSound("error");
        }
        return;
    }

    if (move == "nav") {
        printNavInfo();
        playSound("ui");
        return;
    }

    // Handle invalid command with suggestions
    handleInvalidCommand(move);
}

bool Game::moveDirection(const std::string& direction) {
    const auto& exits = roomData.at(gameState.currentRoom).exits;
    auto it = exits.find(direction);
    if (it == exits.end()) {
        std::cout << "You can't go " << direction << " from here.\n";
        playSound("error");
        return false;
    }

    Room nextRoom = it->second;
    if (nextRoom == Room::Elevator && !gameState.elevatorPowered) {
        std::cout << "The elevator is still powered off. I need to find a way to turn it on.\n";
        playSound("error");
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
    std::cout << roomName(gameState.currentRoom) << ":\n";
    const auto& exits = roomData.at(gameState.currentRoom).exits;

    for (const auto& [direction, room] : exits) {
        std::cout << "  <" << direction << "> - " << roomName(room) << "\n";
    }

    if (gameState.currentRoom == Room::ComputerNorth) {
        std::cout << "  <use term> - Use the terminal here\n";
    }

    if (gameState.currentRoom == Room::OfficeNorth || gameState.currentRoom == Room::OfficeSouth) {
        std::cout << "  [This room is currently locked]\n";
    }

    std::cout << "\n";
}

// New methods for enhanced UX

std::string Game::normalizeCommand(const std::string& cmd) const {
    std::string lowerCmd = cmd;
    std::transform(lowerCmd.begin(), lowerCmd.end(), lowerCmd.begin(), ::tolower);
    
    auto it = commandAliases.find(lowerCmd);
    if (it != commandAliases.end()) {
        return it->second;
    }
    return lowerCmd;
}

std::vector<std::string> Game::getCommandSuggestions(const std::string& partial) const {
    std::vector<std::string> suggestions;
    std::string lowerPartial = partial;
    std::transform(lowerPartial.begin(), lowerPartial.end(), lowerPartial.begin(), ::tolower);
    
    // Check aliases
    for (const auto& [alias, command] : commandAliases) {
        if (alias.find(lowerPartial) == 0) {
            suggestions.push_back(alias);
        }
    }
    
    // Check main commands
    std::vector<std::string> mainCommands = {
        "north", "south", "east", "west", "map", "take", "inv", "help", 
        "look", "save", "load", "use term", "unlock", "energize", 
        "scan id", "quit", "nav"
    };
    
    for (const std::string& cmd : mainCommands) {
        if (cmd.find(lowerPartial) == 0) {
            suggestions.push_back(cmd);
        }
    }
    
    // Remove duplicates
    std::sort(suggestions.begin(), suggestions.end());
    suggestions.erase(std::unique(suggestions.begin(), suggestions.end()), suggestions.end());
    
    return suggestions;
}

void Game::handleInvalidCommand(const std::string& cmd) {
    std::cout << "Unknown command: '" << cmd << "'\n";
    playSound("error");
    
    // Get suggestions
    auto suggestions = getCommandSuggestions(cmd);
    if (!suggestions.empty()) {
        std::cout << "Did you mean: ";
        for (size_t i = 0; i < suggestions.size() && i < 3; ++i) {
            std::cout << suggestions[i];
            if (i < suggestions.size() - 1 && i < 2) std::cout << ", ";
        }
        if (suggestions.size() > 3) std::cout << "...";
        std::cout << "?\n";
    }
    
    std::cout << "Type 'help' for available commands.\n";
}

void Game::addToCommandHistory(const std::string& cmd) {
    if (!cmd.empty()) {
        gameState.commandHistory.push_back(cmd);
        if (gameState.commandHistory.size() > 50) { // Keep last 50 commands
            gameState.commandHistory.pop_front();
        }
        gameState.historyIndex = gameState.commandHistory.size();
    }
}

std::string Game::getPreviousCommand() {
    if (gameState.historyIndex > 0) {
        gameState.historyIndex--;
        return gameState.commandHistory[gameState.historyIndex];
    }
    return "";
}

std::string Game::getNextCommand() {
    if (gameState.historyIndex < gameState.commandHistory.size() - 1) {
        gameState.historyIndex++;
        return gameState.commandHistory[gameState.historyIndex];
    }
    return "";
}

void Game::playSound(const std::string& soundType) const {
    if (!gameState.enableSound) return;
    
    // Simple console beep for different sound types
    if (soundType == "move") {
        std::cout << "\a"; // Bell character for movement
    } else if (soundType == "item") {
        std::cout << "\a\a"; // Double beep for items
    } else if (soundType == "error") {
        std::cout << "\a\a\a"; // Triple beep for errors
    } else if (soundType == "save") {
        std::cout << "\a"; // Single beep for save
    } else if (soundType == "load") {
        std::cout << "\a\a"; // Double beep for load
    } else if (soundType == "power") {
        std::cout << "\a\a\a\a"; // Quadruple beep for power activation
    } else if (soundType == "unlock") {
        std::cout << "\a\a"; // Double beep for unlock
    } else if (soundType == "scan") {
        std::cout << "\a"; // Single beep for scan
    } else if (soundType == "terminal") {
        std::cout << "\a\a\a"; // Triple beep for terminal
    } else {
        std::cout << "\a"; // Default beep for UI actions
    }
}

void Game::loadTitanPointe() {
    std::ifstream file("../src/titanpointe.txt");
    if (!file.is_open()) {
        std::cout << "Could not load Titan Pointe display.\n";
        return;
    }
    
    std::string line;
    std::cout << "\033[32m"; // Green color
    while (std::getline(file, line)) {
        std::cout << line << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Slow scroll effect
    }
    std::cout << "\033[0m"; // Reset color
    file.close();
    
    // Wait for user to continue
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
