// Copyright 2025 chrisfantasy

#include "Game/Logic/Player.hpp"

namespace TR {

Player_Data::Player_Data() {}

Player_Data::~Player_Data() {}

// Accessors and Mutators

void Player_Data::balanceChange(float change) {
    _player_balance += change;
}

// Other char functions
void Player_Data::showDesc() {
    std::cout << _char_desc << "\n";
}

}  // namespace TR
