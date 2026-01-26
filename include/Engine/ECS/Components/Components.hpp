#pragma once

// Include necessary component headers
#include "Engine/ECS/Components/ColliderComponent.hpp"
#include "Engine/ECS/Components/TransformComponent.hpp"
#include "Engine/ECS/Components/VelocityComponent.hpp"
#include "Engine/ECS/Components/RenderLayerComponent.hpp"
#include "Engine/ECS/Components/SpriteComponent.hpp"
#include "Engine/ECS/Components/TextComponent.hpp"
#include "Engine/ECS/Components/InputComponent.hpp"
#include "Engine/ECS/Components/MouseComponent.hpp"


#include <typeindex>
#include <typeinfo>

namespace Engine {
    using Component = std::type_index;


}