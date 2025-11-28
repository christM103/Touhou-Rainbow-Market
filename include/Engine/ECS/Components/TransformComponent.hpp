#pragma once

#include "Engine/Math/Rect.hpp"
#include "Engine/Math/Vector2.hpp"

namespace Engine {
    struct TransformComponent {
        Vector2f position;
        float rotation; // In degrees
        Vector2f scale;

        TransformComponent() 
            : position(0.0f, 0.0f), rotation(0.0f), scale(1.0f, 1.0f) {}

        TransformComponent(const Vector2f& pos, float rot, const Vector2f& scl)
            : position(pos), rotation(rot), scale(scl) {}
    };
} // namespace Engine