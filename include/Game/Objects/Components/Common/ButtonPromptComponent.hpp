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

		ButtonComponent True, False;

	};
}