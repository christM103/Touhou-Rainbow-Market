#pragma once

#include <deque>

#include "Game/Logic/Player.hpp"

namespace TR {
	struct PlayerComponent {
		Player_Data* player_data{};													// Player Data
		Player_Data::Player_ID player_number;										// Player Index (i.e. Player 1, etc)
		Player_Data::Char_State current_char;										// Character ID
		uint8_t char_type{ 1 };														// Character Type (i.e. Type 1 / Type 2)
		std::deque<Player_Data::Char_State> _player_pathway{  };					// Player's Character Progression Pathway

		PlayerComponent(Player_Data::Char_State ch = Player_Data::S_Null_Char, Player_Data::Player_ID id = Player_Data::PI_Player_Null )
			: player_number{ch}, current_char{id} { }
	};
}