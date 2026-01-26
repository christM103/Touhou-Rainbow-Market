#pragma once
#include <cmath>
#include <type_traits>
#include <ostream>

namespace Engine {

    template<typename T>
    struct Vector4 {
        // Ensure T is an arithmetic type
        static_assert(std::is_arithmetic<T>::value, "Vector4 requires an arithmetic type");

        T w;
        T x;
        T y;
        T z;

        constexpr Vector4() : w(0), x(0), y(0), z(0) {}
        constexpr Vector4(T w, T x, T y, T z) : w(w), x(x), y(y), z(z) {}


        // Arithmetic operators
        constexpr Vector4 operator+(const Vector4& v4) const noexcept {
            return Vector4(w + v4.w, x + v4.x, y + v4.y, z + v4.z);
        }
        constexpr Vector4 operator-(const Vector4& v4) const noexcept {
            return Vector4(w - v4.w, x - v4.x, y - v4.y, z - v4.z);
        }
        constexpr Vector4 operator*(T scalar) const noexcept {
            return Vector4(w * scalar, x * scalar, y * scalar, z * scalar);
        }
        constexpr Vector4 operator/(T scalar) const noexcept {
            return Vector4(w / scalar, x / scalar, y / scalar, z / scalar);
        }


        // Arithmetic assignment operators

        /// @brief Adds anv2 vector to this vector.
        /// @param v2 The vector to add.
        Vector4& operator+=(const Vector4& v4) {
            w += v4.w;
            x += v4.x;
            y += v4.y;
            z += v4.z;
            return *this;
        }
        Vector4& operator-=(const Vector4& v4) {
            w -= v4.w;
            x -= v4.x;
            y -= v4.y;
            z -= v4.z;
            return *this;
        }
        Vector4& operator*=(T scalar) {
            w *= scalar;
            x *= scalar;
            y *= scalar;
            z *= scalar;
            return *this;
        }
        Vector4& operator/=(T scalar) {
            w /= scalar;
            x /= scalar;
            y /= scalar;
            z /= scalar;
            return *this;
        }

        // Comparison operators

        bool operator==(const Vector4& v4) const {
            return w == v4.w && x == v4.x && y == v4.y && z == v4.z;
        }
        bool operator!=(const Vector4& v4) const {
            return !(*this == v4);
        }

    };

    template<typename T>
    std::ostream& operator<<(std::ostream& os, const Vector4<T>& vec) {
        os << "Vector4(" << ", " << static_cast<T>(vec.w) << ", " << static_cast<T>(vec.x) << ", " << static_cast<T>(vec.y) << ", " << static_cast<T>(vec.z) << ")";
        return os;
    }
} // namespace Engine

namespace Engine {
    using Vector4i = Vector4<int>;
    using Vector4f = Vector4<float>;
    using Vector4u = Vector4<unsigned>;
} // namespace Engine