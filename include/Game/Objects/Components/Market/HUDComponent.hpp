#pragma once

#include <cstdint>
#include "Game/Logic/Common.hpp"

namespace TR{
	struct HUDComponent {
		bool isHUDEnabled{ false };
		HUD_Flags hudFlags{ HUD_Flags::Null };
		Land_ID highlightedLand{ Land_ID::Land_Null };
	};
}