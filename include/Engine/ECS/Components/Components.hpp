#pragma once

#include <utility>
#include <tuple>

// Include necessary component headers
#include "Engine/ECS/Components/ColliderComponent.hpp"
#include "Engine/ECS/Components/TransformComponent.hpp"
#include "Engine/ECS/Components/SpriteComponent.hpp"
#include "Engine/ECS/Components/TextComponent.hpp"
#include "Engine/ECS/Components/InputComponent.hpp"
#include "Engine/ECS/Components/MouseComponent.hpp"

namespace Engine {
	template <typename... Components>
	struct ComponentGroup {
		std::tuple<Components...> components;

		ComponentGroup() = default;

		explicit ComponentGroup(Components... comp) 
			: components(std::move(comp)...){}
	};
}