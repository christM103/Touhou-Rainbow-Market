#pragma once

#include <vector>
#include <memory>

#include "Engine/ECS/ComponentManager.hpp"
#include "Engine/ECS/EntityManager.hpp"
#include "Engine/Input/Input.hpp"
#include "Engine/Graphics/AssetManager.hpp"
#include "Engine/Graphics/Window.hpp"

namespace Engine {
	using System = std::type_index;

	struct SystemContext {
		EntityManager* entityManager{ nullptr };
		ComponentManager* componentManager{ nullptr };
		AssetManager* assetManager{ nullptr };
		Input* input{ nullptr };
		Window* window{ nullptr };
	};

}