#include "../headers/Actor.hpp"

Actor::Actor(int x, int y, int w, int h) {
    Actor::x = x;
    Actor::y = y;
    Actor::w = w;
    Actor::h = h;
}

int Actor::getX() {
    return Actor::x;
}

int Actor::getY() {
    return Actor::y;
}

int Actor::getW() {
    return Actor::w;
}

int Actor::getH() {
    return Actor::h;
}

void Actor::setW(int w) {
    Actor::w = w;
}

void Actor::setH(int h) {
    Actor::h = h;
}

bool Actor::isCollidingWith(Actor& actor) {
    if(
        Actor::x < actor.getX() + actor.getW() &&
        Actor::x + Actor::w > actor.getX() &&
        Actor::y < actor.getY() + actor.getH() &&
        Actor::h + Actor::y > actor.getY()
    ) {
        return true;
    }
}