// Copyright 2025 chrisfantasy

#pragma once

#include "Game/Logic/Common.hpp"

/*
For context ~
Every turn, each player is bombarded with 3 pop-ups of 3 different tiers starting at tier 1 on turn 1, that can be viewed in order to choose between 2 different open markets. 
Whichever open market is chosen is placed on an empty lot of the players choosing. 
If you chose not to construct an open market, gain $50,000. You can sell open markets to free up that space again. 
If you're using all your lots you will receive higher tiered market pop-ups in addition to ones in your tier. Every 3 turns, the tier of open markets for sale increases by 1 permanently. 
Open market Max levels vary based on individual market effect (generally max lvl 5).

(Tier 1 - low cost, minimal profit output, minimal effects. Tier 2 - medium cost, high profit output, ok effects. Tier 3 - High cost, low profit output, amazing effects) 


Open markets can inflict a whole heap of buffs, debuffs, aliments and the like. Whether they are character specific or general, open markets will always follow these rules:

    Shut Down - Targeted open market(s) do not generate profit at the end of turn.
    Immunity - Open markets cannot be affected by any of the effects that would target them.
    Profit Rates - Targeted open market(s) in play have the profits you would gain this turn altered by the multiplier listed in the effect.
    Sell - Cost effect that targets an open market you control and removes it from play, you do not receive profit from this open market.
    Destroy - Target open market anywhere on field and remove it from play, the owner of this open market does not receive profit from this open market.
    Negate - Target the activation of a targeted skill, if you do the activation of that skill is null & void.


*/

// TODO: Use nested getters & setters, replace enums

namespace TR {

enum class Market_ID : uint8_t {MID_Null, MID_Myst, MID_Koga, MID_Wrig, MID_Kein, MID_Suwa, MID_Rema};

class Market{
 public:
    // Constructor and Destuctor
    Market();
    Market(Market_ID id);
    ~Market();

    // Accessors and Mutators
    inline const int getLevel() { return _market_lvl; };
    inline std::string getName() { return _market_name; }
    inline const int getTier() { return _market_tier; };
    inline const float getSellPrice() { return _market_sell; };
    inline void setLevel(int lvl) { _market_lvl = lvl; };
    inline void setTier(int tier) { _market_tier = tier; };
    inline void setSellPrice(float sell) { _market_sell = sell; };

    inline static constexpr Market_ID marketStrToID(std::string str) {
        if (str == "MID_Null") {return Market_ID::MID_Null;}
        else if (str == "MID_Myst") { return Market_ID::MID_Myst; }
        else if (str == "MID_Koga") { return Market_ID::MID_Koga; }
        else if (str == "MID_Wrig") { return Market_ID::MID_Wrig; }
        else if (str == "MID_Kein") { return Market_ID::MID_Kein; }
        else if (str == "MID_Suwa") { return Market_ID::MID_Suwa; }
        else if (str == "MID_Rema") { return Market_ID::MID_Rema; }

        return Market_ID::MID_Null;
    }
    

    // Other Functions
    void marketReset();
    virtual float marketSell();
    void marketLvlUp();
    virtual float marketProfit();

 private:
     Market_ID _market_ID{ Market_ID::MID_Null };
     std::string _market_name{ "Null Market" }, _market_bio{ "" };
    int _market_lvl{1}, _market_tier{1};
    float _market_sell{0.0}, _market_profit{0};
    
};

}  // namespace TR
