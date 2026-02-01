#pragma once

#include "Engine/ECS/System/BaseSystem.hpp"

namespace TR {
	class TextboxSystem {
        enum Text_Box_Transitions : uint16_t {
            TXT_NULL = 0,
            TXT_ACTIVE_TRANSITION = 1 << 0,
            TXT_VERTICAL_TRANSITION = 1 << 1,
            TXT_HORIZONTAL_TRANSITION = 1 << 2,
            TXT_CONST_VELOCITY = 1 << 3,
            TXT_ACTIVE_TEXT = 1 << 4,
            TXT_ACTIVE_TEXT_COMPLETE = 1 << 5,
            TXT_ENTER_EXIT = 1 << 6,
            TXT_PROMPT_COMFIRM = 1 << 7,
            TXT_PROMPT_TEXT = 1 << 8,
        };
	public:

	private:

	};
}