#include "../headers/Snack.hpp"

Snack::Snack(int x, int y) : Actor(x, y, 30, 25) {
    Snack::eaten = false;
}

void Snack::eat() {
    Snack::eaten = true;
}

bool Snack::isEaten() {
    return Snack::eaten;
}

std::string Snack::getAssetKey() {
    return "snack";
}