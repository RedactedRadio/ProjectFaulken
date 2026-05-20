#include "Player.h"
#include "IGameUI.h"
#include <chrono>
#include <iostream>
#include <thread>

Player::Player()
    : ui(nullptr) {
}

Player::Player(IGameUI* ui)
    : ui(ui) {
}

void Player::printSlowText(const std::string& text, double delayMs) const {
    for (char c : text) {
        if (ui) {
            ui->print(std::string(1, c));
        } else {
            std::cout << c;
            std::cout.flush();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(delayMs)));
    }
}
