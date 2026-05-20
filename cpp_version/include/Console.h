#ifndef CONSOLE_H
#define CONSOLE_H

#include <string>

class Game;  // Forward declaration
class IGameUI;

class Console {
public:
    explicit Console(IGameUI* ui);
    
    void startTerminal();
    void funcConsole();
    void funcCheckCred();
    
private:
    std::string CRED;
    std::string CEND;
    std::string varUser;
    std::string varCmd;
    std::string decryptCmd;
    std::string filename;
    IGameUI* ui;
    bool active;
    
    void funcCmdStop();
    void funcCmdHelp();
    void funcCmdLs();
    void funcCmdOpen();
    void funcOpenCrypto();
    void clearScreen() const;
    void printTerminal(const std::string& text) const;
    void printTerminalLine(const std::string& text) const;
    std::string readTerminalLine();
};

#endif
