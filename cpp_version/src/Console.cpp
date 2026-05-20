#include "Console.h"
#include "IGameUI.h"

Console::Console(IGameUI* ui)
    : CRED("\u001b[31m")
    , CEND("\033[0m")
    , ui(ui)
    , active(false) {
}

void Console::clearScreen() const {
    if (ui) {
        ui->clearScreen();
    }
}

void Console::printTerminal(const std::string& text) const {
    if (!ui) {
        return;
    }

    ui->setColor(CRED);
    ui->print(text);
    ui->resetColor();
}

void Console::printTerminalLine(const std::string& text) const {
    if (!ui) {
        return;
    }

    ui->setColor(CRED);
    ui->printLine(text);
    ui->resetColor();
}

std::string Console::readTerminalLine() {
    if (!ui) {
        return "";
    }
    return ui->readLine();
}

void Console::startTerminal() {
    active = true;
    clearScreen();

    printTerminalLine(" ===================================================================");
    printTerminalLine(" CENTRAL INTELLIGENCE MAINFRAME TERMINAL.      AUTHORIZED USERS ONLY.");
    printTerminalLine(" ===================================================================");
    ui->printLine("");
    ui->printLine("");
    ui->printLine("");
    printTerminalLine("Enter your authentication credentials.");

    funcCheckCred();
}

void Console::funcCheckCred() {
    while (active) {
        printTerminal("Enter User ID: ");
        varUser = readTerminalLine();

        printTerminal("Scanning SuperCrypt ID Badge.");
        ui->sleepMs(500);
        printTerminal(".");
        ui->sleepMs(500);
        printTerminalLine(".");
        ui->sleepMs(500);

        if (varUser == "Faulken, S.") {
            printTerminalLine("User Faulken, S. - ACCESS GRANTED");
            funcConsole();
            return;
        }

        printTerminalLine("ACCESS DENIED");
    }
}

void Console::funcConsole() {
    while (active) {
        ui->print("?: ");
        varCmd = readTerminalLine();

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
            printTerminalLine("Invalid Command. Type --help for command list.");
        }
    }
}

void Console::funcCmdHelp() {
    printTerminalLine("");
    printTerminalLine("");
    printTerminalLine("Command List");
    printTerminalLine("--");
    printTerminalLine("ls     - directory listing");
    printTerminalLine("open   - opens file");
    printTerminalLine("crypto - opens decrytion package");
    printTerminalLine("stop   - Exit Terminal.");
}

void Console::funcCmdLs() {
    printTerminalLine("");
    printTerminalLine("Contents of:");
    printTerminalLine("             /user...");
    printTerminalLine("readme.txt   msg1.###    img1.###");
    printTerminalLine("msg2.###     pwdList.### codes.###");
    printTerminalLine("9thFloor_Map.###");
}

void Console::funcCmdOpen() {
    printTerminal("Enter the filename to open: ");
    filename = readTerminalLine();

    printTerminalLine("");
    printTerminalLine("This file is encrypted with 1024 bit SuperCrypt technology...");
    printTerminalLine("Contents are not able to be displayed.");
}

void Console::funcOpenCrypto() {
    while (active) {
        printTerminal("Enter the code to decrypt:> ");
        decryptCmd = readTerminalLine();

        if (decryptCmd == "EPEbddftt") {
            clearScreen();
            printTerminalLine("Loading NSA Decryption Engine...");
            ui->sleepMs(500);
            printTerminalLine("");
            printTerminalLine("Generating Hash Algorithms...");
            ui->sleepMs(500);
            printTerminal("Decryption Complete.\nDECRYPTED CODE:");
            ui->printLine("      DODaccess");
            ui->sleepMs(500);
            return;
        }

        printTerminalLine("Encryption algorithm not found. Unable to decrypt.");
    }
}

void Console::funcCmdStop() {
    printTerminalLine("Closing terminal session.");
    active = false;
}
