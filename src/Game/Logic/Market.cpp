// Copyright 2025 chrisfantasy

#include "Game/Logic/Market.hpp"
#include <algorithm>
#include <yaml-cpp/yaml.h>


namespace TR {

Market::Market() {}

Market::Market(Market_ID id) {
    auto isMarket = [&](YAML::detail::iterator_value item) {return marketStrToID.at(item["ID"].as<std::string>()) == id;};
    _market_ID = id;

    YAML::Node market_data = YAML::LoadFile("assets/text/markets.yaml");                                                            // Replace literal with global variable for the location of the folder
    if (auto result = std::find_if(market_data.begin(), market_data.end(), isMarket); result != market_data.end()) {
        _market_name = (*result)["name"].as<std::string>();
        _market_bio = (*result)["bio"].as<std::string>();
        _market_tier = (*result)["tier"].as<int>();
        _market_profit = (*result)["profit"].as<float>();
        _market_sell = (*result)["sell"].as<float>();
    }

}

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
