// Copyright 2025 chrisfantasy

#pragma once

#include <chrono>
#include "Game/logic_obj.hpp"
//#include "Game/event.hpp"

using namespace std::chrono_literals;
typedef std::chrono::steady_clock::time_point current_time;
typedef std::chrono::seconds seconds;
typedef std::chrono::duration<double> timer;

namespace TR {

    constexpr Engine::Vector2i TXT_A = Engine::Vector2i(205, 219);

    /// @brief Generic Game Scene
    class Scene {
    public:
        enum Scene_ID : uint8_t {
            SC_Null, SC_Title, SC_CharS, SC_Main
        };

        Scene();
        virtual ~Scene();

        virtual bool create(SDL_Renderer* renderer, Engine::Engine* gEngine, Sprite_Map& sprite_set, Player_Set& player_set) = 0;
        virtual void update(Engine::Engine* gEngine, Sprite_Map& sprite_set, Player_Set& player_set) = 0;
        virtual void render(SDL_Renderer* renderer, Engine::Engine* gEngine, Sprite_Map& sprite_set, Player_Set& player_set) = 0;

        inline Scene_ID getSceneCurr() { return _currState; }
        inline Scene_ID getSceneNext() { return _nextState; }

        inline void setSceneCurr(Scene_ID state) { _currState = state; }
        inline void setSceneNext(Scene_ID state) { _nextState = state; }

    protected:
        Scene_ID _currState{ SC_Null }, _nextState{ SC_Null };
    };

    /// @brief Title Screen Scene
    class Title_Screen : public Scene {
    public:
        Title_Screen();
        ~Title_Screen() override;

        bool create(SDL_Renderer* renderer, Engine::Engine* gEngine, Sprite_Map& sprite_set, Player_Set& player_set) override;
        void update(Engine::Engine* gEngine, Sprite_Map& sprite_set, Player_Set& player_set) override;
        void render(SDL_Renderer* renderer, Engine::Engine* gEngine, Sprite_Map& sprite_set, Player_Set& player_set) override;

    private:
        Engine::Text start_prompt{ "Press Space to play!", 40 };

    };

    /// @brief Character Select Scene
    class Char_Select : public Scene {
    public:
        Char_Select();
        ~Char_Select() override;

        bool create(SDL_Renderer* renderer, Engine::Engine* gEngine, Sprite_Map& sprite_set, Player_Set& player_set) override;
        void update(Engine::Engine* gEngine, Sprite_Map& sprite_set, Player_Set& player_set) override;
        void render(SDL_Renderer* renderer, Engine::Engine* gEngine, Sprite_Map& sprite_set, Player_Set& player_set) override;


    private:
        Engine::Text char_choice_prompt{ "Choose your character using the left and right arrow keys", 40 };
    };

    /// @brief Main Market Game Scene
    class Market_Game : public Scene {
    public:

        /// @brief List of possible game states
        enum Main_Game_States : uint16_t {
            MG_Null_State = 0,
            MG_Pause = 1 << 0,
            MG_Intro_Sceen = 1 << 1,
            MG_Help_Screen = 1 << 2,
            MG_Market_Prompt = 1 << 3,
            MG_Turn_Intro = 1 << 4,
            MG_Text_Prompt = 1 << 5,
            MG_Highlight_Market = 1 << 6,
            MG_Highlight_Action = 1 << 7,
            MG_Choosing_Player_Land = 1 << 8,
            MG_Choosing_Enemy_Land = 1 << 9,
            MG_End_Of_Turn = 1 << 10,
            MG_Market_Action = 1 << 11
        };

        Market_Game();
        explicit Market_Game(std::vector<std::shared_ptr<TR::Player_Data>> players);
        ~Market_Game() override;

        bool create(SDL_Renderer* renderer, Engine::Engine* gEngine, Sprite_Map& sprite_set, Player_Set& player_set);
        void update(Engine::Engine* gEngine, Sprite_Map& sprite_set, Player_Set& player_set) override;
        void render(SDL_Renderer* renderer, Engine::Engine* gEngine, Sprite_Map& sprite_set, Player_Set& player_set) override;

        /// @brief Timer used for the game
        class Timer {
        public:
            explicit Timer(seconds new_dur);
            timer time_left();
            void timer_reset(seconds new_dur);


        private:
            current_time _start;
            seconds _dur;
            timer _curr_left;
        };

    private:
        uint16_t _market_scene_state{ MG_Null_State };
        std::string test_string = "THE QUICK BROWN FOX JUMPED OVER \nTHE LAZY DOG'S BACK 1234567890\nThe five boxing wizards jump quickly?";
        TextBox test_textbox{ "This is a small test demo for the game Touhou Rainbow Market.\nTo control, You can highlight a specific market using keypad numbers 1-6. From there you can have the option to either sell or buy a specific given market.\nMake sure to keep in mind the time!", 
            true, {TextBox::TXT_NULL | TextBox::TXT_UP_DOWN, TextBox::TXT_NULL | TextBox::TXT_UP_DOWN} };
    };

    

}
// namespace TR