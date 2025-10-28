// Copyright 2025 chrisfantasy

#pragma once

#include <chrono>
#include "Engine/Core/Engine.hpp"
#include "Engine/Graphics/Sprite.hpp"
#include "Game/player.hpp"
//#include "Game/event.hpp"

using namespace std::chrono_literals;
using Sprite_Map = std::map<std::string, std::unique_ptr<Engine::Sprite>>;
using Player_Set = std::vector<std::shared_ptr<TR::Player_Data>>;

typedef std::chrono::steady_clock::time_point current_time;
typedef std::chrono::seconds seconds;
typedef std::chrono::duration<double> timer;

namespace TR {

    enum Main_Game_States : uint16_t {
        Null_State = 0,
        Pause = 1 << 0,
        Intro_Sceen = 1 << 1,
        Help_Screen = 1 << 2,
        Market_Prompt = 1 << 3,
        Turn_Intro = 1 << 4,
        Text_Prompt = 1 << 5,
        Highlight_Market = 1 << 6,
        Highlight_Action = 1 << 7,
        Choosing_Player_Land = 1 << 8,
        Choosing_Enemy_Land = 1 << 9,
        End_Of_Turn = 1 << 10,
        Market_Action = 1 << 11
    };

    class Timer {
    public:
        explicit Timer(seconds new_dur);
        timer time_left();
        void timer_reset(seconds new_dur);


    private:
        current_time _start;
        seconds _dur;
        timer _curr_left;


    };  // namespace TR

    class Game_States {
    public:
        Game_States();
        virtual ~Game_States();

        virtual bool create(SDL_Renderer* renderer, Engine::Engine* gEngine, Sprite_Map& sprite_set) = 0;
        virtual void update(float deltaTime) = 0;
        virtual void render(SDL_Renderer* renderer, Sprite_Map& sprite_set, Player_Set& player_set) = 0;

    protected:
    };

    class Char_Select : public Game_States {
    public:
        Char_Select();
        ~Char_Select() override;

        bool create(SDL_Renderer* renderer, Engine::Engine* gEngine, Sprite_Map& sprite_set) override;
        void update(float deltaTime) override;
        void render(SDL_Renderer* renderer, Sprite_Map& sprite_set, Player_Set& player_set) override;


    private:
        
    };

    class Market_Game : public Game_States {
    public:
        Market_Game();
        explicit Market_Game(std::vector<std::shared_ptr<TR::Player_Data>> players);
        ~Market_Game() override;

        bool create(SDL_Renderer* renderer, Engine::Engine* gEngine, Sprite_Map& sprite_set);
        void update(float deltaTime) override;
        void render(SDL_Renderer* renderer, Sprite_Map& sprite_set, Player_Set& player_set) override;

    private:
        Main_Game_States _current_state{ Null_State };
    };

}
