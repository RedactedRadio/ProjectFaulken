#ifndef CONSOLE_H
#define CONSOLE_H

#include <string>

class Game;  // Forward declaration

class Console {
public:
    Console();
    
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
    
    void funcCmdStop();
    void funcCmdHelp();
    void funcCmdLs();
    void funcCmdOpen();
    void funcOpenCrypto();
    void clearScreen() const;
};

#endif
