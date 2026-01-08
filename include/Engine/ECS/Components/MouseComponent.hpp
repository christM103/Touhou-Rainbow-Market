#pragma once

#include <functional>

#include "Engine/Math/Vector2.hpp"

namespace Engine {

	class MouseComponent {
	public:
		MouseComponent() : position(0, 0), button( 0 ), state( 0 ) {}
		~MouseComponent() = default;

		MouseComponent(const Vector2<int>& pos, Uint8 but, Uint8 st) 
			: position(pos), button(but), state(st) {}

		/// @brief When the mouse is on the entity.
		std::function<void()> onMove;
		/// @brief When the mouse was pressed on the entity.
		std::function<void()> onClick;
		/// @brief When the entity was held on by the mouse.
		std::function<void()> onHeld;
		/// @brief When the entity was released by the mouse.
		std::function<void()> onReleased;

	private:
		Vector2<int> position;	// x & y mouse position
		Uint8 button;			// mouse button
		Uint8 state;			// held, released, clicked
	};
}