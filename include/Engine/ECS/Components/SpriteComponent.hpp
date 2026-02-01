#pragma once

#include <unordered_map>

#include "Engine/Math/Rect.hpp"
#include "Engine/Math/Vector2.hpp"


namespace Engine {
    class SpriteComponent {
        public:
        SpriteComponent() : sourceRect(0, 0, 0, 0), size(0, 0) {}
        ~SpriteComponent() = default;

        
        SpriteComponent(const Rect<int>& srcRect, const Vector2<int>& sz, const char* str)
            : sourceRect(srcRect), size(sz), resourceID(str) {}

        const Rect<int> getSourceRect() const { return sourceRect; }
        const Vector2<int> getSize() const { return size; }
        const char* getResourceID() const { return resourceID.c_str(); }

        void setSourceRect(Rect<int> srcR) { sourceRect = srcR; }
        void setSize(Vector2<int> s) { size = s; }
        void setResourceID(const char* txt) { resourceID = txt; }

        bool operator==(const SpriteComponent& sc) const {
            return size == sc.getSize() && sourceRect == sc.getSourceRect();
        }

        private:
        Rect<int> sourceRect;
        Vector2<int> size;
        std::string resourceID;
    };

    struct MultiSpriteComponent {
        std::unordered_map<uint8_t, SpriteComponent*> sprites;
    };
}