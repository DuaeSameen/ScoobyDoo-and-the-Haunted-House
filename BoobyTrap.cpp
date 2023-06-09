#include "../headers/BoobyTrap.hpp"

BoobyTrap::BoobyTrap(int x, int y) : Actor(x, y, 40, 25) {
}

std::string BoobyTrap::getAssetKey() {
    return "booby_trap";
}