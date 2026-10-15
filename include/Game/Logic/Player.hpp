// Copyright 2025 chrisfantasy

#pragma once


#include <memory>
#include <vector>
#include <map>

#include "Game/Logic/Land.hpp"

namespace TR {

// TODO: Replace enums w uint16s, try to combine Player_Data class w Character class

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
    inline int getType() { return _player_type; };
    inline std::unique_ptr<Land>& getLand() { return _player_land; };
    inline float getBalance() { return _player_balance; };
    inline float getProfit() { return _player_profit; };

    // Standard Mutators
    inline void setType(int type) { _player_type = type; };
    inline void setDesc(std::string str) { _player_desc = str; }

    // Other Functions
    void balanceChange(float change);
    void showDesc();

 protected:
     uint8_t _player_type{ 0 };                                                          // Player's Playstyle Type Number
     float _player_balance{ 0 };                                                         // Player's Current Balance
     float _player_profit{ 0 };                                                          // Player's Total Profit
     std::string _player_desc{ "" };                                                     // Player's Character Description
     std::unique_ptr<Land> _player_land{ new Land() };                                   // Player's Land Lot
     


     
};

class Player_Null : public Player_Data {
public:
    Player_Null(int type);
    ~Player_Null();
};

class Player_Reimu : public Player_Data {
public:
    // Constructor and Destuctor
    Player_Reimu(int type);
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
    Player_Marisa(int type);
    ~Player_Marisa();

    // Child Functions
    void MarisaMushroom(Player_Data& playerA, Player_Data& playerB);
    void MarisaMagicA(Player_Data& playerA, Player_Data& playerB);

private:
    // Mushroom Variable, Magic Level (Playstyle B)
    int _randMush{ 1 }, _magLvl{ 1 };
};


}  // namespace TR
