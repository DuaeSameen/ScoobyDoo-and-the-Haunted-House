#include "../headers/TreasureBox.hpp"
#include "../headers/GameState.hpp"

#include <iostream>

int TreasureBox::currentBoxNum = 0;

TreasureBox::TreasureBox(int x, int y) : Actor(x, y, 45, 21) {
    TreasureBox::opened = false;
    TreasureBox::currentBoxNum += 1;
    if(GameState::getInstance()->getTotalCluesLeftToPutInBoxes() < 12 - currentBoxNum) {
        bool shouldHaveClue = rand() % 2;
        if(shouldHaveClue) {
            GameState::getInstance()->decrementTotalCluesLeftToPutInBoxes();
            TreasureBox::hasClue = true;
        }
    } else {
        //std::cout << "here" << std::endl;
        GameState::getInstance()->decrementTotalCluesLeftToPutInBoxes();
        TreasureBox::hasClue = true;
    }
}

std::string TreasureBox::getAssetKey() {
    if(TreasureBox::opened) {
        return "treasure_box_opened";
    } else {
        return "treasure_box_closed";
    }
}

void TreasureBox::open() {
    TreasureBox::opened = true;
}

void TreasureBox::close() {
    TreasureBox::opened = false;
}

bool TreasureBox::isOpened() {
    return TreasureBox::opened;
}

bool TreasureBox::containsClue() {
    return TreasureBox::hasClue;
}
