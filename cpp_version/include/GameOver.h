#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <string>

class IGameUI;

class GameOver {
public:
    GameOver(IGameUI* ui);
    
    void gameOverTxt();
    
private:
    IGameUI* ui;
    void gameOverPrint(const std::string& text);
    void clearScreen() const;
};

#endif
