#pragma once

#include <cstdint>
#include <string>
#include <unordered_set>

namespace TR {

    struct TextBoxComponent {

        enum TextBoxFlags : uint16_t {
            TXTBOX_NULL = 0,
            // Textbox Transitions
            ENTER = 1 << 1,
            EXIT = 1 << 2,

            // Transition Directions
            TRANSITION_LEFT = 1 << 3,
            TRANSITION_RIGHT = 1 << 4,
            TRANSITION_UP = 1 << 5,
            TRANSITION_DOWN = 1 << 6,

            // Text Flags
            TXT_ACTIVE = 1 << 7,
            TXT_COMPLETE = 1 << 8,
            TXT_CONTINUE = 1 << 9,

            INPUT_PRESSED = 1 << 10,
            RESIZE = 1 << 11,

            END = 1 << 15,
        };

        enum TextBoxStyles : uint8_t {
            NULL_BOX = 0, 
            WIDTH_TINY = 1 << 0,
            WIDTH_SMALL = 1 << 1,
            WIDTH_MEDIUM = 1 << 2,
            WIDTH_LARGE = 1 << 3,
            HEIGHT_TINY = 1 << 4,
            HEIGHT_SMALL = 1 << 5,
            HEIGHT_MEDIUM = 1 << 6,
            HEIGHT_LARGE = 1 << 7,
        };

        /// Textbox Components
        std::string _textbox_text;
        std::string _textbox_next{""};
        Engine::Vector2i _textbox_position;
        Engine::Vector2i _textbox_size{ 0,0 };
        uint8_t _textbox_speed;
        uint8_t _textbox_style;
        TextBoxFlags _textbox_flags;

        // Text Properties
        uint8_t _textSize;
        uint8_t _textLine{ 1 };
        uint8_t _textMax{ 6 };

        // Time Properties
        uint16_t dT{ 0 };

        TextBoxComponent(const char* text, int x, int y, int txtSp = 1, uint16_t flags = TXTBOX_NULL | TXT_COMPLETE, uint8_t txtSt = WIDTH_MEDIUM | HEIGHT_MEDIUM, uint8_t txtSz = 40)
            : _textbox_text(text), _textbox_position(x, y), _textbox_speed(txtSp), _textbox_flags(static_cast<TextBoxFlags>(flags)), _textbox_style(txtSt), _textSize(txtSz) {}

        TextBoxComponent(const char* text, Engine::Vector2i pos, int txtSp = 1, uint16_t flags = TXTBOX_NULL | TXT_COMPLETE, uint8_t txtSt = WIDTH_MEDIUM | HEIGHT_MEDIUM, uint8_t txtSz = 40)
            : TextBoxComponent(text, pos.x, pos.y, txtSp, flags, txtSt, txtSz) {}

    };

    inline TextBoxComponent::TextBoxFlags operator^(TextBoxComponent::TextBoxFlags lhs, TextBoxComponent::TextBoxFlags rhs) {
        return static_cast<TextBoxComponent::TextBoxFlags>(
            static_cast<uint16_t>(lhs) ^ static_cast<uint16_t>(rhs)
        );
    }

    inline TextBoxComponent::TextBoxFlags& operator^=(TextBoxComponent::TextBoxFlags& lhs, TextBoxComponent::TextBoxFlags rhs) {
        lhs = static_cast<TextBoxComponent::TextBoxFlags>(
            static_cast<uint16_t>(lhs) ^ static_cast<uint16_t>(rhs)
        );
        return lhs;
    }

    inline TextBoxComponent::TextBoxFlags operator|(TextBoxComponent::TextBoxFlags lhs, TextBoxComponent::TextBoxFlags rhs) {
        return static_cast<TextBoxComponent::TextBoxFlags>(
            static_cast<uint16_t>(lhs) | static_cast<uint16_t>(rhs)
        );
    }

    inline TextBoxComponent::TextBoxFlags& operator|=(TextBoxComponent::TextBoxFlags& lhs, TextBoxComponent::TextBoxFlags rhs) {
        lhs = static_cast<TextBoxComponent::TextBoxFlags>(
            static_cast<uint16_t>(lhs) | static_cast<uint16_t>(rhs)
        );
        return lhs;
    }

    inline TextBoxComponent::TextBoxFlags operator&(TextBoxComponent::TextBoxFlags lhs, TextBoxComponent::TextBoxFlags rhs) {
        return static_cast<TextBoxComponent::TextBoxFlags>(
            static_cast<uint16_t>(lhs) & static_cast<uint16_t>(rhs)
        );
    }

    inline TextBoxComponent::TextBoxFlags& operator&=(TextBoxComponent::TextBoxFlags& lhs, TextBoxComponent::TextBoxFlags rhs) {
        lhs = static_cast<TextBoxComponent::TextBoxFlags>(
            static_cast<uint16_t>(lhs) & static_cast<uint16_t>(rhs)
        );
        return lhs;
    }

    inline TextBoxComponent::TextBoxFlags operator~(TextBoxComponent::TextBoxFlags flag) {
        return static_cast<TextBoxComponent::TextBoxFlags>(
            ~static_cast<uint16_t>(flag)
        );
    }

}