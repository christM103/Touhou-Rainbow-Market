// Copyright 2025 chrisfantasy

#include "Game/logic.hpp"
#include <chrono>

#include "Engine/Graphics/AssetManager.hpp"


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


Game_States::Game_States() {}
Game_States::~Game_States() {}


void Game_States::update(Engine::Engine* gEngine, Sprite_Map& sprite_set, Player_Set& player_set) {}


}  // namespace TR
