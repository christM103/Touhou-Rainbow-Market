// Copyright 2025 chrisfantasy

#include "Game/Logic/Player.hpp"

namespace TR {
    Player_Null::Player_Null(int type) : Player_Data() {
        _player_type = type;
        _player_desc = "Null \nType Num " + std::to_string(_player_type);
    }

    Player_Null::~Player_Null() {}

}  // namespace TR