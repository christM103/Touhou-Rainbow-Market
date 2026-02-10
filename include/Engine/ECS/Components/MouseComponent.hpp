#pragma once

#include "Engine/Math/Vector2.hpp"

namespace Engine {

	struct MouseButton {
		bool isPressed{ false };
		bool isHeld{ false };
		bool isReleased{ false };
	};

	struct MouseComponent {
		Vector2<int>* position;								// x & y mouse position
		MouseButton* buttonL, *buttonR, *buttonM;			// mouse button

		bool leftPressed() {
			if (buttonL) {
				return buttonL->isPressed;
			}
			return false;
		}

		bool leftHeld() {
			if (buttonL) {
				return buttonL->isHeld;
			}
			return false;
		}

		bool leftReleased() {
			if (buttonL) {
				return buttonL->isReleased;
			}
			return false;
		}
	};
}