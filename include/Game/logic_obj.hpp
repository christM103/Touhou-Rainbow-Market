#pragma once

#include "Engine/Core/Engine.hpp"
#include "Engine/Graphics/Sprite.hpp"
#include "Engine/Graphics/Text.hpp"
#include "Engine/Math/Rect.hpp"
#include "Engine/Math/Vector2.hpp"
#include "Game/player.hpp"

#include <SDL2/SDL_ttf.h>


constexpr int SCREEN_SCALE = 2;
using Sprite_Map = std::map<std::string, std::unique_ptr<Engine::Sprite>>;
using Player_Set = std::vector<std::shared_ptr<TR::Player_Data>>;

namespace TR {

    class Scene_Object {
    public:
        Scene_Object() = default;
        virtual ~Scene_Object() = default;

        virtual void init(SDL_Renderer* renderer, Engine::Engine* gEngine, Sprite_Map& sprite_set, Player_Set& player_set) = 0;
        virtual void draw(SDL_Renderer* renderer, Engine::Engine* gEngine, Sprite_Map& sprite_set, Player_Set& player_set) = 0;
        virtual void updateMask(Sprite_Map& sprite_set) = 0;

        virtual void objMouseMove(Engine::Engine* gEngine, Sprite_Map& sprite_set, Player_Set& player_set) = 0;
        virtual void objMouseClick(Engine::Engine* gEngine, Sprite_Map& sprite_set, Player_Set& player_set) = 0;
        virtual void objKeyInput(Engine::Engine* gEngine, Sprite_Map& sprite_set, Player_Set& player_set) = 0;

        inline void objInput(Engine::Engine* gEngine, Sprite_Map& sprite_set, Player_Set& player_set) {
            objMouseMove(gEngine, sprite_set, player_set);
            objMouseClick(gEngine, sprite_set, player_set);
            objKeyInput(gEngine, sprite_set, player_set);
        }

    protected:
        int _time{0};
        Engine::Recti _sprite_mask{ 0, 0, 1, 1 };
    };

    /// @brief In-game textbox objects

    /*
    class TextBox : public Scene_Object {
    public:

        enum Text_Box_Transitions : uint16_t {
            TXT_NULL = 0,
            TXT_ACTIVE = 1 << 0,
            TXT_ACTIVE_TEXT = 1 << 1,
            TXT_ACTIVE_TEXT_COMPLETE = 1 << 2,
            TXT_ENTER_EXIT = 1 << 3,
            TXT_UP_DOWN = 1 << 4,
            TXT_LEFT_RIGHT = 1 << 5,
            TXT_CONST_VEL = 1 << 6
        };

        TextBox();
        TextBox(const char* text, bool prompt);
        TextBox(const char* text, bool prompt, uint16_t transitions);
        ~TextBox();


        void init(SDL_Renderer* renderer, Engine::Engine* gEngine, Sprite_Map& sprite_set, Player_Set& player_set) override;
        void draw(SDL_Renderer* renderer, Engine::Engine* gEngine, Sprite_Map& sprite_set, Player_Set& player_set) override;


        inline void setText(const char* str) { _text_stored = str; }
        inline void setSpeed(int speed) { _text_speed = speed; }

        inline char* getText() { return _text_stored.data(); }
        inline int getSpeed() { return _text_speed; }

        inline void enableAttr(uint16_t attr) { if (!(_text_attr & attr)) { _text_attr |= attr; } }
        inline void disableAttr(uint16_t attr) { if (_text_attr & attr) { _text_attr ^= attr; } }
        inline uint16_t getAttr() { return _text_attr; }

        void update(Engine::Engine* gEngine, Sprite_Map& sprite_set, Player_Set& player_set);
        void updateMask(Sprite_Map& sprite_set) override;
        void objMouseMove(Engine::Engine* gEngine, Sprite_Map& sprite_set, Player_Set& player_set) override;
        void objMouseClick(Engine::Engine* gEngine, Sprite_Map& sprite_set, Player_Set& player_set) override;
        void objKeyInput(Engine::Engine* gEngine, Sprite_Map& sprite_set, Player_Set& player_set) override;
        void displayTextBox(Engine::Engine* gEngine);
        void textAppear();
        void textContinue();

    private:
        std::string _text_stored;
        std::string _text_current;
        int _text_speed{ 1 };
        bool _confirm_prompt{ false };
        uint16_t _text_attr{ TXT_NULL };
        Engine::Text _text_gfx;
        //std::map<char, Engine::Vector2i> _char_map;
    };
    */

}