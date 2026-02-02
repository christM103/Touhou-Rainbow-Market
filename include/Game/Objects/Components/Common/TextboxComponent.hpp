#pragma once

#include <cstdint>
#include <string>
#include <unordered_set>


#include "Engine/ECS/Components/Components.hpp"

namespace TR {
	struct TextBoxInfo {
        
        int textbox_speed;
        int textbox_style;
        bool textbox_confirm;
        std::unordered_set<std::string> textbox_prompts;

        TextBoxInfo(int txtSp = 1, int txtSt = 0, bool txtCon = false)
        : textbox_speed(txtSp), textbox_style(txtSt), textbox_confirm(txtCon) {}

	};

    class TextBoxComponent {
    public:

        TextBoxComponent(const char* text, int x, int y) {

            _transform_comp = std::make_shared<Engine::MultiTransformComponent>();
            _sprite_comp = std::make_shared<Engine::MultiSpriteComponent>();
            _text_comp = std::make_shared<Engine::MultiTextComponent>();
            _render_comp = std::make_shared<Engine::RenderLayerComponent>();

            _transform_comp->transforms.emplace(0, std::make_shared<Engine::TransformComponent>(Engine::Vector2i{ x, y }));
            _transform_comp->transforms.emplace(1, std::make_shared<Engine::TransformComponent>(Engine::Vector2i{ x, y }));
            _transform_comp->transforms.emplace(2, std::make_shared<Engine::TransformComponent>(Engine::Vector2i{ x + 40, y + 40 }));

            _sprite_comp->sprites.emplace(0, std::make_shared<Engine::SpriteComponent>(Engine::Recti(0, 0, 800, 400), Engine::Vector2i(800, 400), "TXT_BOX_BG"));
            _sprite_comp->sprites.emplace(1, std::make_shared<Engine::SpriteComponent>(Engine::Recti(0, 0, 800, 400), Engine::Vector2i(800, 400), "TXT_BOX_F"));


            _text_comp->text.emplace(2, std::make_shared<Engine::TextComponent>(text, 40, Engine::Vector4i(255, 255, 255, 255), Engine::Vector2i(740, 400)));

            _render_comp->layer = Engine::RenderLayerComponent::FG;
        }

        TextBoxComponent(const char* text, Engine::Vector2i pos) : TextBoxComponent(text, pos.x, pos.y) {}

        inline Engine::MultiTransformComponent getMultiTransComponent() { return *_transform_comp; }
        inline Engine::MultiSpriteComponent getMultiSpriteComponent() { return *_sprite_comp; }
        inline Engine::MultiTextComponent getMultiTextComponent() { return  *_text_comp; }
        inline Engine::RenderLayerComponent getRenderLayerComponent() { return *_render_comp; }

    private:
        enum class Text_Box_Transitions : uint16_t {
            TXT_NULL = 0,
            TXT_ACTIVE = 1 << 0,
            TXT_COMPLETE = 1 << 1,
            ENTER = 1 << 2,
            EXIT = 1 << 3,
            TRANSITION_LEFT = 1 << 4,
            TRANSITION_RIGHT = 1 << 5,
            TRANSITION_UP = 1 << 6,
            TRANSITION_DOWN = 1 << 7,
        };

        /*
        friend constexpr Text_Box_Transitions operator|(Text_Box_Transitions a, Text_Box_Transitions b) noexcept {
            return static_cast<Text_Box_Transitions>(static_cast<uint16_t>(a) | static_cast<uint16_t>(b));
        }
        friend constexpr Text_Box_Transitions operator&(Text_Box_Transitions a, Text_Box_Transitions b) noexcept {
            return static_cast<Text_Box_Transitions>(static_cast<uint16_t>(a) & static_cast<uint16_t>(b));
        }
        friend constexpr Text_Box_Transitions operator^(Text_Box_Transitions a, Text_Box_Transitions b) noexcept {
            return static_cast<Text_Box_Transitions>(static_cast<uint16_t>(a) ^ static_cast<uint16_t>(b));
        }
        friend constexpr Text_Box_Transitions operator~(Text_Box_Transitions a) noexcept {
            return static_cast<Text_Box_Transitions>(~static_cast<uint16_t>(a));
        }
        friend Text_Box_Transitions& operator|=(Text_Box_Transitions& a, Text_Box_Transitions b) noexcept {
            a = a | b;
            return a;
        }
        friend Text_Box_Transitions& operator&=(Text_Box_Transitions& a, Text_Box_Transitions b) noexcept {
            a = a & b;
            return a;
        }
        friend Text_Box_Transitions& operator^=(Text_Box_Transitions& a, Text_Box_Transitions b) noexcept {
            a = a ^ b;
            return a;
        }
        */

        TextBoxInfo _textbox_data;
        Engine::Vector2i _textbox_position;

        std::shared_ptr<Engine::MultiTransformComponent> _transform_comp;
        std::shared_ptr<Engine::MultiSpriteComponent> _sprite_comp;
        std::shared_ptr<Engine::MultiTextComponent> _text_comp;

        std::shared_ptr<Engine::RenderLayerComponent> _render_comp;
    };

}