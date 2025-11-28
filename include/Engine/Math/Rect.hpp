#pragma once
#include "Vector2.hpp"

namespace Engine {

template<typename T>
struct Rect {
    // Ensure T is an arithmetic type
    static_assert(std::is_arithmetic<T>::value, "Rect requires an arithmetic type");

    Vector2<T> position;
    Vector2<T> size;

    constexpr Rect() : position(0, 0), size(0, 0) {}
    constexpr Rect(T x, T y, T width, T height) : position(x, y), size(width, height) {}

    // Utility functions

    /// @brief Checks if a point is inside the rectangle.
    /// @param point The point to check.
    /// @return True if the point is inside the rectangle, false otherwise.
    bool contains(const Vector2<T>& point) const {
        return point.x >= position.x && point.x < position.x + size.x &&
               point.y >= position.y && point.y < position.y + size.y;
    }
};

using Recti = Rect<int>;
using Rectf = Rect<float>;
using Rectu = Rect<unsigned int>;

} // namespace Engine