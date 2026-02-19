#pragma once

#include <unordered_map>
#include <memory>
#include "Engine/Math/Rect.hpp"
#include "Engine/Math/Vector2.hpp"

namespace Engine {
    struct VelocityComponent {
        Vector2f linear;
        float angular; // In degrees
        Vector2f scalar;
        float deltaTime; // In seconds

        VelocityComponent(const Vector2f& lin = { 0.0f, 0.0f }, float ang = 0.0f, const Vector2f& scl = {0.0f, 0.0f}, float t = 0.0f)
            : linear(lin), angular(ang), scalar(scl), deltaTime(t) {
        }
    };

    struct AccelerationComponent {
        Vector2f linear;
        float angular; // In degrees
        Vector2f scalar;

        AccelerationComponent(const Vector2f& lin = { 0.0f, 0.0f }, float ang = 0.0f, const Vector2f& scl = { 0.0f, 0.0f })
            : linear(lin), angular(ang), scalar(scl) {
        }
    };

    struct MultiVelocityComponent {
        std::unordered_map<uint8_t, std::shared_ptr<VelocityComponent>> velocities;
    };

    struct MultiAccelerationComponent {
        std::unordered_map<uint8_t, std::shared_ptr<AccelerationComponent>> accelerations;
    };
} // namespace Engine