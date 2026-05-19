#include "ConsoleUI.h"
#include "Game.h"
#include <iostream>

int main() {
    ConsoleUI ui;
    Game game(&ui);
    game.startGame();
    return 0;
}
