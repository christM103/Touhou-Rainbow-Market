#pragma once
#include <cmath>
#include <type_traits>
#include <ostream>

namespace Engine {

    template<typename T>
    struct Vector3 {
        // Ensure T is an arithmetic type
        static_assert(std::is_arithmetic<T>::value, "Vector3 requires an arithmetic type");

        T x;
        T y;
        T z;

        constexpr Vector3() : x(0), y(0), z(0) {}
        constexpr Vector3(T x, T y, T z) : x(x), y(y), z(z) {}


        // Arithmetic operators
        constexpr Vector3 operator+(const Vector3& v3) const noexcept {
            return Vector3(x + v3.x, y + v3.y, z + v3.z);
        }
        constexpr Vector3 operator-(const Vector3& v3) const noexcept {
            return Vector3(x - v3.x, y - v3.y, z - v3.z);
        }
        constexpr Vector3 operator*(T scalar) const noexcept {
            return Vector3(x * scalar, y * scalar, z * scalar);
        }
        constexpr Vector3 operator/(T scalar) const noexcept {
            return Vector3(x / scalar, y / scalar, z / scalar);
        }


        // Arithmetic assignment operators

        /// @brief Adds anv3 vector to this vector.
        /// @param v3 The vector to add.
        Vector3& operator+=(const Vector3& v3) {
            x += v3.x;
            y += v3.y;
            z += v3.z;
            return *this;
        }
        Vector3& operator-=(const Vector3& v3) {
            x -= v3.x;
            y -= v3.y;
            z -= v3.z;
            return *this;
        }
        Vector3& operator*=(T scalar) {
            x *= scalar;
            y *= scalar;
            z *= scalar;
            return *this;
        }
        Vector3& operator/=(T scalar) {
            x /= scalar;
            y /= scalar;
            z /= scalar;
            return *this;
        }

        // Comparison operators

        bool operator==(const Vector3& v3) const {
            return x == v3.x && y == v3.y && z == v3.z;
        }
        bool operator!=(const Vector3& v3) const {
            return !(*this == v3);
        }


        // Utility functions

    };

    template<typename T>
    std::ostream& operator<<(std::ostream& os, const Vector3<T>& vec) {
        os << "Vector2(" << static_cast<T>(vec.x) << ", " << static_cast<T>(vec.y) << ", " << static_cast<T>(vec.z) << ")";
        return os;
    }
} // namespace Engine

namespace Engine {
    using Vector3i = Vector3<int>;
    using Vector3f = Vector3<float>;
    using Vector3u = Vector3<unsigned>;
} // namespace Engine