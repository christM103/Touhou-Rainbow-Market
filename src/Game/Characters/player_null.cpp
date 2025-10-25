// Copyright 2025 chrisfantasy

#include "Game/player.hpp"

namespace TR {
    Player_Null::Player_Null(Player_ID ID, int type) : Player_Data(ID) {
        _style_type = type;
        _char_desc = "Null \nType Num " + std::to_string(_style_type);
        _player_char_state = S_Null_Char;
        _player_pathway = { S_Koishi, S_Koishi, S_Koishi, S_Koishi, S_Koishi };
    }

    Player_Null::~Player_Null() {}

}  // namespace TR