#include "GameOver.h"
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <fstream>

GameOver::GameOver() {
}

void GameOver::clearScreen() const {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void GameOver::gameOverPrint(const std::string& text) {
    for (char c : text) {
        std::cout << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(9));
    }
}

void GameOver::gameOverTxt() {
    clearScreen();
    gameOverPrint(" ██████   █████  ███    ███ ███████      ██████  ██    ██ ███████ ██████\n");
    std::this_thread::sleep_for(std::chrono::milliseconds(150));
    gameOverPrint("██       ██   ██ ████  ████ ██          ██    ██ ██    ██ ██      ██   ██\n");
    std::this_thread::sleep_for(std::chrono::milliseconds(150));
    gameOverPrint("██   ███ ███████ ██ ████ ██ █████       ██    ██ ██    ██ █████   ██████\n");
    std::this_thread::sleep_for(std::chrono::milliseconds(150));
    gameOverPrint("██    ██ ██   ██ ██  ██  ██ ██          ██    ██  ██  ██  ██      ██   ██\n");
    std::this_thread::sleep_for(std::chrono::milliseconds(150));
    gameOverPrint(" ██████  ██   ██ ██      ██ ███████      ██████    ████   ███████ ██   ██\n");
    std::cout << "\nGoodbye!\n";
    exit(0);
}
