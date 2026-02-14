// Copyright 2025 chrisfantasy

#include "Game/Logic/Market.hpp"


namespace TR {

Market::Market() {}

Market::Market(int tier, float sell) : _market_tier(tier), _market_sell(sell) {}

Market::~Market() {}

float Market::marketSell() {
    return _market_sell;
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

}  // namespace TR
