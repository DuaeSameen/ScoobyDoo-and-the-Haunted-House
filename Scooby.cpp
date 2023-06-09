#include "../headers/Scooby.hpp"

//initial values for scooby
Scooby::Scooby(int x, int y) : Actor(x, y, 100, 47) {
    Scooby::direction = "right";
    Scooby::currentFoot = "0";
    Scooby::footSwitchTimer = 0;
    Scooby::flashlightOn = false;
    Scooby::resetJump();
}

//changes scooby sprite to portray animation 0- neutral 1-run1 2-run2
void Scooby::changeFoot() {
    if(Scooby::currentFoot == "0") Scooby::currentFoot = "1";
    if(Scooby::footSwitchTimer % 20 == 0) {
        if(Scooby::currentFoot == "1") {
            Scooby::currentFoot = "2";
        } else {
            Scooby::currentFoot = "1";
        }
    }
}

//changes direction + moves in that direction
void Scooby::moveLeft() {
    Scooby::direction = "left";
    Scooby::x -= 1;
    Scooby::footSwitchTimer += 1; //keeps track of when to change animation
    Scooby::changeFoot();
}

//changes direction + moves in that direction
void Scooby::moveRight() {
    Scooby::direction = "right";
    Scooby::x += 1;
    Scooby::footSwitchTimer += 1;
    Scooby::changeFoot();
}

//falls down due to gravity
void Scooby::moveDown() {
    Scooby::y += 1;
}

//scooby neutral standing
void Scooby::stand() {
    Scooby::currentFoot = "0";
}

void Scooby::jump() {
    if(!Scooby::jumping) { //jumping becomes true and jumpbase is current y value
        Scooby::jumping = true;
        Scooby::jumpingUp = true;
        Scooby::jumpBase = y;
    } else { //already jumping
        if (Scooby::jumpingUp && Scooby::y > Scooby::jumpBase - 255) { //can go higher
            Scooby::y -= 1; //continues the jump
            Scooby::inAir = true; //scooby flying
        } else {
            Scooby::jumpingUp = false; //cant go higher
        }

        if (!Scooby::jumpingUp && Scooby::y < Scooby::jumpBase) { //coming back down
            Scooby::y += 1;
        } else if(!Scooby::jumpingUp && Scooby::y <= Scooby::jumpBase) { //resets to jumpbase; end of jump
            Scooby::inAir = false;
            jumping = false;
        }
    }
}

void Scooby::turnFlashlightOn() {
    if (flashlight_battery > 0){ //check for battery
        Scooby::flashlightOn = true;
        flashlight_battery -= 1; //decrement battery while flashlight in use
    }
}

void Scooby::turnFlashlightOff() {
    Scooby::flashlightOn = false;
}

void Scooby::interruptJump() { //collision occured
    Scooby::jumpingUp = false;
}

void Scooby::resetJump() { //sets all jumps to false and resets jumpbase to new y value
    Scooby::jumping = false;
    Scooby::jumpingUp = false;
    Scooby::inAir = false;
    Scooby::jumpBase = y;
}

//returns the assetkey based on current values (asset keys then used to render sprites)
string Scooby::getAssetKey() {
    if(Scooby::flashlightOn) {
        return "scooby_flashlight_" + Scooby::direction + Scooby::currentFoot;
    } else {
        return "scooby_" + Scooby::direction + Scooby::currentFoot;
    }
}

bool Scooby::isJumping() {
    return Scooby::jumping;
}

bool Scooby::isInAir() {
    return Scooby::inAir;
}

int Scooby::getBattery(){
    return flashlight_battery;
}