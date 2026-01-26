// Copyright 2025 chrisfantasy

#pragma once

#include <map>
#include <utility>
#include "Game/Market.hpp"

namespace TR {
    // --- Land Class --- //

class Land{
 public:
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

    // Constructor and Destuctor
     Land();
    ~Land();

    // Accessors and Mutators

    /// @brief Returns the current market stored in the land.
    /// @param ind  The index of the specific piece of land
    /// @return The current market occupied
    Market& getMarket(int ind);

    /// @brief Returns the current market stored in the land as a string
    /// @param ind      The index of the specific piece of land
    /// @return The string market
    const char* getMarketStr(int ind);

    /// @brief Gets a list of all the currently active markets
    /// @return String featuring every market loaded into all lands
    const char* getMarketList();

    /// @brief Sets the size of the sprite.
    /// @param ind      The index of the piece of land
    /// @param state    The state to set
    inline void setState(int ind, Land_States state) { _landMarkets[ind].first ^= state; };

    /// @brief Removes the size of the sprite.
    /// @param ind      The index of the piece of land
    /// @param state    The state to remove
    inline void remState(int ind, Land_States state) { _landMarkets[ind].first &= ~state; };

    /// @brief Sets one portion of land with a market
    /// @param ind      The index of the piece of land
    /// @param mar    The market that is going to be used
    template <class T> inline void setLand(int ind, T&& mar) {
        if (_landMarkets[ind].first & LS_Free) {
            _landMarkets[ind].second = std::make_shared<T>(std::forward<T>(mar));
            _landMarkets[ind].first ^= LS_Free;
        }
    };

    /// @brief Clears the land that currently has a market occupied
    /// @param ind    The index of the piece of land
    void remLand(int ind);

    /// @brief Swaps the current group of land with another group of land
    /// @param lot    The market that is going to be used
    void swapLand(Land& lot);


 private:
     // Market State and Storage
     std::map<int, std::pair<uint64_t, std::shared_ptr<Market>>> _landMarkets {
         {0, {LS_Null, std::make_shared<Market>(MID_Null, 1, 0.00f)}}, 
         {1, {LS_Null, std::make_shared<Market>(MID_Null, 1, 0.00f)}},
         {2, {LS_Null, std::make_shared<Market>(MID_Null, 1, 0.00f)}},
         {3, {LS_Null, std::make_shared<Market>(MID_Null, 1, 0.00f)}},
         {4, {LS_Null, std::make_shared<Market>(MID_Null, 1, 0.00f)}} };

};

}  // namespace TR
