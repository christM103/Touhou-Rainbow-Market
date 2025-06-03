// Copyright 2025 chrisfantasy

#pragma once

#include <iostream>
#include <vector>
#include <map>
#include "market.hpp"

namespace TR {

enum class Lot_State {
    LS_free, LS_occupied,                         //  First index         (free or occupied)
    LS_normal, LS_shut_down, LS_immune,              //  Second index        (lot status)
    LS_Reimu_Orb, LS_Reimu_TalisA, LS_Reimu_TalisB   //  Third to Nth index  (character/event effects)
};

class Lot{
 public:
    // Constructor and Destuctor
    Lot();
    ~Lot();

    // Accessors and Mutators
    Market getLot(int ind);
    std::string getLotAll();
    void setLot(int ind, Market mar);
    void remLot(int ind);
    void swapLot(Lot& lot);

    // Other Functions
    void setState(int ind, Lot_State state);
    void remState(int ind, Lot_State state);

 private:
    std::map<int, std::vector<TR::Lot_State>> _lotStates;
    std::vector<Market> _lotMarkets;
};

}  // namespace TR
