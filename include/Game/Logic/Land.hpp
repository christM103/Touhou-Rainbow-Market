// Copyright 2025 chrisfantasy

#pragma once

#include "Game/Logic/Market.hpp"
#include "Game/Logic/Common.hpp"

namespace TR {

    // --- Land Class --- //

class Land{
 public:

    // Constructor and Destuctor
     Land();
    ~Land();

    // Accessors and Mutators

    /// @brief Returns the current market stored in the land.
    /// @param ind  The index of the specific piece of land
    /// @return The current market occupied
    Market* getMarket(Land_ID ind);

    /// @brief Gets a list of all the currently active markets
    /// @return String featuring every market loaded into all lands
    std::string getMarketList();

    /// @brief Sets one portion of land with a market
    /// @param ind      The index of the piece of land
    /// @param mar    The market that is going to be used
    inline void setLand(Land_ID ind, Market&& mar) {
        if (has_flag(_landMarkets[ind].first, Land_States::Free)) {
            _landMarkets[ind].second = std::make_unique<Market>(std::forward<Market>(mar));
            disable_flag(_landMarkets[ind].first, Land_States::Free);
        }
    };

    /// @brief Clears the land that currently has a market occupied
    /// @param ind    The index of the piece of land
    void remLand(Land_ID ind);

    /// @brief Swaps the current group of land with another group of land
    /// @param lot    The market that is going to be used
    void swapLand(Land& lot);
    
    /// @brief Gets a list of all the currently free pieces of land
    /// @return Vector containing the list of free land indices
    const std::vector<Land_ID> availableLand();


 private:
     // Market State and Storage
     std::unordered_map<Land_ID, std::pair<Land_States, std::unique_ptr<Market>>> _landMarkets { };

};

}  // namespace TR
