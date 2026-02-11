// Copyright 2025 chrisfantasy

#pragma once

#include "Engine/Core/Engine.hpp"
#include "Game/Logic/Player.hpp"
//#include "Game/event.hpp"

using Player_Set = std::vector<std::shared_ptr<TR::Player_Data>>;

namespace TR {

    constexpr Engine::Vector2i TXT_A = Engine::Vector2i(205, 219);

    /// @brief Generic Game Scene
    class Scene {
    public:
        enum Scene_ID : uint8_t {
            SC_Null, SC_Title, SC_CharS, SC_Main
        };

        Scene() {
            _currState = SC_Null;
            _nextState = _currState;
        }

        ~Scene() = default;

        virtual bool create(SDL_Renderer* renderer, Engine::Engine* gEngine) = 0;
        virtual void update(Engine::Engine* gEngine) = 0;

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

        bool create(SDL_Renderer* renderer, Engine::Engine* gEngine) override;
        void update(Engine::Engine* gEngine) override;

    };

    /// @brief Character Select Scene
    class Char_Select : public Scene {
    public:
        Char_Select();

        bool create(SDL_Renderer* renderer, Engine::Engine* gEngine) override;
        void update(Engine::Engine* gEngine) override;
    };

    /// @brief Main Market Game Scene
    class Market_Game : public Scene {
    public:

        /// @brief List of possible game states
        enum Main_Game_States : uint16_t {
            MG_Null_State = 0,
            MG_Main_Game = 1 << 0,
            MG_Pause = 1 << 1,
            MG_Intro_Sceen = 1 << 2,
            MG_Help_Screen = 1 << 3,
            MG_Market_Prompt = 1 << 4,
            MG_Turn_Intro = 1 << 5,
            MG_Text_Prompt = 1 << 6,
            MG_Highlight_Market = 1 << 7,
            MG_Highlight_Action = 1 << 8,
            MG_Choosing_Player_Land = 1 << 9,
            MG_Choosing_Enemy_Land = 1 << 10,
            MG_End_Of_Turn = 1 << 11,
            MG_Market_Action = 1 << 12
        };

        Market_Game();
        explicit Market_Game(std::vector<std::shared_ptr<TR::Player_Data>> players);

        bool create(SDL_Renderer* renderer, Engine::Engine* gEngine);
        void update(Engine::Engine* gEngine) override;

        void state_machine(Engine::Engine* gEngine, Player_Set& player_set);

    private:
        uint16_t _market_scene_state{ MG_Null_State };
    };

    

}
// namespace TR