#pragma once
#include "Game/Objects/Components/Common/ButtonComponent.hpp"

namespace TR {
	struct ButtonPromptComponent {
		enum choice : uint8_t {
			NULL_STATE = 0,
			NONE = 0 << 1,
			TRUE = 1 << 1,
			FALSE = 2 << 1
		};

		ButtonComponent _buttonTrue{ false }, _buttonFalse{ false };
		Engine::Vector2i position;

		ButtonPromptComponent(Engine::Vector2i pos = Engine::Vector2i()) : position(pos) {}

		ButtonPromptComponent(int x = 0, int y = 0) {
			ButtonPromptComponent(Engine::Vector2i{ x, y });
		}

	};
}