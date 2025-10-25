// Copyright 2025 chrisfantasy

#pragma once

#include <chrono>

#include "Game/player.hpp"
//#include "Game/event.hpp"

using namespace std::chrono_literals;

typedef std::chrono::steady_clock::time_point current_time;
typedef std::chrono::seconds seconds;
typedef std::chrono::duration<double> timer;

namespace TR {

class Timer {
 public:
    explicit Timer(seconds new_dur);
    timer time_left();
    void timer_reset(seconds new_dur);


 private:
    current_time _start;
    seconds _dur;
    timer _curr_left;
};

class Turns {
 public:
    Turns();
    ~Turns();
    void nextTurn();

 private:
    int _turn_count;
};

}  // namespace TR
