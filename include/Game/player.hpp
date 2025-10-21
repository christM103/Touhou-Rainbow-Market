// Copyright 2025 chrisfantasy

#pragma once

#include <memory>

#include "Game/land.hpp"

namespace TR {

// TODO: Replace enums w uint16s, try to combine Player_Data class w Character class

enum Char_State {
    S_Null_Char, S_Reimu, S_Marisa, S_Sanae, S_Flandre, S_Youmu, S_Tewi, S_Koishi
};

static const std::string Char_State_Str[] =
    {"Null", "Reimu", "Marisa", "Sanae", "Flandre", "Youmu", "Tewi", "Koishi"};

enum Action_State {
    A_Idle, A_Action_1, A_Action_2, A_Finished
};

enum class Player_ID {
    PI_Player_Null, PI_Player_1, PI_Player_2, PI_Player_3, PI_Player_4
};

class Player_Data{
 public:
    // Constructor and Destuctor
    Player_Data();
    explicit Player_Data(Player_ID ID);
    ~Player_Data();


    // Accessors and Mutators
    float getBalance();
    float getProfit();
    std::unique_ptr<Land>& getLot();
    std::string getActionState();
    Char_State getCharState();
    std::string getPathway();
    Player_ID getPlayerID();
    void setChar(Char_State state);
    void setPathway();

    // Other Functions
    void balanceChange(float change);

 protected:
    std::unique_ptr<Land> _player_lot {new Land()};
    Player_ID _player_ID;
    float _player_balance {0};
    float _player_profit {0};
    Action_State _player_action_state {Action_State::A_Idle};
    Char_State _player_char_state {Char_State::S_Null_Char};
    std::vector<Char_State> _player_pathway {Char_State::S_Null_Char};
};

}  // namespace TR
