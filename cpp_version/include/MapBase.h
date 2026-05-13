#ifndef MAPBASE_H
#define MAPBASE_H

class MapBase {
public:
    static void mapZc();   // Zero Central
    static void mapZw();   // Zero West
    static void mapZe();   // Zero East
    static void mapCompS();
    static void mapCompN();
    static void mapSec();  // Security
    static void mapOff();  // Office space
    static void mapStair();
    static void mapCor();  // Corridor
    static void mapSto();  // Storage
    static void mapCtrl(); // Control room
    
private:
    static void clearScreen();
    static void printMap(const char* mapStr);
};

#endif
