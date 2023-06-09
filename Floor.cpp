#include "../headers/Floor.hpp"

//all floors have 635x35 dimensions except the groundfloor (separate class)
Floor::Floor(int x, int y) : BaseFloor(x, y, 635, 35) {
}

//returns asset key of the floor - no asset key (actor because of collision, not for the purpose of rendering)
std::string Floor::getAssetKey() {
    return "";
}