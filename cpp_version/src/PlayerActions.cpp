#include "Player.h"
#include "IGameUI.h"
#include "MapBase.h"

void Player::inventory() const {
    if (ui) {
        ui->printLine("\nINVENTORY");
        ui->printLine("===========================================================\n");
        for (const auto& [key, value] : loot) {
            if (key == "paper") {
                ui->printLine(key + " - An encrypted code, EPEbddftt, is written on this paper.");
                
            } else {
                ui->printLine(key + " - " + value);
            }
        }
    }
}

void Player::take(const std::map<std::string, std::string>& items) {
    if (items.empty()) {
        if (ui) {
            ui->setColor("\033[90m");
            ui->printLine("\nNothing more to take from here. Let's keep moving.");
            ui->resetColor();
        }
        return;
    }

    for (const auto& [key, value] : items) {
        if (loot.find(key) != loot.end()) {
            if (ui) {
                ui->setColor("\033[90m");
                ui->printLine("\nYou have the " + key + " already");
                ui->resetColor();
            }
        } else {
            if (ui) {
                ui->setColor("\033[33m");
                ui->printLine("\nYou found the " + key + "! \nThis might be useful later. ");
                ui->resetColor();
            }
            loot[key] = value;
        }
    }
}

void Player::map(int pos, IGameUI* ui) const {
    switch (pos) {
        case 1: MapBase::mapZc(ui); break;
        case 2: MapBase::mapZw(ui); break;
        case 3: MapBase::mapZe(ui); break;
        case 4: MapBase::mapCompS(ui); break;
        case 5: MapBase::mapCompN(ui); break;
        case 6: MapBase::mapSec(ui); break;
        case 8: MapBase::mapOff(ui); break;
        case 9: MapBase::mapStair(ui); break;
        case 10: MapBase::mapCor(ui); break;
        case 13: MapBase::mapSto(ui); break;
        case 14: MapBase::mapCtrl(ui); break;
        default:
            if (ui) {
                ui->printLine("The <map> is unavailable.");
            }
    }
}

void Player::help() const {
    if (!ui) {
        return;
    }

    ui->printLine("Available action commands:");
    ui->printLine("============================================================================================");
    ui->printLine("<use term>   - This command will allows you to use the Terminal, if there is one in the room.");
    ui->printLine("<look>       - This command looks around your current location,");
    ui->printLine("               and gives you a report of your surroundings.");
    ui->printLine("<scan ID>    - Use this command to scan your ID Badge.");
    ui->printLine("<use term>   - This command allows you to sit at the terminal and interact with it.");
    ui->printLine("<take>       - This command allows you to add found items to your inventory.");
    ui->printLine("<help>       - Shows this screen");
    ui->printLine("<nav>        - Player Navigation based on current positioning.");
    ui->printLine("<load>       - Load a saved game.");
    ui->printLine("<save>       - Save Gameplay.");
    ui->printLine("<map>        - Display the map");
    ui->printLine("<quit>       - End game and exit.");
}

void Player::look(
    int pos,
    const std::map<std::string, std::string>& items,
    const std::map<std::string, std::string>& playerLoot
) const {
    if (playerLoot.find("flashlight") == playerLoot.end()) {
        if (ui) {
            ui->setColor("\033[90m");
            ui->printLine("Its too dark to <look> for anything! \n We need the FLASHLIGHT to see.");
            ui->resetColor();
        }
        return;
    }

    bool allItemsTaken = true;
    for (const auto& [key, value] : items) {
        if (playerLoot.find(key) == playerLoot.end()) {
            allItemsTaken = false;
            break;
        }
    }

    if (allItemsTaken && !items.empty()) {
        if (ui) {
            ui->setColor("\033[90m");
            ui->printLine("Nothing more to look at. Let's keep moving.");
            ui->resetColor();
        }
        return;
    }

    switch (pos) {
        case 1:
            if (ui) ui->printLine("You <look> down at the ID BADGE. \nYou should <take> it!");
            if (ui) ui->printLine("Hey! We really need to find the elevator.");
            return;
        case 2:
            if (ui) ui->printLine("We are getting closer to the elevator. Let's keep going <west>.");
            return;
        case 3:
            if (ui) ui->printLine("You see a FLASHLIGHT on the floor. You should <take> it!");
            return;
        case 4:
            if (ui) ui->printLine("There is a computer console in the room just <north> of here.");
            return;
        case 5:
            if (ui) ui->printLine("There's a computer terminal over there. Let's <use term>.");
            if (ui) ui->printLine("Maybe we can decode the code on the [paper].");
            return;
        case 6:
            if (ui) ui->printLine("This must be the security center. You see a KEY! This must fit something important. \nProlly better <take> it with you!");
            if (ui) ui->printLine("The elevator is on the <north> wall of the security center.");
            return;
        case 8:
            if (ui) ui->printLine("As you enter this dark liminal space, you feel a sense of unease.");
            if (ui) ui->printLine("This room is filled with cubicles.");
            if (ui) ui->printLine("A small piece of PAPER catches your eye. Better <take> it along.");
            return;
        case 9:
            if (ui) ui->printLine("Ermmmm... The eighth and tenth floor access doors are locked!");
            return;
        case 11:
            if (ui) ui->printLine("Executive Suite North is Locked!");
            return;
        case 12:
            if (ui) ui->printLine("Executive Suite South is Locked!");
            return;
        case 13:
            if (ui) ui->printLine("You see a pack of BATTERIES and a can of Olliebeans!");
            if (ui) ui->printLine("You can <take> the batteries, but the Olliebeans will always remain.");
            return;
        case 14:
            if (ui) ui->printLine("Among the heavy cables running floor to ceiling, you notice \na giant switchgear, with a lock securing the actuator.");
            if (ui) ui->printLine("If you had the KEY you could <unlock> the switchgear.");
            return;
        default:
            if (items.empty()) {
                if (ui) ui->printLine("Nothing more to see here. Let's keep moving.");
            } else {
                if (ui) ui->printLine("Oopsie! Well, this is really embarassing...");
                if (ui) ui->printLine(std::to_string(pos));
            }
            return;
    }
}
