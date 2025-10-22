// Copyright 2025 chrisfantasy

#pragma once

#include <vector>
#include <string>

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

enum Market_ID{MID_Null, MID_Wriggle, MID_Kisume, MID_Kogasa, MID_Nazrin};
static const std::string Market_ID_Str[] = {"MID_Null", "MID_Wriggle", "MID_Kisume", "MID_Kogasa", "MID_Nazrin"};

class Market{
 public:
    // Constructor and Destuctor
    Market();
    Market(int id, int tier, float sell);
    ~Market();

    // Accessors and Mutators
    inline int getID() { return _market_id; };
    inline int getLevel() { return _market_lvl; };
    inline int getTier() { return _market_tier; };
    inline std::string getType() { return _market_type; };
    inline float getSellPrice() { return _market_sell; };
    inline void setID(int id) { _market_id = id; };
    inline void setLevel(int lvl) { _market_lvl = lvl; };
    inline void setTier(int tier) { _market_tier = tier; };
    inline void setSellPrice(float sell) { _market_sell = sell; };

    // Other Functions
    float marketSell();
    void marketLvlUp();
    virtual float marketProfit();

 protected:
    int _market_id{MID_Null}, _market_lvl{1}, _market_tier{1};
    float _market_sell{0}, _market_profit{0};
    std::string _market_type{"Null"};
};

std::string& operator<<(std::string& str, Market& market);

class Wriggle : public Market {
 public:
    Wriggle();
    void wriggleSell(Market other);
    float marketProfit();
 private:
    float _wrig_sell{0};
};

}  // namespace TR
