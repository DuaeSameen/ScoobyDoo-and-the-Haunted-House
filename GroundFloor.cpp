#include "../headers/GroundFloor.hpp"

//has different dimensions from rest of the floors 1000x35
GroundFloor::GroundFloor(int x, int y) : BaseFloor(x, y, 1000, 35) {

}

//returns asset key of the floor - no asset key (actor because of collision, not for the purpose of rendering)
std::string GroundFloor::getAssetKey() {
    return "";
}