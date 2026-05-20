#include "ConsoleUI.h"
#include "Game.h"
#include <iostream>
#include <string>

#ifdef HAS_WINDOW_UI
#include "WindowUI.h"
#endif

#ifdef HAS_WINDOW_UI
int main(int argc, char* argv[]) {
    bool useWindow = false;
    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "--window") {
            useWindow = true;
            break;
        }
    }

    if (useWindow) {
        WindowUI ui;
        if (ui.isInitialized()) {
            Game game(&ui);
            game.startGame();
            return 0;
        }
        std::cerr << "Warning: Window UI initialization failed, falling back to console UI.\n";
    }

    ConsoleUI ui;
    Game game(&ui);
    game.startGame();
    return 0;
}
#else
int main() {
    ConsoleUI ui;
    Game game(&ui);
    game.startGame();
    return 0;
}
#endif
