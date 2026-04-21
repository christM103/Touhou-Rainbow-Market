#pragma once

#include <map>
#include <memory>

#include "Engine/Math/Rect.hpp"
#include "Engine/Math/Vector2.hpp"

namespace Engine {
    struct ColliderComponent {
        enum CollisionFlags : uint16_t {
            Null = 0,

            trackObj = 1 << 1,
            trackMouse = 1 << 2,
            
            mousePressed = 1 << 3,
            mouseHeld = 1 << 4,
            mouseReleased = 1 << 5,
            mouseHovered = 1 << 6,

            hitsObj = 1 << 7,
        };
        
        Rect<float> bounds;
        Vector2<float> offset;
        uint16_t flags{ CollisionFlags::Null };

        ColliderComponent(const Rectf& rect = Rectf(), const Vector2f& off = Vector2f(), bool tObj = false, bool tMouse = false)
            : bounds(rect), offset(off) {
            if (tObj) {
                flags ^= trackObj;
            }

            if (tMouse) {
                flags ^= trackMouse;
            }
        
        }

        bool const objPressed() {
            return (flags & CollisionFlags::mousePressed) != CollisionFlags::Null;
        }

        bool const objHeld() {
            return (flags & CollisionFlags::mouseHeld) != CollisionFlags::Null;
        }

        bool const objReleased() {
            return (flags & CollisionFlags::mouseReleased) != CollisionFlags::Null;
        }

        bool const objHovered() {
            return (flags & CollisionFlags::hitsObj) != CollisionFlags::Null;
        }


    };
    
    struct MultiColliderComponent {
        std::map<uint8_t, std::shared_ptr<ColliderComponent>> colliders;
    };
} // namespace Engine