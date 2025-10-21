// Copyright 2025 chrisfantasy

#include "Game/player.hpp"

namespace TR {

Player_Data::Player_Data() : _player_ID(Player_ID::PI_Player_Null) {}

Player_Data::Player_Data(Player_ID ID) : _player_ID(ID) {}

Player_Data::~Player_Data() {}

// Accessors and Mutators
float Player_Data::getBalance() {
    return _player_balance;
}

float Player_Data::getProfit() {
    return _player_profit;
}

std::unique_ptr<Land>& Player_Data::getLot() {
    return _player_lot;
}

std::string Player_Data::getActionState() {
    return std::to_string(_player_action_state);
}

Char_State Player_Data::getCharState() {
    return _player_char_state;
}

std::string Player_Data::getPathway() {
    std::string temp;
    for (auto i : _player_pathway) {
        temp += Char_State_Str[i] + " ";
    }
    return temp;
}

Player_ID Player_Data::getPlayerID() {
    return _player_ID;
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

}  // namespace TR
