#include "Game.h"
#include "TitleScreen.h"

Game::Game(IGameUI* ui)
    : gameState{}
    , ui(ui)
    , player(ui) {
    initRooms();
}

void Game::startGame() {
    TitleScreen titleScreen(ui);
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

void Game::actions() {
    while (!gameState.shouldExit) {
        std::string move = ui->readLine();

        if (move.empty()) {
            continue;
        }

        addToCommandHistory(move);
        handleInput(normalizeCommand(move));
    }
}
