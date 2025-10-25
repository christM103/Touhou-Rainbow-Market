// Copyright 2025 chrisfantasy

#include "Game/land.hpp"

namespace TR {

Land::Land() {
    for (uint8_t x = 0; x < 5; x++) {
        _landMarkets[x].first ^= LS_Free;
    }
}

Land::~Land() {}

Market& Land::getMarket(int ind) {
    return *_landMarkets.at(ind).second.get();
}

std::string Land::getMarketList() {
    std::string temp;

    for (auto i : _landMarkets) {
        temp += i.second.second.get()->getIDStr();
        temp += " ";
    }

    return temp;
}

void Land::setLand(int ind, Market&& mar) {
    if (_landMarkets[ind].first & LS_Free) {
        //_landMarkets[ind].second.swap(std::make_shared<Market>(std::move(mar)));
        _landMarkets[ind].first ^= LS_Free;
    }
}

void Land::remLand(int ind) {
    if (_landMarkets[ind].first & !LS_Free) {
        _landMarkets[ind].second.reset();
        _landMarkets[ind].first &= ~(Land_States_Chars | LS_Immunity | LS_Active);
    }
}

void Land::swapLand(Land& land) {
    _landMarkets.swap(land._landMarkets);
}


}  // namespace TR
