#include "GameOver.h"
#include "IGameUI.h"
#include <chrono>
#include <thread>

GameOver::GameOver(IGameUI* ui)
    : ui(ui) {
}

void GameOver::clearScreen() const {
    if (ui) ui->clearScreen();
}

void GameOver::gameOverPrint(const std::string& text) {
    for (char c : text) {
        if (ui) ui->print(std::string(1, c));
        std::this_thread::sleep_for(std::chrono::milliseconds(9));
    }
}

void GameOver::gameOverTxt() {
    clearScreen();
    gameOverPrint(" ██████   █████  ███    ███ ███████      ██████  ██    ██ ███████ ██████\n");
    //std::this_thread::sleep_for(std::chrono::milliseconds(50));
    gameOverPrint("██       ██   ██ ████  ████ ██          ██    ██ ██    ██ ██      ██   ██\n");
    //std::this_thread::sleep_for(std::chrono::milliseconds(50));
    gameOverPrint("██   ███ ███████ ██ ████ ██ █████       ██    ██ ██    ██ █████   ██████\n");
    //std::this_thread::sleep_for(std::chrono::milliseconds(50));
    gameOverPrint("██    ██ ██   ██ ██  ██  ██ ██          ██    ██  ██  ██  ██      ██   ██\n");
    //std::this_thread::sleep_for(std::chrono::milliseconds(50));
    gameOverPrint(" ██████  ██   ██ ██      ██ ███████      ██████    ████   ███████ ██   ██\n");
    if (ui) ui->printLine("\nGoodbye!");
    exit(0);
}
