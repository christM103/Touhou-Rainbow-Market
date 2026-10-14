// Copyright 2025 chrisfantasy

#pragma once

#include <map>
#include <utility>
#include "Game/Logic/Market.hpp"

namespace TR {

enum class Land_ID : uint8_t {
    Land_1, Land_2, Land_3, Land_4, Land_5, Land_6, Land_Null = 255
};

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
    Market* getMarket(int ind);

    /// @brief Gets a list of all the currently active markets
    /// @return String featuring every market loaded into all lands
    std::string getMarketList();

    /// @brief Sets the size of the sprite.
    /// @param ind      The index of the piece of land
    /// @param state    The state to set
    inline void setState(int ind, uint64_t state) { _landMarkets[ind].first |= state; };

    /// @brief Removes the size of the sprite.
    /// @param ind      The index of the piece of land
    /// @param state    The state to remove
    inline void remState(int ind, uint64_t state) { _landMarkets[ind].first &= ~state; };

    /// @brief Sets one portion of land with a market
    /// @param ind      The index of the piece of land
    /// @param mar    The market that is going to be used
    inline void setLand(int ind, Market&& mar) {
        if (_landMarkets[ind].first & LS_Free) {
            _landMarkets[ind].second = std::make_unique<Market>(std::forward<Market>(mar));
            _landMarkets[ind].first ^= LS_Free;
        }
    };

    /// @brief Clears the land that currently has a market occupied
    /// @param ind    The index of the piece of land
    void remLand(int ind);

    /// @brief Swaps the current group of land with another group of land
    /// @param lot    The market that is going to be used
    void swapLand(Land& lot);
    
    /// @brief Gets a list of all the currently free pieces of land
    /// @return Vector containing the list of free land indices
    const std::vector<uint8_t> availableLand();


 private:
     // Market State and Storage
     std::map<uint8_t, std::pair<uint64_t, std::unique_ptr<Market>>> _landMarkets { };

};

}  // namespace TR
