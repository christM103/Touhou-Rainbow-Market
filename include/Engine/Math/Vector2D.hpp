#pragma once
#include <cmath>
#include <type_traits>
#include <ostream>

namespace Engine {

template<typename T>
struct Vector2 {
    static_assert(std::is_arithmetic<T>::value, "Vector2 requires an arithmetic type");

    T x;
    T y;

    constexpr Vector2() : x(0), y(0) {}
    constexpr Vector2(T x, T y) : x(x), y(y) {}


    // Arithmetic operators
    constexpr Vector2 operator+(const Vector2& v2) const noexcept{
        return Vector2(x + v2.x, y + v2.y);
    }
    constexpr Vector2 operator-(const Vector2& v2) const noexcept {
        return Vector2(x - v2.x, y - v2.y);
    }
    constexpr Vector2 operator*(T scalar) const noexcept {
        return Vector2(x * scalar, y * scalar);
    }
    constexpr Vector2 operator/(T scalar) const noexcept {
        return Vector2(x / scalar, y / scalar);
    }


    // Arithmetic assignment operators

    /// @brief Adds anv2 vector to this vector.
    /// @param v2 The vector to add.
    Vector2& operator+=(const Vector2& v2) {
        x += v2.x;
        y += v2.y;
        return *this;
    }
    Vector2& operator-=(const Vector2& v2) {
        x -= v2.x;
        y -= v2.y;
        return *this;
    }
    Vector2& operator*=(T scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }
    Vector2& operator/=(T scalar) {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    // Comparison operators
    
    bool operator==(const Vector2& v2) const {
        return x == v2.x && y == v2.y;
    }
    bool operator!=(const Vector2& v2) const {
        return !(*this == v2);
    }


    // Utility functions

    /// @brief Calculates the magnitude (length) of the vector.
    /// @return The magnitude of the vector.
    float magnitude() const noexcept {
        return std::sqrt(x * x + y * y);
    }

    /// @brief Returns a normalized version of the vector.
    /// @return A normalized vector.
    Vector2<float> normalized() const noexcept {
        auto len = magnitude();
        if (len == 0) return Vector2<float>(0.0f, 0.0f);
        return Vector2<float>(x / len, y / len);
    }

    constexpr auto dot(const Vector2& v2) const noexcept {
        return x * v2.x + y * v2.y;
    }
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const Vector2<T>& vec) {
    os << "Vector2(" << static_cast<T>(vec.x) << ", " << static_cast<T>(vec.y) << ")";
    return os;
}
} // namespace Engine

namespace Engine {
    using Vector2i = Vector2<int>;
    using Vector2f = Vector2<float>;
    using Vector2u = Vector2<unsigned>;
} // namespace Engine