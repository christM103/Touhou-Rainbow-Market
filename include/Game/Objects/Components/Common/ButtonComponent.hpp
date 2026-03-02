#pragma once
#include "Engine/Math/Vector2.hpp"

namespace TR {
	struct ButtonComponent {
		Engine::Vector2i position;
		bool activated;
	};
}