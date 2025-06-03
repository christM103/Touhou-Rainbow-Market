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

#include "../../include/char.hpp"

namespace TR {
Reimu::Reimu(int type, Player_ID ID) : Char(type, ID) {
    _char_desc = "Reimu \nType Num " + std::to_string(_style_type);
    this->setChar(S_Reimu);
}

Reimu::~Reimu() {}

void Reimu::ReimuTreasure(Lot& lot, int index) {
    lot.setState(index, Lot_State::LS_Reimu_Orb);
}

void Reimu::ReimuTalisA(Lot& lot, int index) {
    lot.setState(index, Lot_State::LS_Reimu_TalisA);
    _rSealT++;
    if (_rSealT == 3) {
        lot.remState(index, Lot_State::LS_Reimu_TalisA);
        _rSealT = 0;
    }
}

void Reimu::ReimuTalisB(Lot& lot, int index) {
    lot.setState(index, Lot_State::LS_Reimu_TalisB);
    _rBarrierT++;
    if (_rBarrierT == 3) {
        lot.remState(index, Lot_State::LS_Reimu_TalisB);
        _rBarrierT = 0;
    }
}

}  // namespace TR
