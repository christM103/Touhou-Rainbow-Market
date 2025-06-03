// Copyright 2025 chrisfantasy
#include "../include/char.hpp"
#include <iostream>
#include <string>

namespace TR {

// Constructor and Destuctor
Char::Char(): Player_Data(Player_ID::PI_Player_Null),
     _char_desc("Null"), _style_type(1), _turn(1) {}

Char::Char(int type, Player_ID ID): Player_Data(ID),
     _char_desc("Null"), _style_type(type), _turn(1) {}

Char::Char(int type, Player_ID ID, Char_State state) {
    switch (state) {
        case S_Reimu:
            *this << Reimu(type, ID);
            break;
        case S_Marisa:
            *this << Marisa(type, ID);
            break;
        default:
            *this << Char(type, ID);
            break;
    }
}

Char::~Char() {}


// Mutators and Accessors
int Char::getType() {
    return _style_type;
}

int Char::getTurn() {
    return _turn;
}

void Char::setType(int type) {
    _style_type = type;
}

void Char::setTurn(int turn) {
    _turn = turn;
}

void Char::setDesc(std::string str) {
    _char_desc = str;
}


// Other char functions
void Char::showDesc() {
    std::cout << _char_desc << "\n";
}

void Char::turnInc() {
    _turn++;
}

template <class T> Char& Char::operator<<(const T& ch) {
    this->_char_desc = ch._char_desc;
    this->_style_type = ch._style_type;
    this->setChar(ch._player_char_state);
    this->setPathway();
    this->_player_balance = ch._player_balance;
    return *this;
}

}  // namespace TR
