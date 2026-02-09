#pragma once

#include <functional>
#include <unordered_map>

namespace Engine {
	using Keycode = uint16_t;

	struct KeyComponent {
		Keycode key{ 0 };
		bool isPressed{ false };
		bool isHeld{ false };
		bool isReleased{ false };

		KeyComponent(Keycode key = 0) : key(key) {}
	};

	struct InputComponent {
		std::unordered_map<Keycode, KeyComponent*>  scancode;

		void newKey(Keycode key) {
			scancode.emplace(key, nullptr);
		}

		bool keyPressed(Keycode key) {
			if (scancode.find(key) != scancode.end()) {
				return scancode.at(key)->isPressed;
			}
			return false;
		}

		bool keyHeld(Keycode key) {
			if (scancode.find(key) != scancode.end()) {
				return scancode.at(key)->isHeld;
			}
			return false;
		}

		bool keyReleased(Keycode key) {
			if (scancode.find(key) != scancode.end()) {
				return scancode.at(key)->isReleased;
			}
			return false;
		}
	};

	struct KeyboardComponent {
		Keycode* key{ nullptr };
	};
}