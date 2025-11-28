#pragma once

#include "Engine/Math/Rect.hpp"
#include "Engine/Math/Vector2.hpp"

namespace Engine {
    struct ColliderComponent {
        Rect<float> bounds;
        Vector2<float> offset;

        ColliderComponent() : bounds(0, 0, 0, 0), offset(0, 0) {}
        ColliderComponent(const Rect<float>& rect, const Vector2<float>& off)
            : bounds(rect), offset(off) {}
    };
} // namespace Engine