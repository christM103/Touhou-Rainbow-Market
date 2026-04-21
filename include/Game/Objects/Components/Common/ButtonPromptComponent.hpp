#pragma once
#include "Game/Objects/Components/Common/ButtonComponent.hpp"

namespace TR {
	struct ButtonPromptComponent {
		enum Choice : uint8_t {
			NULL_STATE = 0,
			NONE = 0 << 1,
			TRUE = 1 << 1,
			FALSE = 2 << 1
		};

		enum Layout : uint8_t {
			NULL_LAYOUT = 0,
			HORIZONTAL = 0 << 1,
			VERTICAL = 1 << 1,
			CENTER_HORIZONTAL = 2 << 1,
			CENTER_VERTICAL = 3 << 1
		};

		ButtonComponent _buttonTrue{ false }, _buttonFalse{ false };
		Engine::Vector2i position;
		Layout layout;
		

		ButtonPromptComponent(Engine::Vector2i pos = Engine::Vector2i(), Layout l = HORIZONTAL) : position(pos), layout(l) {}

		ButtonPromptComponent(int x = 0, int y = 0, Layout l = HORIZONTAL) {
			ButtonPromptComponent(Engine::Vector2i{ x, y }, l);
		}

	};
}