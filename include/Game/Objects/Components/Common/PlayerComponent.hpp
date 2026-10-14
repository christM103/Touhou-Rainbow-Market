#pragma once

#include <deque>

#include "Game/Logic/Player.hpp"

namespace TR {
	struct PlayerComponent {
		std::map<Char_State, std::string> _char_dict{
			{Char_State::Null, "Null"}, {Char_State::Reimu, "Reimu"}, {Char_State::Marisa, "Marisa"}, {Char_State::Sanae, "Sanae"},
			{Char_State::Flandre, "Flandre"}, { Char_State::Youmu, "Youmu"}, {Char_State::Tewi, "Tewi"}, {Char_State::Koishi, "Koishi"} };

		Player_Data* player_data{};													// Player Data
		Player_ID player_number;										// Player Index (i.e. Player 1, etc)
		Char_State current_char;										// Character ID
		uint8_t char_type{ 1 };														// Character Type (i.e. Type 1 / Type 2)
		std::deque<Char_State> _player_pathway{  };					// Player's Character Progression Pathway
		uint8_t market_actions = 2;
		uint8_t player_actions = 1;

		PlayerComponent(Char_State ch = Char_State::Null, Player_ID id = Player_ID::Player_Null )
			: player_number{id}, current_char{ch} { }
	};
}