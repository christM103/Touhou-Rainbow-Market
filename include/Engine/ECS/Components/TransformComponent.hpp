#pragma once

#include "Engine/Math/Rect.hpp"
#include "Engine/Math/Vector2.hpp"

namespace Engine {
    struct TransformComponent {
        Vector2i position;
        float rotation; // In degrees
        Vector2f scale;
        bool centered;

        TransformComponent(const Vector2i& pos = Vector2i(0,0), float rot = 0.0f, const Vector2f& scl = Vector2f(1.0f, 1.0f), bool cnt = false)
            : position(pos), rotation(rot), scale(scl), centered(cnt) {}

        // Comparison operators

        bool operator==(const TransformComponent& r2) const {
            return ((position == r2.position) && (rotation == r2.rotation) && (scale == r2.scale));
        }
        bool operator!=(const TransformComponent& r2) const {
            return !(*this == r2);
        }

    };
} // namespace Engine