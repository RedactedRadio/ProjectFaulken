#ifndef CONSOLE_UI_H
#define CONSOLE_UI_H

#include "IGameUI.h"
#include <string>

class ConsoleUI : public IGameUI {
public:
    ConsoleUI();
    void clearScreen() override;
    void print(const std::string& text) override;
    void printLine(const std::string& text) override;
    std::string readLine() override;
    void sleepMs(int ms) override;
    void setColor(const std::string& colorCode) override;
    void resetColor() override;
    void showImage(const std::string& imageId) override;

private:
    void systemClear() const;
};

#endif // CONSOLE_UI_H
