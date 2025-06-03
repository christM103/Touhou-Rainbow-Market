// Copyright 2025 chrisfantasy

#include "../../include/market.hpp"

namespace TR {

Wriggle::Wriggle() : Market() {
    this->_market_id = MID_Wriggle;
    this->_market_sell = 50000;
    this->_market_lvl = 1;
    this->_market_tier = 1;
    this->_market_type = "Striker";
    this->_market_profit = 10000;
}

float Wriggle::marketProfit() {
    return _market_profit + _wrig_sell;
}

void Wriggle::wriggleSell(Market other) {
    _wrig_sell += other.marketSell();
}

}  // namespace TR
