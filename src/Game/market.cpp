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

int Market::getID() {
    return _market_id;
}

int Market::getLevel() {
    return _market_lvl;
}

int Market::getTier() {
    return _market_tier;
}

std::string Market::getType() {
    return _market_type;
}

float Market::getSellPrice() {
    return _market_sell;
}

void Market::setID(int id) {
    _market_id = id;
}

void Market::setLevel(int lvl) {
    _market_lvl = lvl;
}

void Market::setTier(int tier) {
    _market_tier = tier;
}

void Market::setSellPrice(float sell) {
    _market_sell = sell;
}

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
