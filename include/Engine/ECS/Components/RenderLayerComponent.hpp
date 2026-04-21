#pragma once

#include <cstdint>

namespace Engine {
	struct RenderLayerComponent {
		uint16_t layer;

		RenderLayerComponent(uint16_t l = 10) : layer(l) {}

		enum Layers : uint16_t {
			BG = 10,

			SPRITE = 50,

			FG = 100,
			TEXTBOX = 400,

			HUD = 1000,
		};
	};
} // namespace Engine