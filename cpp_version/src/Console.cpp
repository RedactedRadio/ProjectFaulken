#include "Console.h"
#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>

Console::Console() 
    : CRED("\u001b[31m"), CEND("\033[0m") {
}

void Console::clearScreen() const {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void Console::startTerminal() {
    clearScreen();
    
    std::cout << CRED << " ===================================================================" << CEND << "\n";
    std::cout << CRED << " CENTRAL INTELLIGENCE MAINFRAME TERMINAL.      AUTHORIZED USERS ONLY." << CEND << "\n";
    std::cout << CRED << " ===================================================================" << CEND << "\n";
    std::cout << "\n\n\n";
    std::cout << CRED << "Enter your authentication credentials.\n" << CEND;
    
    funcCheckCred();
}

void Console::funcCheckCred() {
    std::cout << CRED << "Enter User ID: " << CEND;
    std::getline(std::cin, varUser);
    
    std::cout << CRED << "Scanning SuperCrypt ID Badge.";
    std::cout.flush();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << ".";
    std::cout.flush();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << ".\n" << CEND;
    std::cout.flush();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    
    if (varUser == "Faulken, S.") {
        std::cout << CRED << "User Faulken, S. - ACCESS GRANTED" << CEND << "\n";
        funcConsole();
    } else {
        std::cout << CRED << "ACCESS DENIED" << CEND << "\n";
        funcCheckCred();
    }
}

void Console::funcConsole() {
    std::cout << "?: ";
    std::getline(std::cin, varCmd);
    
    if (varCmd == "--help") {
        funcCmdHelp();
    } else if (varCmd == "stop") {
        funcCmdStop();
    } else if (varCmd == "ls") {
        funcCmdLs();
    } else if (varCmd == "open") {
        funcCmdOpen();
    } else if (varCmd == "crypto") {
        funcOpenCrypto();
    } else {
        std::cout << CRED << "Invalid Command. Type --help for command list." << CEND << "\n";
        funcConsole();
    }
}

void Console::funcCmdHelp() {
    std::cout << CRED << "\n\nCommand List\n" << CEND;
    std::cout << CRED << "--" << CEND << "\n";
    std::cout << CRED << "ls     - directory listing" << CEND << "\n";
    std::cout << CRED << "open   - opens file" << CEND << "\n";
    std::cout << CRED << "crypto - opens decrytion package" << CEND << "\n";
    std::cout << CRED << "stop   - Exit Terminal.\n" << CEND;
    funcConsole();
}

void Console::funcCmdLs() {
    std::cout << CRED << "\nContents of:\n             /user...\n" << CEND;
    std::cout << CRED << "readme.txt   msg1.###    img1.###" << CEND << "\n";
    std::cout << CRED << "msg2.###     pwdList.### codes.###" << CEND << "\n";
    std::cout << CRED << "9thFloor_Map.###" << CEND << "\n";
    funcConsole();
}

void Console::funcCmdOpen() {
    std::cout << CRED << "Enter the filename to open:" << CEND;
    std::getline(std::cin, filename);
    
    std::cout << CRED << "\nThis file is encrypted with 1024 bit SuperCrypt technology... \n";
    std::cout << "Contents are not able to be displayed.\n" << CEND;
    funcConsole();
}

void Console::funcOpenCrypto() {
    std::cout << CRED << "Enter the code to decrypt:> " << CEND;
    std::getline(std::cin, decryptCmd);
    
    if (decryptCmd == "EPEbddftt") {
        clearScreen();
        std::cout << CRED << "\nLoading NSA Decryption Engine..." << CEND << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::cout << CRED << "\nGenerating Hash Algorithms..." << CEND << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::cout << CRED << "\nDecryption Complete.\nDECRYPTED CODE:" << CEND << "      DODaccess\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        funcConsole();
    } else {
        std::cout << CRED << "Encryption algorithm not found. Unable to decrypt." << CEND << "\n";
        funcOpenCrypto();
    }
}

void Console::funcCmdStop() {
    // Return to game
}
