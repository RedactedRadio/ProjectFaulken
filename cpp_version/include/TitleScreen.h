#ifndef TITLESCREEN_H
#define TITLESCREEN_H

#include <string>

class IGameUI;

class TitleScreen {
public:
    TitleScreen(IGameUI* ui);
    
    // Returns 1 for new game, 2 for load game, 0 for exit
    int display();
    
private:
    IGameUI* ui;
    void clearScreen() const;
    void slowPrint(const std::string& text, double delayMs = 0.009);
    void typingPrint(const std::string& text, double delayMs = 0.015);
};

#endif
