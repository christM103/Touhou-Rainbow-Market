#pragma once

#include <cstdint>
#include "Game/Logic/Player.hpp"

namespace TR {
	struct SelectComponent {
		std::map<Char_State, std::string> _char_dict{
			{Char_State::Null, "Null"}, {Char_State::Reimu, "Reimu"}, {Char_State::Marisa, "Marisa"}, {Char_State::Sanae, "Sanae"},
			{Char_State::Flandre, "Flandre"}, { Char_State::Youmu, "Youmu"}, {Char_State::Tewi, "Tewi"}, {Char_State::Koishi, "Koishi"} };

		Char_State _current_selected{ Char_State::Reimu };
	};
}