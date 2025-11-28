// Copyright 2025 chrisfantasy

/*

Marisa Route:
1 - Flandre, 2 - Koishi, 3 - Kosuzu, 4 - Reimu, 5 - Sagume, 6 - Chimata
EX - EX Sagume

Marisa’s Magic Shop side?


PLAYSTYLE #1:
Every time you have one more hundred thousand in your possession, you gain a level in your “magician” meter” (Max 10). Every 2 levels give you different stacking mandatory effects…
    Lv 2 - Gain a random mushroom effect.
    Lv 4 -  Spend “magician meter” to steal X * $100,000 from your opponent where X is level spent (Min 0). 
    Lv 6 - Steal $50,000 from your opponents.
    Lv 8 - Gain a random mushroom effect.
    Lv 10 - Spend half of total profits, you lose half “magician meter.” Your opponent loses as much profit as you lost. Gain half of what your opponent lost.

PLAYSTYLE #2:
Once per turn you can choose to…
    Sacrifice an open market and “eat a mushroom” with stacking effects correlating to the turn number: 
    Even (2,4,6,8,10): You and your opponent loses $150,000.
    Odd (1,3,5,7,9): Steal $X from your opponents where X is 1/4 of your total profit. 
    Lucky (5,7): Gain $250,000, Steal $100,000 from your opponent. You do not need to sacrifice an open market this turn. 
    Unlucky (4, 9): Shut down a select open market in your possession for 1 turn. 
*/

#include "Game/player.hpp"
#include <random>



namespace TR {

Player_Marisa::Player_Marisa(Player_ID ID, int type) : Player_Data(ID) {
    _style_type = type;
    _char_desc = "Marisa \nType Num " + std::to_string(_style_type);
    _player_char_state = S_Marisa;
    _player_pathway = { S_Tewi, S_Sanae, S_Koishi, S_Reimu, S_Flandre };
}

Player_Marisa::~Player_Marisa() {}

void Player_Marisa::MarisaMushroom(Player_Data& playerA, Player_Data& playerB) {
    _randMush = rand() * 6;
    std::cout << _randMush << "\n";
    if (_randMush % 2 == 0) {
        playerA.balanceChange(-150000);
        playerB.balanceChange(-150000);
        std::cout << "Even Mush \n";
    } else {
        playerA.balanceChange(playerB.getProfit() / 4);
        playerB.balanceChange(-(playerB.getProfit() / 4));
        std::cout << "Odd Mush \n";
    }
}

void Player_Marisa::MarisaMagicA(Player_Data& playerA, Player_Data& playerB) {}

}  // namespace TR
