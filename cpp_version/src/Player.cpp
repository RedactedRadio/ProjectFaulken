#include "Player.h"
#include "Game.h"
#include "MapBase.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <filesystem>
#include <nlohmann/json.hpp>

namespace fs = std::filesystem;

Player::Player() {
}

void Player::printSlowText(const std::string& text, double delayMs) const {
    for (char c : text) {
        std::cout << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(delayMs)));
    }
}

void Player::inventory() const {
    std::cout << "\nINVENTORY\n";
    std::cout << "===========================================================\n\n";
    for (const auto& [key, value] : loot) {
        if (key == "paper") {
            std::cout << key << "     -     An encrypted code is written on this small piece of paper.\n It reads... EPEbddftt.\n";
        } else {
            std::cout << key << "     -     " << value << "\n";
        }
    }
}

void Player::take(const std::map<std::string, std::string>& items) {
    if (items.empty()) {
        std::cout << "\nNothing to take from here. Let's keep moving.\n";
        return;
    }
    
    for (const auto& [key, value] : items) {
        if (loot.find(key) != loot.end()) {
            std::cout << "\nYou have the " << key << " already\n";
        } else {
            std::cout << "\nYou found the " << key << "!\n\n";
            loot[key] = value;
        }
    }
}

void Player::map(int pos) const {
    switch (pos) {
        case 1: MapBase::mapZc(); break;
        case 2: MapBase::mapZw(); break;
        case 3: MapBase::mapZe(); break;
        case 4: MapBase::mapCompS(); break;
        case 5: MapBase::mapCompN(); break;
        case 6: MapBase::mapSec(); break;
        case 8: MapBase::mapOff(); break;
        case 9: MapBase::mapStair(); break;
        case 10: MapBase::mapCor(); break;
        case 13: MapBase::mapSto(); break;
        case 14: MapBase::mapCtrl(); break;
        default:
            std::cout << "The <map> is unavailable.\n";
    }
}

void Player::help() const {
    std::cout << "Available action commands:\n";
    std::cout << "============================================================================================\n";
    std::cout << "<use term>   - This command will allows you to use the Terminal, if there is one in the room.\n";
    std::cout << "<look>       - This command looks around your current location,\n";
    std::cout << "               and gives you a report of your surroundings.\n";
    std::cout << "<scan_ID>    - Use this command to scan your ID Badge.\n";
    std::cout << "<use term>   - This command allows you to sit at the terminal and interact with it.\n";
    std::cout << "<take>       - This command allows you to add found items to your inventory.\n";
    std::cout << "<help>       - Shows this screen\n";
    std::cout << "<nav>        - Player Navigation based on current positioning.\n";
    std::cout << "<load>       - Load a saved game.\n";
    std::cout << "<save>       - Save Gameplay.\n";
    std::cout << "<map>        - Display the map\n";
    std::cout << "<quit>       - End game and exit.\n";
}

void Player::look(int pos, const std::map<std::string, std::string>& items, const std::map<std::string, std::string>& playerLoot) const {
    std::cout << pos << "\n";
    
    // Check if all items in the room are already taken
    bool allItemsTaken = true;
    for (const auto& [key, value] : items) {
        if (playerLoot.find(key) == playerLoot.end()) {
            allItemsTaken = false;
            break;
        }
    }
    
    if (allItemsTaken && !items.empty()) {
        std::cout << "Nothing to see here. Let's keep moving.\n";
        return;
    }
    
    switch (pos) {
        case 1:
            std::cout << "You <look> down at the ID BADGE. You should <take> it!\n";
            std::cout << "Hey! We really need to find the elevator.\n";
            return;
        case 2:
            std::cout << "We are getting closer to the elevator. Let's keep going <west>.\n";
            return;
        case 3:
            std::cout << "You see a FLASHLIGHT on the floor. You should <take> it!\n";
            return;
        case 4:
            std::cout << "There is a computer console in the room just <north> of here.\n";
            return;
        case 5:
            std::cout << "There's a computer terminal over there. Let's <use term>. \nMaybe we can decode the code on the[paper].\n";
            return;
        case 6:
            std::cout << "This must be the security center. You see a KEY! \n This must fit something important. <take> it!\n";
            std::cout << "The elevator is on the <north> wall of the security center.\n";
            return;
        case 8:
            std::cout << "As you enter this dark liminal space, you feel a sense of unease.\n";
            std::cout << "This room is filled with cubicles.\n";
            std::cout << "A small piece of PAPER catches your eye. Better <take> it along.\n";
            return;
        case 9:
            std::cout << "Ermmmm... The eighth and tenth floor access doors are locked!\n";
            return;
        case 11:
            std::cout << "Executive Suite North is Locked!\n";
            return;
        case 12:
            std::cout << "Executive Suite South is Locked!\n";
            return;
        case 13:
            std::cout << "You see a pack of BATTERIES and a can of Olliebeans!\n";
            std::cout << "You can <take> the batteries, but the Olliebeans will always remain.\n";
            return;
        case 14:
            std::cout << "You enter the control room and look up at the tall ceilings.\nThey must be 15-20 feet tall!";
            std::cout << "Among the heavy cables running floor to ceiling, you notice a giant switchgear \nwith a lock securing the the actuator.\n";
            std::cout << "If you had the <key> you could <unlock> the switchgear.\n";
            return;
        default:
            if (items.empty()) {
                std::cout << "Nothing to see here. Let's keep moving.\n";
            } else {
                std::cout << "Oopsie! Well, this is really embarassing...\n";
                std::cout << pos << "\n";
            }
            return;
    }
}

void Player::newGame() {
    // Display opening storyline from levelOne.py
    printSlowText("In a dimly lit, cold room you regain consciousness...\n", 0.05);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    printSlowText("The back of your head is searing with pain.\n", 0.05);
    printSlowText("You can't seem to remember your name.\n\n", 0.05);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    printSlowText("You look at the ID Badge next to you. ", 0.05);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    printSlowText("ASSET: FAULKEN, S. \n", 0.05);
    std::this_thread::sleep_for(std::chrono::milliseconds(250));
    printSlowText("As you stare at the fuzzy picture, you realize two things.\n", 0.05);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    printSlowText("You are not Faulken...", 0.05);
    std::this_thread::sleep_for(std::chrono::milliseconds(250));
    printSlowText("and you have no idea why you are here.\n", 0.05);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    
    
    std::cout << "Enter your name...\n";
    std::getline(std::cin, name);
    
    try {
        saveData = name + " lvl=1";
        std::string filename = "cpp_version/saves/" + name + ".data";
        
        // Create saves directory if it doesn't exist
        fs::create_directories("cpp_version/saves");
        
        std::ofstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Unable to create save file");
        }
        file << saveData;
        file.close();
    } catch (const std::exception& e) {
        std::cout << "Unable to create new gamesave file: " << e.what() << "\n";
    }
}

void Player::saveGame(int position) {
    std::cout << "Enter save file name...\n";
    std::getline(std::cin, name);
    std::cout << position << "\n\n";
    
    try {
        std::string filename = "cpp_version/saves/" + name + ".data";
        
        // Create saves directory if it doesn't exist
        fs::create_directories("cpp_version/saves");
        
        // Create JSON save data
        nlohmann::json saveJson;
        saveJson["name"] = name;
        saveJson["level"] = position;
        saveJson["loot"] = loot;
        
        std::ofstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open file for writing");
        }
        
        file << saveJson.dump(4); // Pretty print with 4-space indentation
        file.close();
        
        std::cout << "Game Save Successful.\n";
        std::cout << "Saved: " << saveJson.dump(4) << "\n";
    } catch (const std::exception& e) {
        std::cout << "Could not write file: " << e.what() << "\n";
    }
}

void Player::loadGame(Game* game) {
    std::cout << "Enter file name to load...\n";
    std::getline(std::cin, name);
    
    try {
        std::string filename = "cpp_version/saves/" + name + ".data";
        std::ifstream file(filename);
        
        if (!file.is_open()) {
            throw std::runtime_error("Could not open save file");
        }
        
        nlohmann::json saveJson;
        file >> saveJson;
        file.close();
        
        std::cout << "Loading Game...\n\n";
        
        // Restore player name
        if (saveJson.contains("name")) {
            name = saveJson["name"];
        }
        
        // Restore room level
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
        
        // Restore inventory
        if (saveJson.contains("loot")) {
            loot = saveJson["loot"].get<std::map<std::string, std::string>>();
        }
        
        std::cout << "Loaded save data:\n" << saveJson.dump(4) << "\n";
        
    } catch (const std::exception& e) {
        std::cout << "Could not read file: " << e.what() << "\n";
    }
}
