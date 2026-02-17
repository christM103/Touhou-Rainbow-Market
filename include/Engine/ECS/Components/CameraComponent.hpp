#include "Engine/Math/Rect.hpp"
#include "Engine/Math/Vector2.hpp"

namespace Engine {
	struct CameraComponent {
		Recti position;
		Vector2f scale;

		CameraComponent(Recti pos = Recti(), Vector2f sc = Vector2f()) : position(pos), scale(sc) {}
	};
}