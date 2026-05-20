#ifndef MAPBASE_H
#define MAPBASE_H

class IGameUI;

class MapBase {
public:
    static void mapZc(IGameUI* ui);   // Zero Central
    static void mapZw(IGameUI* ui);   // Zero West
    static void mapZe(IGameUI* ui);   // Zero East
    static void mapCompS(IGameUI* ui);
    static void mapCompN(IGameUI* ui);
    static void mapSec(IGameUI* ui);  // Security
    static void mapOff(IGameUI* ui);  // Office space
    static void mapStair(IGameUI* ui);
    static void mapCor(IGameUI* ui);  // Corridor
    static void mapSto(IGameUI* ui);  // Storage
    static void mapCtrl(IGameUI* ui); // Control room
    
private:
    static void clearScreen(IGameUI* ui);
    static void printMap(IGameUI* ui, const char* mapStr);
};

#endif
