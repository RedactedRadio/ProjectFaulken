#include "Game.h"
#include <fstream>

void Game::playSound(const std::string& soundType) const {
    if (!gameState.enableSound) {
        return;
    }

    ui->playSound(soundType);
}

void Game::loadTitanPointe() {
    std::ifstream file("../src/titanpointe.txt");
    if (!file.is_open()) {
        ui->printLine("Could not load Titan Pointe display.");
        return;
    }

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    ui->setColor("\033[32m");
    ui->printLines(lines);
    ui->resetColor();
    file.close();

    if (ui->isQuitRequested()) {
        return;
    }

    ui->printLine("\nPress Enter to continue...");
    ui->readLine();
}
