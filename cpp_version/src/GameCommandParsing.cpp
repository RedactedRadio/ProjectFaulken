#include "Game.h"
#include <algorithm>
#include <cctype>

std::string Game::normalizeCommand(const std::string& cmd) const {
    std::string lowerCmd = cmd;
    std::transform(lowerCmd.begin(), lowerCmd.end(), lowerCmd.begin(), ::tolower);

    auto it = commandAliases.find(lowerCmd);
    if (it != commandAliases.end()) {
        return it->second;
    }
    return lowerCmd;
}

std::vector<std::string> Game::getCommandSuggestions(const std::string& partial) const {
    std::vector<std::string> suggestions;
    std::string lowerPartial = partial;
    std::transform(lowerPartial.begin(), lowerPartial.end(), lowerPartial.begin(), ::tolower);

    for (const auto& [alias, command] : commandAliases) {
        if (alias.find(lowerPartial) == 0) {
            suggestions.push_back(alias);
        }
    }

    std::vector<std::string> mainCommands = {
        "north", "south", "east", "west", "map", "take", "inv", "help",
        "look", "save", "load", "use term", "unlock", "energize",
        "scan id", "quit", "nav"
    };

    for (const std::string& cmd : mainCommands) {
        if (cmd.find(lowerPartial) == 0) {
            suggestions.push_back(cmd);
        }
    }

    std::sort(suggestions.begin(), suggestions.end());
    suggestions.erase(std::unique(suggestions.begin(), suggestions.end()), suggestions.end());

    return suggestions;
}

void Game::handleInvalidCommand(const std::string& cmd) {
    ui->printLine("Unknown command: '" + cmd + "'");
    playSound("error");

    auto suggestions = getCommandSuggestions(cmd);
    if (!suggestions.empty()) {
        std::string suggestionText = "Did you mean: ";
        for (size_t i = 0; i < suggestions.size() && i < 3; ++i) {
            suggestionText += suggestions[i];
            if (i < suggestions.size() - 1 && i < 2) {
                suggestionText += ", ";
            }
        }
        if (suggestions.size() > 3) {
            suggestionText += "...";
        }
        suggestionText += "?";
        ui->printLine(suggestionText);
    }

    ui->printLine("Type 'help' for available commands.");
}
