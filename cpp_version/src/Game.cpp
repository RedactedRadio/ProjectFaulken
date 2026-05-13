#include "Game.h"
#include "Console.h"
#include "GameOver.h"
#include "TitleScreen.h"
#include <iostream>
#include <cstdlib>

Game::Game() 
    : pos(0) {
    player = Player();
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
        return;  // Exit
    } else if (choice == 1) {
        player.newGame();
        zeroCentral();
    } else if (choice == 2) {
        player.loadGame(this);
    }
}

void Game::zeroCentral() {
    pos = 1;
    desc = "You are in Zero Central.";
    items = {{"ID badge", "Your metal ID badge is made from the latest technology."}};
    
    clearScreen();
    std::cout << desc << "\n";
    
    actions();
}

void Game::zeroWest() {
    pos = 2;
    desc = "You're in Zero West.";
    items = {};
    
    clearScreen();
    std::cout << desc << "\n";
    
    actions();
}

void Game::zeroEast() {
    pos = 3;
    desc = "You're in Zero East.";
    items = {{"flashlight", "automatically turns on in low light."}};
    
    clearScreen();
    std::cout << desc << "\n";
    
    actions();
}

void Game::terminalA() {
    pos = 4;
    desc = "Computer Room South";
    items = {};
    
    clearScreen();
    std::cout << desc << "\n";
    
    actions();
}

void Game::terminalB() {
    pos = 5;
    desc = "Computer Room North";
    items = {};
    
    clearScreen();
    std::cout << desc << "\n";
    
    actions();
}

void Game::security() {
    pos = 6;
    desc = "You're in the Security Office.";
    items = {{"key", "A small brass key"}};
    
    clearScreen();
    std::cout << desc << "\n";
    
    actions();
}

void Game::elevatorRoom() {
    pos = 7;
    desc = "The Elevator Room";
    items = {};
    
    clearScreen();
    std::cout << desc << "\n";
    
    // Check if power is on
    if (elevStatus != "juiced") {
        std::cout << "The elevator is dark and lifeless. The power must be out.\n";
        std::cout << "You can't use the elevator without power.\n";
        std::cout << "Let's go back and find a way to turn on the power.\n\n";
        // Force player back to security room
        security();
        return;
    }
    
    std::cout << "The elevator lights are on! The power is working.\n";
    std::cout << "You can now access the upper floors.\n";
    std::cout << "**LEVEL 1 COMPLETE!**\n";
    
    actions();
}

void Game::officeSpace() {
    pos = 8;
    desc = "Office Space";
    items = {{"paper", "A small piece of paper with notes"}};
    
    clearScreen();
    std::cout << desc << "\n";
    
    actions();
}

void Game::stairwell() {
    pos = 9;
    desc = "The Stairwell";
    items = {};
    
    clearScreen();
    std::cout << desc << "\n";
    
    actions();
}

void Game::corridor() {
    pos = 10;
    desc = "The Corridor";
    items = {};
    
    clearScreen();
    std::cout << desc << "\n";
    
    actions();
}

void Game::officeNorth() {
    pos = 11;
    desc = "Office North";
    items = {};
    
    clearScreen();
    std::cout << desc << "\n";
    
    actions();
}

void Game::officeSouth() {
    pos = 12;
    desc = "Office South";
    items = {};
    
    clearScreen();
    std::cout << desc << "\n";
    
    actions();
}

void Game::storage() {
    pos = 13;
    desc = "Storage Room";
    items = {{"batteries", "A pack of batteries. These might be useful for the flashlight."}};
    
    clearScreen();
    std::cout << desc << "\n";
    
    actions();
}

void Game::control() {
    pos = 14;
    desc = "Control Room";
    items = {};
    
    clearScreen();
    std::cout << desc << "\n";
    std::cout << "As you enter, you see that this is a mechanical room\n";
    std::cout << "with two large electrical switches secured by large padlocks.\n";
    
    actions();
}

void Game::actions() {
    std::string move;
    std::cout << "ACTION:>";
    std::getline(std::cin, move);
    
    // Navigation based on current room
    if (move == "north") {
        switch (pos) {
            case 1: terminalA(); break;           // Zero Central -> Computer Room South
            case 2: std::cout << "You can't go north here.\n"; actions(); break;
            case 3: std::cout << "You can't go north here.\n"; actions(); break;
            case 4: terminalB(); break;           // Computer Room South -> Computer Room North
            case 6: 
                if (elevStatus == "juiced") {
                    elevatorRoom(); 
                } else {
                    std::cout << "The elevator is still powered off. I need to find a way to turn it on.\n"; 
                    actions(); 
                }
                break;        // Security -> Elevator (only if powered)
            case 7: control(); break;             // Elevator -> Control Room (if power is on)
            case 8: stairwell(); break;           // Office Space -> Stairwell
            case 10: officeNorth(); break;        // Corridor -> Executive Office North
            case 12: corridor(); break;           // Executive Office South -> Corridor
            default: std::cout << "You can't go north from here.\n"; actions(); break;
        }
    }
    else if (move == "south") {
        switch (pos) {
            case 1: std::cout << "You can't go south here.\n"; actions(); break;
            case 2: std::cout << "You can't go south here.\n"; actions(); break;
            case 4: zeroCentral(); break;        // Computer Room South -> Zero Central
            case 5: terminalA(); break;           // Computer Room North -> Computer Room South
            case 7: security(); break;            // Elevator -> Security
            case 9: officeSpace(); break;         // Stairwell -> Office Space
            case 10: officeSouth(); break;        // Corridor -> Executive Office South
            case 11: corridor(); break;           // Executive Office North -> Corridor
            default: std::cout << "You can't go south from here.\n"; actions(); break;
        }
    }
    else if (move == "east") {
        switch (pos) {
            case 1: zeroEast(); break;            // Zero Central -> Zero East
            case 2: zeroCentral(); break;         // Zero West -> Zero Central
            case 3: officeSpace(); break;         // Zero East -> Office Space
            case 4: corridor(); break;            // Computer Room South -> Corridor
            case 6: zeroWest(); break;            // Security -> Zero West
            case 9: std::cout << "You can't go east here.\n"; actions(); break;  // Stairwell east blocked
            case 10: stairwell(); break;          // Corridor -> Stairwell
            case 13: terminalA(); break;          // Storage -> Computer Room South
            case 14: terminalB(); break;          // Control Room -> Computer Room North
            default: std::cout << "You can't go east from here.\n"; actions(); break;
        }
    }
    else if (move == "west") {
        switch (pos) {
            case 1: zeroWest(); break;            // Zero Central -> Zero West
            case 2: security(); break;            // Zero West -> Security
            case 3: zeroCentral(); break;         // Zero East -> Zero Central
            case 4: storage(); break;             // Computer Room South -> Storage
            case 5: control(); break;             // Computer Room North -> Control Room
            case 8: zeroEast(); break;            // Office Space -> Zero East
            case 9: corridor(); break;            // Stairwell -> Corridor
            case 10: terminalA(); break;          // Corridor -> Computer Room South
            default: std::cout << "You can't go west from here.\n"; actions(); break;
        }
    }
    else if (move == "map") {
        player.map(pos);
        actions();
    }
    else if (move == "take") {
        player.take(items);
        actions();
    }
    else if (move == "inv") {
        player.inventory();
        actions();
    }
    else if (move == "help") {
        player.help();
        actions();
    }
    else if (move == "look") {
        player.look(pos, items, player.getLoot());
        actions();
    }
    else if (move == "save") {
        player.saveGame(pos);
        actions();
    }
    else if (move == "load") {
        player.loadGame(this);
        // Note: loadGame() calls the appropriate room function which starts actions() loop
        // so we don't call actions() again here
    }
    else if (move == "use term") {
        if (pos == 4 || pos == 5) {  // Terminal rooms
            Console console;
            console.startTerminal();
            actions();
        } else {
            std::cout << "There's no terminal here.\n";
            actions();
        }
    }
    else if (move == "unlock") {
        if (player.swStatus == "locked") {
            if (player.getLoot().find("key") != player.getLoot().end()) {
                std::cout << "You have unlocked the switches! Now, <energize> them!\n";
                player.swStatus = "unlocked";
                actions();
            } else {
                std::cout << "You need the key to unlock the switches.\n";
                actions();
            }
        }
    }
    else if (move == "energize") {
        if (player.swStatus == "unlocked") {
            elevStatus = "juiced";
            std::cout << "As you throw the switches on, you can feel the power flowing through the lines.\n";
            std::cout << "The emergency lighting is now on. Let's check the elevator!\n";
            actions();
        } else {
            std::cout << "These switches are locked. You must <unlock> them first.\n";
            actions();
        }
    }
    else if (move == "scan id") {
        std::cout << "You hold your badge up to the scanner...\n";
        actions();
    }
    else if (move == "quit") {
        GameOver go;
        std::string choice;
        std::cout << "Save before quitting? <y><n>:>";
        std::getline(std::cin, choice);
        
        if (choice == "y") {
            player.saveGame(pos);
            go.gameOverTxt();
        } else if (choice == "n") {
            std::cout << "Are you sure?:>";
            std::getline(std::cin, choice);
            if (choice == "y") {
                go.gameOverTxt();
            } else {
                actions();
            }
        } else {
            std::cout << "Invalid command.\n";
            actions();
        }
    }
    else if (move == "nav") {
        printNavInfo();
        actions();
    }
    else {
        std::cout << "Invalid command. Type <help> for available commands.\n";
        actions();
    }
}

void Game::printNavInfo() const {
    std::cout << "\n=== Navigation Information ===\n\n";
    
    switch (pos) {
        case 1:
            std::cout << "Zero Central:\n";
            std::cout << "  <north> - Computer Room South\n";
            std::cout << "  <east>  - Zero East\n";
            std::cout << "  <west>  - Zero West\n";
            break;
        case 2:
            std::cout << "Zero West:\n";
            std::cout << "  <east>  - Zero Central\n";
            std::cout << "  <west>  - Security Office\n";
            break;
        case 3:
            std::cout << "Zero East:\n";
            std::cout << "  <west>  - Zero Central\n";
            std::cout << "  <east>  - Office Space\n";
            break;
        case 4:
            std::cout << "Computer Room South:\n";
            std::cout << "  <north> - Computer Room North\n";
            std::cout << "  <west>  - Storage Room\n";
            std::cout << "  <south> - Zero Central\n";
            std::cout << "  <east>  - Corridor\n";
            break;
        case 5:
            std::cout << "Computer Room North:\n";
            std::cout << "  <north> - Computer Room South\n";
            std::cout << "  <west> - Control Room\n";
            std::cout << "  <use term> - Use the terminal here\n";
            break;
        case 6:
            std::cout << "Security Office:\n";
            std::cout << "  <east>  - Zero West\n";
            std::cout << "  <north> - Elevator\n";
            break;
        case 7:
            std::cout << "Elevator:\n";
            std::cout << "  <south> - Security Office\n";
            break;
        case 8:
            std::cout << "Office Space:\n";
            std::cout << "  <west>  - Zero East\n";
            std::cout << "  <north> - Stairwell\n";
            break;
        case 9:
            std::cout << "Stairwell:\n";
            std::cout << "  <south> - Office Space\n";
            std::cout << "  <west>  - Corridor\n";
            std::cout << "  <east>  - 8th Floor Stairwell\n";
            std::cout << "  <north> - 10th Floor Stairwell\n";
            break;
        case 10:
            std::cout << "Corridor:\n";
            std::cout << "  <east>  - Stairwell\n";
            std::cout << "  <north> - Executive Office North\n";
            std::cout << "  <south> - Executive Office South\n";
            std::cout << "  <west>  - Computer Room South\n";
            break;
        case 11:
            std::cout << "Executive Office North is Locked!\n";
            std::cout << "  <south> - Corridor\n";
            break;
        case 12:
            std::cout << "Executive Office South is Locked!\n";
            std::cout << "  <north> - Corridor\n";
            break;
        case 13:
            std::cout << "Storage Room:\n";
            std::cout << "  <east> - Computer Room South\n";
            break;
        case 14:
            std::cout << "Control Room:\n";
            std::cout << "  <east> - Computer Room North\n";
            break;
        case 15:
            std::cout << "8th Floor Stairwell is Locked!\n";
            break;
        case 16:
            std::cout << "10th Floor Stairwell is Locked!\n";
            break;
        case 17:
            std::cout << "Control Room:\n";
            std::cout << "  <west>  - Computer Room North\n";
            break;
        default:
            std::cout << "No navigation info available for this location.\n";
            break;
    }
    std::cout << "\n";
}
