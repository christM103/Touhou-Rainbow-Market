#pragma once

#include "Game/Logic/Market.hpp"

namespace TR {
	struct MarketComponent {
		Market* data{ nullptr };
		Market_ID market_ID{ Market_ID::MID_Null };

        MarketComponent(Market* d = nullptr, Market_ID id = Market_ID::MID_Null) : data(d), market_ID(id){}
        /*
        std::string& operator<<(std::string& str, MarketComponent& market) {
            std::stringstream temp;
            temp << "Market ID: " << Market_ID_Str[market.getID()] << "\n";
            temp << "Market Lvl: " << market.getLevel() << "\n";
            temp << "Market Tier: " << market.getTier() << "\n";
            temp << "Market Sell Price: " << market.getSellPrice() << "\n";
            temp << "Market Type: " << market.getType() << "\n\n";
            str += temp.str();
            return str;
        }
        */
	};
}