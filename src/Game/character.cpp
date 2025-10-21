// Copyright 2025 chrisfantasy

#include <iostream>
#include <string>
#include "Game/character.hpp"

namespace TR {

// Constructor and Destuctor
Character::Character(): Player_Data(Player_ID::PI_Player_Null),
     _char_desc("Null"), _style_type(1), _turn(1) {}

Character::Character(int type, Player_ID ID): Player_Data(ID),
     _char_desc("Null"), _style_type(type), _turn(1) {}

Character::Character(int type, Player_ID ID, Char_State state) {
    switch (state) {
        case S_Reimu:
            *this << Reimu(type, ID);
            break;
        case S_Marisa:
            *this << Marisa(type, ID);
            break;
        default:
            *this << Character(type, ID);
            break;
    }
}

Character::~Character() {}


// Mutators and Accessors
int Character::getType() {
    return _style_type;
}

int Character::getTurn() {
    return _turn;
}

void Character::setType(int type) {
    _style_type = type;
}

void Character::setTurn(int turn) {
    _turn = turn;
}

void Character::setDesc(std::string str) {
    _char_desc = str;
}


// Other char functions
void Character::showDesc() {
    std::cout << _char_desc << "\n";
}

void Character::turnInc() {
    _turn++;
}

template <class T> Character& Character::operator<<(const T& ch) {
    this->_char_desc = ch._char_desc;
    this->_style_type = ch._style_type;
    this->setChar(ch._player_char_state);
    this->setPathway();
    this->_player_balance = ch._player_balance;
    return *this;
}

}  // namespace TR
