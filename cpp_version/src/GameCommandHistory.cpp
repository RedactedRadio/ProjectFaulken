#include "Game.h"

void Game::addToCommandHistory(const std::string& cmd) {
    if (!cmd.empty()) {
        gameState.commandHistory.push_back(cmd);
        if (gameState.commandHistory.size() > 50) {
            gameState.commandHistory.pop_front();
        }
        gameState.historyIndex = gameState.commandHistory.size();
    }
}

std::string Game::getPreviousCommand() {
    if (gameState.historyIndex > 0) {
        gameState.historyIndex--;
        return gameState.commandHistory[gameState.historyIndex];
    }
    return "";
}

std::string Game::getNextCommand() {
    if (gameState.historyIndex < gameState.commandHistory.size() - 1) {
        gameState.historyIndex++;
        return gameState.commandHistory[gameState.historyIndex];
    }
    return "";
}
