#include "MapBase.h"
#include <iostream>
#include <cstdlib>

void MapBase::clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void MapBase::printMap(const char* mapStr) {
    clearScreen();
    std::cout << mapStr;
}

void MapBase::mapZc() {
    const char* map = R"(    ####################...#####################.##########
    #     CONTROL      #...#    COMPUTER ROOM  #.# OFFICE #
    #      ROOM        #...#       NORTH       #.# NORTH  #
    #                  #####                   #.#        #..###########
    #                               #   #      #.#### #####..#         #
    #                  ##############   ########....# #......#         #
    #                  #...#        #   #      ###### ########         #
    #                  #...#                     CORRIDOR              #
    #                  #...#..COMPUTER ROOM    ###### ########  STAIR  #
    ####################...#      SOUTH        #....# #......#  WELL   #
                  .........#                   #.#### #####..#         #
                  #######..#                   #.#        #..#         #
                  #     #..#                   #.# OFFICE #..#         #
    #############.#     ####                   #.# SOUTH  #..####  #####
    #           #.# STORAGE                    #.#        #.....#  #
    # ELEVATOR  #.#     ####                   #.##########.....#  #
    #           #.#     #..#                   #................#  #
    ########  ###.#######..###########  ########.............####  #####
           #  #......................#  #....................#         #
    ########  ########.###############  ####################.#         #
    #   SECURITY     #.# ZERO  #    ZERO        #  ZERO    #.#  OFFICE #
    #    OFFICE      #.# WEST  #   CENTRAL      #  EAST    #.#  SPACE  #
    #                ###      ###              ###         ###         #
    #                                  X                               #
    #                ###      ###              ###         ###         #
    #                #.#       #                #          #.#         #
    ##################.#####################################.###########)";
    printMap(map);
    std::cout << "\n'X' denotes current position.\n";
}

void MapBase::mapZw() {
    const char* map = R"(    ####################...#####################.##########
    #     CONTROL      #...#    COMPUTER ROOM  #.# OFFICE #
    #      ROOM        #...#       NORTH       #.# NORTH  #
    #                  #####                   #.#        #..###########
    #                               #   #      #.#### #####..#         #
    #                  ##############   ########....# #......#         #
    #                  #...#        #   #      ###### ########         #
    #                  #...#                     CORRIDOR              #
    #                  #...#..COMPUTER ROOM    ###### ########  STAIR  #
    ####################...#      SOUTH        #....# #......#  WELL   #
                  .........#                   #.#### #####..#         #
                  #######..#                   #.#        #..#         #
                  #     #..#                   #.# OFFICE #..#         #
    #############.#     ####                   #.# SOUTH  #..####  #####
    #           #.# STORAGE      X             #.#        #.....#  #
    # ELEVATOR  #.#     ####                   #.##########.....#  #
    #           #.#     #..#                   #................#  #
    ########  ###.#######..###########  ########.............####  #####
           #  #......................#  #....................#         #
    ########  ########.###############  ####################.#         #
    #   SECURITY     #.# ZERO  #    ZERO        #  ZERO    #.#  OFFICE #
    #    OFFICE      #.# WEST  #   CENTRAL      #  EAST    #.#  SPACE  #
    #                ###      ###              ###         ###         #
    #                                                                  #
    #                ###      ###              ###         ###         #
    #                #.#       #                #          #.#         #
    ##################.#####################################.###########)";
    printMap(map);
    std::cout << "\n'X' denotes current position.\n";
}

void MapBase::mapZe() {
    const char* map = R"(    ####################...#####################.##########
    #     CONTROL      #...#    COMPUTER ROOM  #.# OFFICE #
    #      ROOM        #...#       NORTH       #.# NORTH  #
    #                  #####                   #.#        #..###########
    #                               #   #      #.#### #####..#         #
    #                  ##############   ########....# #......#         #
    #                  #...#        #   #      ###### ########         #
    #                  #...#                     CORRIDOR              #
    #                  #...#..COMPUTER ROOM    ###### ########  STAIR  #
    ####################...#      SOUTH        #....# #......#  WELL   #
                  .........#                   #.#### #####..#         #
                  #######..#                   #.#        #..#         #
                  #     #..#                   #.# OFFICE #..#         #
    #############.#     ####                   #.# SOUTH  #..####  #####
    #           #.# STORAGE                    #.#        #.....#  #
    # ELEVATOR  #.#     ####                   #.##########.....#  #
    #           #.#     #..#                   #................#  #
    ########  ###.#######..###########  ########.............####  #####
           #  #......................#  #....................#         #
    ########  ########.###############  ####################.#         #
    #   SECURITY     #.# ZERO  #    ZERO        #  ZERO    #.#  OFFICE #
    #    OFFICE      #.# WEST  #   CENTRAL      #  EAST    #.#  SPACE  #
    #                ###      ###              ###         ###         #
    #                                                              X   #
    #                ###      ###              ###         ###         #
    #                #.#       #                #          #.#         #
    ##################.#####################################.###########)";
    printMap(map);
    std::cout << "\n'X' denotes current position.\n";
}

void MapBase::mapCompS() {
    const char* map = "Computer Room South\n";
    printMap(map);
}

void MapBase::mapCompN() {
    const char* map = "Computer Room North\n";
    printMap(map);
}

void MapBase::mapSec() {
    const char* map = "Security Office\n";
    printMap(map);
}

void MapBase::mapOff() {
    const char* map = "Office Space\n";
    printMap(map);
}

void MapBase::mapStair() {
    const char* map = "Stairwell\n";
    printMap(map);
}

void MapBase::mapCor() {
    const char* map = "Corridor\n";
    printMap(map);
}

void MapBase::mapSto() {
    const char* map = "Storage\n";
    printMap(map);
}

void MapBase::mapCtrl() {
    const char* map = "Control Room\n";
    printMap(map);
}
