// Copyright 2025 chrisfantasy

#pragma once

#include "Game/land.hpp"

namespace TR {

// TODO: Replace enums w uint16s, try to combine Player_Data class w Character class

enum Char_State : uint8_t {
    S_Null_Char, S_Reimu, S_Marisa, S_Sanae, S_Flandre, S_Youmu, S_Tewi, S_Koishi
};

static const std::string Char_State_Str[] =
    {"Null", "Reimu", "Marisa", "Sanae", "Flandre", "Youmu", "Tewi", "Koishi"};

enum Action_State : uint8_t {
    A_Idle, A_Action_1, A_Action_2, A_Finished
};

enum Player_ID : uint8_t {
    PI_Player_Null, PI_Player_1, PI_Player_2, PI_Player_3, PI_Player_4
};

class Player_Data{
 public:
    // Constructor and Destuctor
    Player_Data();
    explicit Player_Data(Player_ID ID);
    ~Player_Data();

    // Copy Constructors and Move Constructors
    Player_Data(const Player_Data&) = delete;
    Player_Data& operator=(const Player_Data& other) = delete;
    Player_Data(Player_Data&&) noexcept = default;
    Player_Data& operator=(Player_Data&& other) noexcept = default;

    // Standard Accessors
    inline Player_ID getPlayerID() { return _player_ID; };
    inline int getCharState() { return _player_char_state; };
    inline int getType() { return _style_type; };
    std::string getPathway();
    inline std::unique_ptr<Land>& getLand() { return _player_land; };
    inline float getBalance() { return _player_balance; };
    inline float getProfit() { return _player_profit; };
    inline int getTurn() { return _turn; };
    inline std::string getActionState() { return std::to_string(_player_action_state); };

    // Standard Mutators
    inline void setType(int type) { _style_type = type; };
    inline void setTurn(int turn) { _turn = turn; };
    inline void setDesc(std::string str) { _char_desc = str; }
    void setChar(Char_State state);
    void setPathway();

    // Other Functions
    void balanceChange(float change);
    void showDesc();
    void turnInc();

 protected:
	 Player_ID _player_ID;                                                               // Player Identifier
     Char_State _player_char_state{ Char_State::S_Null_Char };                           // Player's Current Character State
     std::string _char_desc{ "" };                                                       // Player's Character Description
     int _style_type{ 0 };                                                               // Player's Playstyle Type Number
     std::vector<Char_State> _player_pathway{ Char_State::S_Null_Char };                 // Player's Character Progression Pathway
	 std::unique_ptr<Land> _player_land{ new Land() };                                   // Player's Land Lot
	 float _player_balance{ 0 };                                                         // Player's Current Balance
	 float _player_profit{ 0 };                                                          // Player's Total Profit
     int _turn{ 0 };                                                                     // Player's Current Turn Number
	 Action_State _player_action_state{ Action_State::A_Idle };                          // Player's Current Action State
};

class Player_Null : public Player_Data {
public:
    Player_Null(Player_ID ID, int type);
    ~Player_Null();
};

class Player_Reimu : public Player_Data {
public:
    // Constructor and Destuctor
    Player_Reimu(Player_ID ID, int type);
    ~Player_Reimu();

    // Child Functions
    void ReimuTreasure(Land& lot, int index);
    void ReimuTalisA(Land& lot, int index);
    void ReimuTalisB(Land& lot, int index);

private:
    // Yin-Yang Orb, Seal (Playstyle A), Barrier (Playstyle B)
    int _yOrb{ 0 }, _rSealT{ 3 }, _rBarrierT{ 3 };
};

class Player_Marisa : public Player_Data {
public:
    // Constructor and Destuctor
    Player_Marisa(Player_ID ID, int type);
    ~Player_Marisa();

    // Child Functions
    void MarisaMushroom(Player_Data& playerA, Player_Data& playerB);
    void MarisaMagicA(Player_Data& playerA, Player_Data& playerB);

private:
    // Mushroom Variable, Magic Level (Playstyle B)
    int _randMush{ 1 }, _magLvl{ 1 };
};


}  // namespace TR
