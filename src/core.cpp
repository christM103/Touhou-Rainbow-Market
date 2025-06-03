// Copyright 2025 chrisfantasy

#include "../include/core.hpp"
#include <chrono>
#include <iostream>

using namespace std::chrono_literals;

typedef std::chrono::steady_clock::time_point current_time;
typedef std::chrono::seconds seconds;
typedef std::chrono::duration<double> timer;

namespace TR {

// Timer Functions

Timer::Timer(seconds new_dur) {
    _start = std::chrono::steady_clock::now();
    _dur = new_dur;
    _curr_left = _dur;
}

timer Timer::time_left() {
    _curr_left = _dur - (std::chrono::steady_clock::now() - _start);
    return _curr_left;
}

void Timer::timer_reset(seconds new_dur) {
    *this = Timer(new_dur);
}

}  // namespace TR


/*

// Player Functions

Player::Player(Player_ID playerID, Char_State charID) {

    _data = Player_Data(playerID);
    
    switch (charID) {
        case S_Reimu:
            _char_data = Reimu(2);
            break;
        case S_Marisa:
            _char_data = Marisa(2);
            break;
        default:
            _char_data = Char(2);
            break;
    }

    _char_data.showDesc();

}

Player::~Player() {}

Player_Data Player::getPlayerData() {
    return _data;
}
Char Player::getCharData() {
    return _char_data;
}

void Player::setPlayerData(Player_Data pl) {
    _data = pl;
}

void Player::setCharData(Char ch) {
    _char_data = ch;
}

*/
