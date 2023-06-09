#include "../headers/BaseFloor.hpp"

//initialize 3 treasure boxes for each floor
BaseFloor::BaseFloor(int x, int y, int w, int h) : Actor(x, y, w, h) {
    for(int i = 0; i < 3; i++) {
        BaseFloor::treasureBoxes[i] = new TreasureBox(x + (w/3)*(i+1) - 45, y - 21);
        // std::cout << BaseFloor::treasureBoxes[i] << std::endl;
    }
}

TreasureBox** BaseFloor::getTreasureBoxes() {
    return BaseFloor::treasureBoxes;
}