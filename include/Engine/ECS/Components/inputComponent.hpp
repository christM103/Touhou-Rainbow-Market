#pragma once

#include <functional>
#include <unordered_map>

namespace Engine {
	struct KeyComponent {
		uint8_t key{ 0 };
		bool isPressed{ false };
		bool isHeld{ false };
		bool isReleased{ true };
	};

	struct InputComponent {
		std::unordered_set<KeyComponent>  scancode;
	};
}