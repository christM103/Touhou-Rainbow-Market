#pragma once

#include <cstdint>
#include "Game/Logic/Player.hpp"

namespace TR {
	struct SelectComponent {
		std::map<Player_Data::Char_State, std::string> _char_dict{
			{Player_Data::S_Null_Char, "Null"}, {Player_Data::S_Reimu, "Reimu"}, {Player_Data::S_Marisa, "Marisa"}, {Player_Data::S_Sanae, "Sanae"},
			{Player_Data::S_Flandre, "Flandre"}, { Player_Data::S_Youmu, "Youmu"}, {Player_Data::S_Tewi, "Tewi"}, {Player_Data::S_Koishi, "Koishi"} };

		Player_Data::Char_State _current_selected{ Player_Data::S_Reimu };
	};
}