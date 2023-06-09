#include "../headers/GameState.hpp"

#include<algorithm>

GameState* GameState::instance = 0;

GameState::GameState() {
    GameState::totalCluesLeftToPutInBoxes = 9;
    GameState::energy = 10;
    GameState::fear = 0;
    GameState::cluesFound = 0;
    GameState::clue = "WAREHOUSE";
    GameState::foundClueLetters = new bool[9];
    for(int i = 0; i < 9; i++) {
        GameState::foundClueLetters[i] = false;
    }
}

GameState* GameState::getInstance() {
    if(!GameState::instance) {
        instance = new GameState();
    }
    return instance;
}

void GameState::decrementTotalCluesLeftToPutInBoxes() {
    GameState::totalCluesLeftToPutInBoxes -= 1;
}

int GameState::getTotalCluesLeftToPutInBoxes() {
    return GameState::totalCluesLeftToPutInBoxes;
}

int GameState::getEnergy() {
    return GameState::energy;
}

void GameState::decrementEnergy() {
    if (GameState::energy > 0){
        GameState::energy -= 1;
    }
}

void GameState::incrementEnergy() {
    if (GameState::energy < 10) {
        GameState::energy += 1;
    }
}

void GameState::incrementFear() {
    if (GameState::fear < 10){
        GameState::fear += 1;
    }
}

int GameState::getFear() {
    return 10 - GameState::fear;
}

void GameState::incrementCluesFound() {
    GameState::cluesFound += 1;
    GameState::foundClueLetterIndex = rand() % 9;
    while(GameState::foundClueLetters[foundClueLetterIndex]) {
        GameState::foundClueLetterIndex = rand() % 9;
    }
    GameState::foundClueLetters[GameState::foundClueLetterIndex] = true;
}

bool GameState::hasFoundClue(int clueNum) {
    return GameState::foundClueLetters[clueNum];
}

std::string GameState::getClue() {
    return GameState::clue;
}

void GameState::forceGameOver() {
    GameState::energy = 0;
}

bool GameState::isGameOver() {
    return GameState::energy == 0 || GameState::fear == 10 || GameState::cluesFound == 9;
}

bool GameState::gameFailed() {
    return GameState::energy == 0 || GameState::fear == 10;
}
