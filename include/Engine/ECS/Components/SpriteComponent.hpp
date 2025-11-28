#pragma once

#include "Engine/Math/Rect.hpp"
#include "Engine/Math/Vector2.hpp"

namespace Engine {
    class SpriteComponent {
        public:
        SpriteComponent() : sourceRect(0, 0, 0, 0), size(0, 0) {}
        ~SpriteComponent() = default;

        
        SpriteComponent(const Rect<float>& srcRect, const Vector2<float>& sz)
            : sourceRect(srcRect), size(sz) {}

        private:
        Rect<float> sourceRect;
        Vector2<float> size;

    };
}