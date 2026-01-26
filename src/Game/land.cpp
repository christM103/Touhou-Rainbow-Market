// Copyright 2025 chrisfantasy

#include "Game/Land.hpp"

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

const char* Land::getMarketStr(int ind) {
    return _landMarkets.at(ind).second.get()->getIDStr();
}

const char* Land::getMarketList() {
    std::string temp;

    for (auto const& i : _landMarkets) {
        temp += i.second.second.get()->getIDStr();
        temp += " ";
    }

    return temp.c_str();
}



void Land::remLand(int ind) {
    constexpr uint16_t Land_States_Reimu = LS_Reimu_Orb | LS_Reimu_TalisA | LS_Reimu_TalisB;
    constexpr uint16_t Land_States_Chars = Land_States_Reimu;

    if (_landMarkets[ind].first & ~LS_Free) {
        _landMarkets[ind].second.reset();
        _landMarkets[ind].first &= ~(Land_States_Chars | LS_Immunity | LS_Active);
    }
}

void Land::swapLand(Land& land) {
    _landMarkets.swap(land._landMarkets);
}


}  // namespace TR
