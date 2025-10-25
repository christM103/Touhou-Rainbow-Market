// Copyright 2025 chrisfantasy

#include "Game/player.hpp"

namespace TR {

Player_Data::Player_Data() : _player_ID(Player_ID::PI_Player_Null) {}

Player_Data::Player_Data(Player_ID ID) : _player_ID(ID) {}

Player_Data::~Player_Data() {}

// Accessors and Mutators

std::string Player_Data::getPathway() {
    std::string temp;
    for (auto i : _player_pathway) {
        temp += Char_State_Str[i] + " ";
    }
    return temp;
}


void Player_Data::balanceChange(float change) {
    _player_balance += change;
}

void Player_Data::setChar(Char_State state) {
    _player_char_state = state;
    this->setPathway();
}

void Player_Data::setPathway() {
    switch (_player_char_state) {
        case S_Reimu:
            _player_pathway = {S_Tewi, S_Koishi, S_Sanae, S_Marisa, S_Flandre};
            break;
        case S_Marisa:
            _player_pathway = {S_Flandre, S_Tewi, S_Koishi, S_Sanae, S_Reimu};
            break;
        case S_Sanae:
            break;
        case S_Flandre:
            break;
        case S_Youmu:
            break;
        case S_Tewi:
            break;
        case S_Koishi:
            break;
        default:
            break;
    }
}

// Other char functions
void Player_Data::showDesc() {
    std::cout << _char_desc << "\n";
}

void Player_Data::turnInc() {
    _turn++;
}

}  // namespace TR
