#pragma once

#include "Engine/Math/Vector3.hpp"

namespace Engine {
	struct ColorComponent {
		Vector3<uint8_t> rgb{ 255, 255, 255};
		uint8_t alpha{ 255 };
		bool color_overlay{ false };

		ColorComponent(Vector3<uint8_t> c = {255, 255, 255}, uint8_t a = 255, bool over = false) : rgb(c), alpha(a), color_overlay(over) {}

		bool operator==(const ColorComponent& v3) const {
			return rgb == v3.rgb && alpha == v3.alpha && color_overlay == v3.color_overlay;
		}
	};
}