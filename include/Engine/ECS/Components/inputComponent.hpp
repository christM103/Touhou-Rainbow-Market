#pragma once

namespace Engine {
	class InputComponent {
	public:
		InputComponent() : scancode() {};
		~InputComponent() = default;

	private:
		Uint16 scancode;
	};
}