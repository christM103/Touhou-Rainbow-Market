#pragma once

#include <Engine/ECS/System/BaseSystem.hpp>

namespace Engine {
	class InputSystem() {
	public:

		InputSystem() = default;

		void init();

		// Overloaded functions

		void create(const SystemContext & ctx);

		void update(const SystemContext & ctx);

		void render(const SystemContext & ctx);

		void quit(const SystemContext & ctx);
	private:

	}
}