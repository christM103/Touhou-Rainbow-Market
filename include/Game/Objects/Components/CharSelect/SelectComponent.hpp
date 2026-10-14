#pragma once

#include <cstdint>
#include "Game/Logic/Player.hpp"

namespace TR {
	struct SelectComponent {
		Char_State _current_selected{ Char_State::Reimu };
	};
}