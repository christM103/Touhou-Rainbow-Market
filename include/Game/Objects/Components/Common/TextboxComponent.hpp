#pragma once

#include <cstdint>
#include <string>
#include <unordered_set>


#include "Engine/ECS/Components/Components.hpp"

namespace TR {

    struct TextBoxComponent {

        enum TextBoxFlags : uint16_t {
            TXTBOX_NULL = 0,
            ENTER = 1 << 1,
            EXIT = 1 << 2,
            TRANSITION_LEFT = 1 << 3,
            TRANSITION_RIGHT = 1 << 4,
            TRANSITION_UP = 1 << 5,
            TRANSITION_DOWN = 1 << 6,
            TXT_ACTIVE = 1 << 7,
            TXT_COMPLETE = 1 << 8,
            TXT_CONTINUE = 1 << 9,

        };

        /// Textbox Components
        std::string _textbox_text;
        Engine::Vector2i _textbox_position;
        uint8_t _textbox_speed;
        uint8_t _textbox_style;
        uint16_t _textbox_flags;

        // Text Properties
        uint8_t textLine{ 1 };

        // Time Properties
        uint8_t dT{ 0 };

        TextBoxComponent(const char* text, int x, int y, int txtSp = 1, uint16_t flags = TXTBOX_NULL | TXT_COMPLETE, int txtSt = 0)
            : _textbox_text(text), _textbox_position(x, y), _textbox_speed(txtSp), _textbox_flags(flags), _textbox_style(txtSt){}

        TextBoxComponent(const char* text, Engine::Vector2i pos, int txtSp = 1, uint16_t flags = TXTBOX_NULL | TXT_COMPLETE, int txtSt = 0)
            : TextBoxComponent(text, pos.x, pos.y, txtSp, flags, txtSt) {}

    };

}