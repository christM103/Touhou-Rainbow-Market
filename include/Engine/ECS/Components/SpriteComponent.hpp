#pragma once

#include <map>
#include <memory>

#include "Engine/Math/Rect.hpp"
#include "Engine/Math/Vector2.hpp"
#include "Engine/ECS/Components/ColorComponent.hpp"


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
        const ColorComponent* getColor() const { return &color; }

        void setSourceRect(Rect<int> srcR) { sourceRect = srcR; }
        void setSize(Vector2<int> s) { size = s; }
        void setResourceID(const char* txt) { resourceID = txt; }
        void setColor(ColorComponent col) { color = col; }

        bool operator==(const SpriteComponent& sc) const {
            return size == sc.getSize() && sourceRect == sc.getSourceRect() && resourceID == sc.getResourceID();
        }

        private:
        Rect<int> sourceRect;
        Vector2<int> size;
        std::string resourceID;
        ColorComponent color{};
    };

    struct MultiSpriteComponent {
        std::map<uint8_t, std::shared_ptr<SpriteComponent>> sprites;
    };
}