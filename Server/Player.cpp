//
// Created by benra on 7/16/2024.
//

#include "Player.h"

bool Player::establishConnection() {
    if (!init){
        init = true;
        return true;
    }
    else {
        return false;
    }
}