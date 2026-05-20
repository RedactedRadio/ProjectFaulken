#include "Game.h"

void Game::initRooms() {
    roomData[Room::ZeroCentral] = {
        "You are in Zero Central.",
        {
            {"north", Room::ComputerSouth},
            {"east", Room::ZeroEast},
            {"west", Room::ZeroWest}
        },
        {{"ID badge", "The badge emits a faint glow. Hmmmm..."}},
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
        [this]() {
            if (player.getLoot().find("flashlight") == player.getLoot().end()) {
                ui->printLine("You've tripped on a metallic object! \nYou can't see in this darkness! \n<take> the object you tripped on!");
            }
        }
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
        {{"key", "A large heavy key."}},
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
                ui->printLine("The elevator is dark and lifeless. \nThe power must be out.");
                ui->printLine("You can't use the elevator without power.");
                ui->printLine("Let's go back and find a way to turn it on.");
                enterRoom(Room::Security);
            } else {
                ui->printLine("The elevator lights are on! The power is working.");
                ui->printLine("You can now access the upper floors.");
                ui->printLine("**LEVEL 1 COMPLETE!**");
            }
        }
    };

    roomData[Room::OfficeSpace] = {
        "Office Space",
        {
            {"west", Room::ZeroEast},
            {"north", Room::Stairwell}
        },
        {{"paper", "You see a small piece of paper. The writing makes no sense."}},
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
        {{"batteries", "Looks like a pack of batteries. \nThese might be useful for the flashlight."}},
        nullptr
    };

    roomData[Room::Control] = {
        "Control Room",
        {
            {"east", Room::ComputerNorth}
        },
        {},
        [this]() {
            ui->printLine("As your flashlight illuminates the space,\n this is a mechanical room");
            ui->printLine("with two large electrical switches secured \nby large padlocks.");
        }
    };
}

void Game::enterRoom(Room room) {
    gameState.currentRoom = room;
    const RoomData& roomInfo = roomData.at(room);
    desc = roomInfo.description;
    items = roomInfo.items;

    ui->clearScreen();
    printRoomHeader(room);
    printCompactRoomNavInfo();
    ui->printLine("");
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
