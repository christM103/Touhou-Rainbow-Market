// Copyright 2025 chrisfantasy

/*

Reimu Route:
1 - Yukari, 2 - Futo, 3 - Suika, 4 - Sanae, 5 - Marisa, 6 - Chimata
EX - EX Yukari

Hakurei Shrine side?


PLAYSTYLE #1:
Once per turn you can choose to…
    Treasure - Place a “Yin-Yang Orb” on a select open market boosting the profit rate of it by x100 and x50 to the open markets surrounding them.
    Seal - Shut down a select open market for 2 turns, leave a “Talisman” on that open market, cannot target an open market w/ “Talisman.”
        For every 3 “Talisman” in play you can negate the activation of a skill that targets your total profit. Remove those “Talisman.”

PLAYSTYLE #2:
Once per turn you can choose to…
    Treasure - Place a “Yin-Yang Orb” on a select open market boosting the profit rate of it by x100 and x50 to the open markets surrounding them.
    Barrier - Grant immunity to a select open market for 2 turns, leave a “Talisman” on that open market, cannot target an open market w/ “Talisman.”
        For every 3 “Talisman” in play you can negate the activation of a skill that targets your total profit. Remove those “Talisman.”

*/

#include "Game/player.hpp"

namespace TR {
Player_Reimu::Player_Reimu(Player_ID ID, int type) : Player_Data(ID) {
    _style_type = type;
    _char_desc = "Reimu \nType Num " + std::to_string(_style_type);
    _player_char_state = S_Reimu;
    _player_pathway = { S_Tewi, S_Koishi, S_Sanae, S_Marisa, S_Flandre };
}

Player_Reimu::~Player_Reimu() {}

void Player_Reimu::ReimuTreasure(Land& lot, int index) {
    lot.setState(index, LS_Reimu_Orb);
}

void Player_Reimu::ReimuTalisA(Land& lot, int index) {
    if (_rSealT > 0) {
        lot.setState(index, LS_Reimu_TalisA);
        _rSealT--;
    }
}

void Player_Reimu::ReimuTalisB(Land& lot, int index) {
    if (_rBarrierT > 0) {
        lot.setState(index, LS_Reimu_TalisB);
        _rBarrierT--;
    }
}

}  // namespace TR
