#include "Player.h"
#include "Game.h"
#include "IGameUI.h"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>
#include <thread>

namespace fs = std::filesystem;

void Player::newGame() {
    printSlowText("In a dimly lit, cold room you regain consciousness...\n", 0.05);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    printSlowText("The back of your head is searing with pain.\n", 0.05);
    printSlowText("You can't seem to remember your name.\n\n", 0.05);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    printSlowText("You look at the ID Badge next to you. ", 0.05);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    printSlowText("ASSET: FAULKEN, S. \n", 0.05);
    std::this_thread::sleep_for(std::chrono::milliseconds(250));
    printSlowText("As you stare at the fuzzy picture, you realize two things.\n", 0.05);
    std::this_thread::sleep_for(std::chrono::milliseconds(250));
    printSlowText("You are not Faulken...", 0.05);
    std::this_thread::sleep_for(std::chrono::milliseconds(250));
    printSlowText("and you have no idea why you are here.\n", 0.05);
    std::this_thread::sleep_for(std::chrono::seconds(1));

    if (ui) {
        ui->printLine("Enter your name...");
        name = ui->readLine();
    }

    try {
        saveData = name + " lvl=1";
        std::string filename = "cpp_version/saves/" + name + ".data";

        fs::create_directories("cpp_version/saves");

        std::ofstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Unable to create save file");
        }
        file << saveData;
        file.close();
    } catch (const std::exception& e) {
        if (ui) {
            ui->printLine("Unable to create new gamesave file: " + std::string(e.what()));
        }
    }
}

void Player::saveGame(int position) {
    if (ui) {
        ui->printLine("Enter save file name...");
        name = ui->readLine();
        ui->printLine(std::to_string(position));
    }

    try {
        std::string filename = "cpp_version/saves/" + name + ".data";

        fs::create_directories("cpp_version/saves");

        nlohmann::json saveJson;
        saveJson["name"] = name;
        saveJson["level"] = position;
        saveJson["loot"] = loot;

        std::ofstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open file for writing");
        }

        file << saveJson.dump(4);
        file.close();

        if (ui) {
            ui->printLine("Game Save Successful.");
            ui->printLine("Saved: " + saveJson.dump(4));
        }
    } catch (const std::exception& e) {
        if (ui) {
            ui->printLine("Could not write file: " + std::string(e.what()));
        }
    }
}

void Player::loadGame(Game* game) {
    if (ui) {
        ui->printLine("Enter file name to load...");
        name = ui->readLine();
    }

    try {
        std::string filename = "cpp_version/saves/" + name + ".data";
        std::ifstream file(filename);

        if (!file.is_open()) {
            throw std::runtime_error("Could not open save file");
        }

        nlohmann::json saveJson;
        file >> saveJson;
        file.close();

        if (ui) {
            ui->printLine("Loading Game...\n");
        }

        if (saveJson.contains("name")) {
            name = saveJson["name"];
        }

        if (saveJson.contains("level")) {
            int level = saveJson["level"];
            if (level >= 1 && level <= 14) {
                game->enterRoom(static_cast<Game::Room>(level));
            } else {
                game->zeroCentral();
            }
        } else {
            game->zeroCentral();
        }

        if (saveJson.contains("loot")) {
            loot = saveJson["loot"].get<std::map<std::string, std::string>>();
        }

        if (ui) {
            ui->printLine("Loaded save data:");
            ui->printLine(saveJson.dump(4));
        }
    } catch (const std::exception& e) {
        if (ui) {
            ui->printLine("Could not read file: " + std::string(e.what()));
        }
    }
}
