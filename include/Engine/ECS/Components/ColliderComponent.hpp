#pragma once

#include "Engine/Math/Rect.hpp"
#include "Engine/Math/Vector2.hpp"

namespace Engine {
    struct ColliderComponent {
        Rect<float> bounds;
        Vector2<float> offset;

        ColliderComponent(const Rectf& rect = Rectf(), const Vector2f& off = Vector2f())
            : bounds(rect), offset(off) {}
    };
} // namespace Engine