// Copyright 2025 chrisfantasy

#pragma once

#include <string>
#include <vector>
#include "player.hpp"
#include "lots.hpp"

namespace TR {

class Char: public Player_Data{
 public:
    // Constructor and Destuctor
    Char();
    Char(int type, Player_ID ID);
    Char(int type, Player_ID ID, Char_State state);
    ~Char();

    // Mutators and Accessors
    int getType();
    int getTurn();
    void setType(int type);
    void setTurn(int turn);
    void setDesc(std::string str);

    // Other char functions
    void showDesc();
    void turnInc();
    template <class T> Char& operator<<(const T& ch);

 protected:
    // Character Description, Character Type, and # of Turns
    std::string _char_desc;
    int _style_type, _turn;
};

class Reimu: public Char {
 public:
    // Constructor and Destuctor
    Reimu(int type, Player_ID ID);
    ~Reimu();

    // Child Functions
    void ReimuTreasure(Lot& lot, int index);
    void ReimuTalisA(Lot& lot, int index);
    void ReimuTalisB(Lot& lot, int index);

 private:
    // Yin-Yang Orb, Seal (Playstyle A), Barrier (Playstyle B)
    int _yOrb {0}, _rSealT {0}, _rBarrierT {0};
};

class Marisa: public Char {
 public:
    // Constructor and Destuctor
    Marisa(int type, Player_ID ID);
    ~Marisa();

    // Child Functions
    void MarisaMushroom(Player_Data& playerA, Player_Data& playerB);
    void MarisaMagicA(Player_Data& playerA, Player_Data& playerB);

 private:
    // Mushroom Variable, Magic Level (Playstyle B)
    int _randMush {1}, _magLvl {1};
};

}  // namespace TR
