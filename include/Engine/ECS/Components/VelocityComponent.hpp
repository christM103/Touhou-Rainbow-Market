#pragma once

#include "Engine/Math/Rect.hpp"
#include "Engine/Math/Vector2.hpp"

namespace Engine {
    struct VelocityComponent {
        Vector2f linear;
        float angular; // In degrees
        Vector2f scalar;
        float deltaTime; // In seconds

        VelocityComponent()
            : linear(0.0f, 0.0f), angular(0.0f), scalar(0.0f, 0.0f), deltaTime(0.0f) {
        }

        VelocityComponent(const Vector2f& lin, float ang, const Vector2f& scl, float t)
            : linear(lin), angular(ang), scalar(scl), deltaTime(t) {
        }
    };
} // namespace Engine