// Copyright 2025 chrisfantasy

#include "../include/lots.hpp"
#include <iostream>
#include <vector>
#include <map>

namespace TR {

Lot::Lot() {
    _lotMarkets.reserve(5);
    for (unsigned x = 0; x < 5; x++) {
        _lotStates[x] = {Lot_State::LS_free, Lot_State::LS_normal};
        _lotMarkets.push_back(Market(Market_ID::MID_Null, 1, 0));
        // std::cout << _lotMarkets.size() << "\n";
    }
    // std::cout << _lotMarkets.size() << "\n";
    // std::cout << _lotStates[1].size() << "\n";
}

Lot::~Lot() {}

Market Lot::getLot(int ind) {
    return _lotMarkets[ind];
}

std::string Lot::getLotAll() {
    std::string temp;
    for (auto i : _lotMarkets) {
        // std::cout << "FUCK3\n";
        temp << i;
        // std::cout << "FUCK4\n";
    }
    // std::cout << "FUCK5\n";
    return temp;
}

void Lot::setLot(int ind, Market mar) {
    if (_lotStates[ind].at(0) == Lot_State::LS_free) {
        _lotMarkets[ind] = mar;
        _lotStates[ind][0] = Lot_State::LS_occupied;
    }
}

void Lot::remLot(int ind) {
    if (_lotStates[ind].at(0) == Lot_State::LS_occupied) {
        _lotStates[ind].clear();
        _lotStates[ind].insert(_lotStates[ind].begin(),
            {Lot_State::LS_free, Lot_State::LS_normal});
        _lotMarkets[ind].~Market();
    }
}

void Lot::swapLot(Lot& lot) {
    _lotMarkets.swap(lot._lotMarkets);
    _lotStates.swap(lot._lotStates);
}

void Lot::setState(int ind, Lot_State state) {
    _lotStates[ind].push_back(state);
}

void Lot::remState(int ind, Lot_State state) {
    for (unsigned i = 0; i < _lotStates[ind].size(); i++) {
        if (_lotStates[ind].at(i) == state) {
            _lotStates[ind].erase(_lotStates[ind].begin() + (i - 1));
            return;
        }
    }
}

}  // namespace TR
