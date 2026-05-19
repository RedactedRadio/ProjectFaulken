#include "ConsoleUI.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>

ConsoleUI::ConsoleUI() {
}

void ConsoleUI::systemClear() const {
    #ifdef _WIN32
        std::system("cls");
    #else
        std::system("clear");
    #endif
}

void ConsoleUI::clearScreen() {
    systemClear();
}

void ConsoleUI::print(const std::string& text) {
    std::cout << text;
}

void ConsoleUI::printLine(const std::string& text) {
    std::cout << text << "\n";
}

std::string ConsoleUI::readLine() {
    std::string input;
    std::getline(std::cin, input);
    return input;
}

void ConsoleUI::sleepMs(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void ConsoleUI::setColor(const std::string& colorCode) {
    std::cout << colorCode;
}

void ConsoleUI::resetColor() {
    std::cout << "\033[0m";
}

void ConsoleUI::showImage(const std::string& imageId) {
    std::cout << "[UI] showImage('" << imageId << "')\n";
}
