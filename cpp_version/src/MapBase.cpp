#include "MapBase.h"
#include "IGameUI.h"

void MapBase::clearScreen(IGameUI* ui) {
    if (ui) ui->clearScreen();
}

void MapBase::printMap(IGameUI* ui, const char* mapStr) {
    clearScreen(ui);
    if (ui) ui->print(mapStr);
}
