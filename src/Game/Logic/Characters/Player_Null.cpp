// Copyright 2025 chrisfantasy

#include "Game/Logic/Player.hpp"

namespace TR {
    Player_Null::Player_Null(int type) : Player_Data() {
        _style_type = type;
        _char_desc = "Null \nType Num " + std::to_string(_style_type);
    }

    Player_Null::~Player_Null() {}

}  // namespace TR