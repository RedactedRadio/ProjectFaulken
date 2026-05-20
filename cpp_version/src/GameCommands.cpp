#include "Game.h"
#include "Console.h"
#include "GameOver.h"

void Game::handleInput(const std::string& move) {
    if (move == "north" || move == "south" || move == "east" || move == "west") {
        moveDirection(move);
        playSound("move");
        return;
    }

    if (move == "map") {
        player.map(getPosition(), ui);
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
            Console console(ui);
            console.startTerminal();
            enterRoom(Room::ComputerNorth);
            playSound("terminal");
        } else {
            ui->printLine("There's no terminal here.");
            playSound("error");
        }
        return;
    }

    if (move == "unlock") {
        if (player.swStatus == "locked") {
            if (player.getLoot().find("key") != player.getLoot().end()) {
                ui->printLine("You have unlocked the switches! Now, <energize> them!");
                player.swStatus = "unlocked";
                gameState.switchesLocked = false;
                playSound("unlock");
            } else {
                ui->printLine("You need the key to unlock the switches.");
                playSound("error");
            }
        } else {
            ui->printLine("The switches are already unlocked.");
            playSound("error");
        }
        return;
    }

    if (move == "energize") {
        if (player.swStatus == "unlocked") {
            gameState.elevatorPowered = true;
            ui->printLine("As you throw the switches on, you can feel the power flowing through the lines.");
            ui->printLine("The emergency lighting is now on. Let's check the elevator!");
            playSound("power");
        } else {
            ui->printLine("These switches are locked. You must <unlock> them first.");
            playSound("error");
        }
        return;
    }

    if (move == "scan id") {
        if (!gameState.controlAccessPending) {
            ui->setColor("\033[31m");
            ui->printLine("There is no ID scanner here.");
            ui->resetColor();
            playSound("error");
            return;
        }

        if (player.getLoot().find("ID badge") == player.getLoot().end()) {
            ui->setColor("\033[31m");
            ui->printLine("Access denied. ID badge required.");
            ui->resetColor();
            gameState.controlAccessPending = false;
            playSound("error");
            enterRoom(Room::ComputerNorth);
            return;
        }

        gameState.controlAccessPending = false;
        enterRoom(Room::Control);
        ui->setColor("\033[32m");
        ui->printLine("Access Granted. Welcome, Faulken, S.");
        ui->resetColor();
        playSound("scan");
        return;
    }

    if (move == "quit") {
        GameOver go(ui);
        std::string choice;
        ui->print("Save before quitting? <y><n>:>");
        choice = ui->readLine();

        if (choice == "y" || choice == "Y") {
            player.saveGame(getPosition());
            loadTitanPointe();
            go.gameOverTxt();
            gameState.shouldExit = true;
        } else if (choice == "n" || choice == "N") {
            ui->print("Are you sure?:>");
            choice = ui->readLine();
            if (choice == "y" || choice == "Y") {
                loadTitanPointe();
                go.gameOverTxt();
                gameState.shouldExit = true;
            } else {
                ui->printLine("Quit cancelled.");
                playSound("ui");
            }
        } else {
            ui->printLine("Please enter 'y' or 'n'.");
            playSound("error");
        }
        return;
    }

    if (move == "nav") {
        printNavInfo();
        playSound("ui");
        return;
    }

    handleInvalidCommand(move);
}
