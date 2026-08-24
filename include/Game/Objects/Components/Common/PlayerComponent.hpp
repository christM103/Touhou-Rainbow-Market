#pragma once

#include <deque>

#include "Game/Logic/Player.hpp"

namespace TR {
	struct PlayerComponent {
		std::map<Player_Data::Char_State, std::string> _char_dict{
			{Player_Data::S_Null_Char, "Null"}, {Player_Data::S_Reimu, "Reimu"}, {Player_Data::S_Marisa, "Marisa"}, {Player_Data::S_Sanae, "Sanae"},
			{Player_Data::S_Flandre, "Flandre"}, { Player_Data::S_Youmu, "Youmu"}, {Player_Data::S_Tewi, "Tewi"}, {Player_Data::S_Koishi, "Koishi"} };

		Player_Data* player_data{};													// Player Data
		Player_Data::Player_ID player_number;										// Player Index (i.e. Player 1, etc)
		Player_Data::Char_State current_char;										// Character ID
		uint8_t char_type{ 1 };														// Character Type (i.e. Type 1 / Type 2)
		std::deque<Player_Data::Char_State> _player_pathway{  };					// Player's Character Progression Pathway

		PlayerComponent(Player_Data::Char_State ch = Player_Data::S_Null_Char, Player_Data::Player_ID id = Player_Data::PI_Player_Null )
			: player_number{id}, current_char{ch} { }
	};
}