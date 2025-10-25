// Copyright 2025 chrisfantasy

#pragma once

#include <map>
#include <utility>
#include "Game/market.hpp"

namespace TR {

// --- Land States --- //

enum Land_States : uint64_t {
    LS_Null = 0,                             // (Null)
    LS_Free = 1 << 0,                        // (Free or Occupied)
    LS_Active = 1 << 1,                      // (Active or Shut Down)
    LS_Immunity = 1 << 2,                    // (Land Immunity)
    LS_Reimu_Orb = 1 << 3,                   // (Reimu Orb protection)
    LS_Reimu_TalisA = 1 << 4,                // (Reimu Talisman A (Seal), Shut down a select open market for 2 turns
    LS_Reimu_TalisB = 1 << 5,                // (Reimu Talisman B (Barrier), Grant immunity to a select open market for 2 turns
};

constexpr uint64_t Land_States_Reimu = LS_Reimu_Orb | LS_Reimu_TalisA | LS_Reimu_TalisB;
constexpr uint64_t Land_States_Chars = Land_States_Reimu;

// --- Land Class --- //

class Land{
 public:
    // Constructor and Destuctor
     Land();
    ~Land();

    // Accessors and Mutators
    Market& getMarket(int ind);
    std::string getMarketList();
    inline void setState(int ind, Land_States state) { _landMarkets[ind].first ^= state; };
    inline void remState(int ind, Land_States state) { _landMarkets[ind].first &= ~state; };
    void setLand(int ind, Market&& mar);
    void remLand(int ind);
    void swapLand(Land& lot);


 private:
     // Market State and Storage
     std::map<int, std::pair<uint64_t, std::shared_ptr<Market>>> _landMarkets {
         {1, {LS_Null, std::make_shared<Market>(MID_Null, 1, 0)}}, 
         {2, {LS_Null, std::make_shared<Market>(MID_Null, 1, 0)}},
         {3, {LS_Null, std::make_shared<Market>(MID_Null, 1, 0)}},
         {4, {LS_Null, std::make_shared<Market>(MID_Null, 1, 0)}},
         {5, {LS_Null, std::make_shared<Market>(MID_Null, 1, 0)}} };

};

}  // namespace TR
