// Copyright 2025 chrisfantasy

#include "Game/Logic/Land.hpp"

namespace TR {

Land::Land() {
    for (uint8_t index = 0; index < 6; index++) {
        _landMarkets.emplace(static_cast<Land_ID>(index), std::pair(Land_States::Free, std::make_unique<Market>()));
    }
}

Land::~Land() {}

Market* Land::getMarket(Land_ID ind) {
    return _landMarkets.at(ind).second.get();
}

std::string Land::getMarketList() {
    std::string temp;

    for (auto const& i : _landMarkets) {
        temp += i.second.second->getName();
        temp += " | ";
    }

    return temp;
}



void Land::remLand(Land_ID ind) {
    if (has_flag(_landMarkets[ind].first, ~Land_States::Free)) {
        _landMarkets[ind].second.reset();
        _landMarkets[ind].first = Land_States::Free;
    }
}

void Land::swapLand(Land& land) {
    _landMarkets.swap(land._landMarkets);
}

const std::vector<Land_ID> Land::availableLand() {
    std::vector<Land_ID> available_land{};

    for (auto& ind : _landMarkets) {
        if (has_flag(ind.second.first, Land_States::Free)) {
            available_land.push_back(ind.first);
        }
    }

    return available_land;
}


}  // namespace TR
