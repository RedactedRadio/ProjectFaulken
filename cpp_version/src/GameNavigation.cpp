#include "Game.h"
#include <cctype>

namespace {
std::string toUpper(std::string text) {
    for (char& c : text) {
        c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
    }
    return text;
}
}

bool Game::moveDirection(const std::string& direction) {
    const auto& exits = roomData.at(gameState.currentRoom).exits;
    auto it = exits.find(direction);
    if (it == exits.end()) {
        ui->printLine("You can't go " + direction + " from here.");
        playSound("error");
        return false;
    }

    Room nextRoom = it->second;
    if (nextRoom == Room::Elevator && !gameState.elevatorPowered) {
        ui->printLine("The elevator is still powered off. I need to find a way to turn it on.");
        playSound("error");
        return false;
    }

    if (nextRoom == Room::Control) {
        gameState.controlAccessPending = true;
        ui->setColor("\033[33m");
        ui->printLine("Authorized Access Only! \n<scan id> for access.");
        ui->resetColor();
        return false;
    }

    enterRoom(nextRoom);
    return true;
}

void Game::printNavInfo() const {
    ui->printLine("");
    printRoomHeader(gameState.currentRoom);
    printRoomNavInfo();
}

void Game::printRoomHeader(Room room) const {
    ui->setColor("\033[36m");
    ui->printLine(toUpper(roomName(room)));
    ui->printLine("================================");
    ui->resetColor();
}

void Game::printRoomNavInfo() const {
    const auto& exits = roomData.at(gameState.currentRoom).exits;

    ui->setColor("\033[36m");
    for (const auto& [direction, room] : exits) {
        ui->printLine("  <" + direction + "> - " + roomName(room));
    }
    ui->resetColor();

    if (gameState.currentRoom == Room::ComputerNorth) {
        ui->setColor("\033[33m");
        ui->printLine("  <use term> - Use the terminal here");
        ui->resetColor();
    }

    if (gameState.currentRoom == Room::OfficeNorth || gameState.currentRoom == Room::OfficeSouth) {
        ui->setColor("\033[31m");
        ui->printLine("  [This room is currently locked]");
        ui->resetColor();
    }

    ui->printLine("");
}

void Game::printCompactRoomNavInfo() const {
    const auto& exits = roomData.at(gameState.currentRoom).exits;
    std::string navLine = "Exits: ";
    bool first = true;

    for (const auto& [direction, room] : exits) {
        if (!first) {
            navLine += " | ";
        }
        navLine += "<" + direction + "> " + roomName(room);
        first = false;
    }

    ui->setColor("\033[36m");
    ui->printLine(navLine);
    ui->resetColor();

    if (gameState.currentRoom == Room::ComputerNorth) {
        ui->setColor("\033[33m");
        ui->printLine("Actions: <use term> Terminal");
        ui->resetColor();
    }

    if (gameState.currentRoom == Room::OfficeNorth || gameState.currentRoom == Room::OfficeSouth) {
        ui->setColor("\033[31m");
        ui->printLine("Status: locked");
        ui->resetColor();
    }
}
