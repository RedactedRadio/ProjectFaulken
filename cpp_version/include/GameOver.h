#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <string>

class GameOver {
public:
    GameOver();
    
    void gameOverTxt();
    
private:
    void gameOverPrint(const std::string& text);
    void clearScreen() const;
};

#endif
