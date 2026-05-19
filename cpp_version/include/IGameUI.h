#ifndef I_GAME_UI_H
#define I_GAME_UI_H

#include <string>

class IGameUI {
public:
    virtual ~IGameUI() = default;

    virtual void clearScreen() = 0;
    virtual void print(const std::string& text) = 0;
    virtual void printLine(const std::string& text) = 0;
    virtual std::string readLine() = 0;
    virtual void sleepMs(int ms) = 0;
    virtual void setColor(const std::string& colorCode) = 0;
    virtual void resetColor() = 0;
    virtual void showImage(const std::string& imageId) = 0;
};

#endif // I_GAME_UI_H
