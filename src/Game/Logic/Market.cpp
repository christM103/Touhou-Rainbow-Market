// Copyright 2025 chrisfantasy

#include "Game/Logic/Market.hpp"


namespace TR {

Market::Market() {}

Market::Market(Market_ID id) {
    auto isMarket = [&](YAML::detail::iterator_value item) {return MarketStrToID(item["ID"].as<std::string>()) == id;};
    _market_ID = id;

    YAML::Node market_data = YAML::LoadFile(PATH_JSON_MARKET);                                                            // Replace literal with global variable for the location of the folder
    for (const auto& market : market_data) {
        if (static_cast<Market_ID>(market["id"].as<int>()) == id) {
            _market_name = market["name"].as<std::string>();
            _market_bio = market["bio"].as<std::string>();
            _market_tier = market["tier"].as<int>();
            _market_profit = market["profit"].as<float>();
            _market_sell = market["sell"].as<float>();
            return;
        }
        
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
