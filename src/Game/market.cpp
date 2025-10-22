// Copyright 2025 chrisfantasy
#include "Game/market.hpp"
#include <vector>
#include <iostream>
#include <sstream>
#include <string>

namespace TR {

Market::Market() {}

Market::Market(int id, int tier, float sell) :
    _market_id(id), _market_tier(tier), _market_sell(sell) {}

Market::~Market() {}

float Market::marketSell() {
    if (this->_market_id != MID_Null) {
        float sell = _market_sell;
        *this = Market();
        return sell;
    }
    return 0;
}

void Market::marketLvlUp() {
    if (_market_lvl < 5) {
        _market_lvl++;
        _market_sell *= 1.25;
    }
}

float Market::marketProfit() {
    return _market_profit;
}

std::string& operator<<(std::string& str, Market& market) {
    std::stringstream temp;
    temp << "Market ID: " << Market_ID_Str[market.getID()] << "\n";
    temp << "Market Lvl: " << market.getLevel() << "\n";
    temp << "Market Tier: " << market.getTier() << "\n";
    temp << "Market Sell Price: " << market.getSellPrice() << "\n";
    temp << "Market Type: " << market.getType() << "\n\n";
    str += temp.str();
    return str;
}

}  // namespace TR
