#include "TitleScreen.h"
#include "IGameUI.h"
#include <chrono>
#include <thread>

TitleScreen::TitleScreen(IGameUI* ui)
    : ui(ui) {
}

void TitleScreen::clearScreen() const {
    if (ui) ui->clearScreen();
}

void TitleScreen::slowPrint(const std::string& text, double delayMs) {
    for (char c : text) {
        if (ui) ui->print(std::string(1, c));
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(delayMs)));
    }
}

void TitleScreen::typingPrint(const std::string& text, double delayMs) {
    for (char c : text) {
        if (ui) ui->print(std::string(1, c));
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(delayMs)));
    }
}

int TitleScreen::display() {
    clearScreen();
    
    slowPrint("8888888888                 888 888                        d8b\n", 0.009);
    slowPrint("888                        888 888                        88P\n", 0.009);
    slowPrint("888                        888 888                        8P\n", 0.009);
    slowPrint("8888888   8888b.  888  888 888 888  888  .d88b.  88888b.  \"   .d8888b\n", 0.009);
    slowPrint("888          \"88b 888  888 888 888 .88P d8P  Y8b 888 \"88b     88K\n", 0.009);
    slowPrint("888      .d888888 888  888 888 888888K  88888888 888  888     \"Y8888b.\n", 0.009);
    slowPrint("888      888  888 Y88b 888 888 888 \"88b Y8b.     888  888          X88\n", 0.009);
    slowPrint("888      \"Y888888  \"Y88888 888 888  888  \"Y8888  888  888      88888P`\n", 0.009);
    
    slowPrint("\n\n88888888888 8888888888 8888888b.  888b     d888 8888888 888b    888        d8888 888\n", 0.009);
    slowPrint("    888     888        888   Y88b 8888b   d8888   888   8888b   888       d88888 888\n", 0.009);
    slowPrint("    888     888        888    888 88888b.d88888   888   88888b  888      d88P888 888\n", 0.009);
    slowPrint("    888     8888888    888   d88P 888Y88888P888   888   888Y88b 888     d88P 888 888\n", 0.009);
    slowPrint("    888     888        8888888P\"  888 Y888P 888   888   888 Y88b888    d88P  888 888\n", 0.009);
    slowPrint("    888     888        888 T88b   888  Y8P  888   888   888  Y88888   d88P   888 888\n", 0.009);
    slowPrint("    888     888        888  T88b  888   \"   888   888   888   Y8888  d8888888888 888\n", 0.009);
    slowPrint("    888     8888888888 888   T88b 888       888 8888888 888    Y888 d88P     888 88888888\n\n\n", 0.009);
    
    std::this_thread::sleep_for(std::chrono::seconds(1));
    typingPrint("Shall we play a game?", 0.015);
    
    if (ui) ui->print("\n\n\nEnter <1> for a new game. Enter <2> to resume progress. Enter <X> to exit: ");
    std::string choice;
    if (ui) choice = ui->readLine();
    
    if (choice == "1") {
        return 1;
    } else if (choice == "2") {
        return 2;
    } else if (choice == "X" || choice == "x") {
        clearScreen();
        return 0;
    } else {
        if (ui) ui->printLine("Invalid choice. Please try again.");
        return display();
    }
}
