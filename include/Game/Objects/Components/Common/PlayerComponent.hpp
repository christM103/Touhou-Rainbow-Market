#pragma once

#include <deque>

#include "Game/Objects/Components/Market/MarketComponent.hpp"
#include "Game/Logic/Player.hpp"

namespace TR {
	struct PlayerComponent {
		Player_Data* player_data{};													// Player Data
		Player_ID player_number;										// Player Index (i.e. Player 1, etc)
		Char_State current_char;										// Character ID
		uint8_t char_type{ 1 };														// Character Type (i.e. Type 1 / Type 2)
		std::deque<Char_State> _player_pathway{  };					// Player's Character Progression Pathway
		std::unique_ptr<Land>* lot_data{};
		std::array<MarketComponent*, 6> player_lot;
		uint8_t market_actions{ 2 };
		uint8_t player_actions{ 1 };

		PlayerComponent(Char_State ch = Char_State::Null, Player_ID id = Player_ID::Player_Null )
			: player_number{id}, current_char{ch} { }
	};
}