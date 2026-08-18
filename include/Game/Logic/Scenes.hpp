// Copyright 2025 chrisfantasy

#pragma once

#include <yaml-cpp/yaml.h>
#include "Game/Logic/Globals.hpp"

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

        virtual bool create() = 0;
        virtual void update() = 0;

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

        bool create() override;
        void update() override;

    };

    /// @brief Character Select Scene
    class Char_Select : public Scene {
    public:
        Char_Select();

        bool create() override;
        void update() override;
    };

    /// @brief Main Market Game Scene
    class Market_Game : public Scene {
    public:

        /// @brief List of possible game states
        enum Main_Game_States : uint16_t {
            MG_Null_State,

            MG_Welcome_Screen,
            MG_First_Turn_Question,
            MG_Guide_Screen,
            MG_Intro_Market,
            MG_Market_Prompt,
            MG_Turn_Start,

            MG_Main_Game,
            MG_Highlight_Market,
            MG_Highlight_Portrait,

            MG_Market_Action_Prompt,
            MG_Player_Action_Prompt,
            MG_Player_Action,
            MG_Market_Action,
            MG_Market_Choice,
            MG_Player_Choice,

            MG_Turn_End,
            MG_Turn_Debrief,
            
            MG_Game_End,

            MG_Paused = 1 << 16,

        };

        Market_Game();
        explicit Market_Game(std::vector<std::shared_ptr<TR::Player_Data>> players);

        bool create() override;
        void update() override;

        /* Start of turn Actions */
        void introScreen();
        void firstTurnQuestion();
        void guideScreen();
        void marketPrompt();
        void addingMarket();
        void removingMarket();
        void turnStart();
        /* Global Actions */
        void showHUD();
        void hideHUD();
        void landEffect();
        bool countdownTimer();
        /* Market Actions */
        void highlightMarket();
        void marketActionPrompt(); // Checks for 2 actions from the market
        /* Player Actions */
        void highlightPlayer();
        void playerActionPrompt(); // Checks for 1 action from the player
        /* Actions */
        void actionSelf();
        void actionSelfAll();
        void actionOther();
        void actionOtherAll();
        void actionFailed();
        void actionSuccess();
        /* End of turn Actions */
        void turnEnd();
        void debriefScreen();
        void gameComplete();




    private:
        uint32_t _market_scene_state{ MG_Null_State };
    };

    

}
// namespace TR