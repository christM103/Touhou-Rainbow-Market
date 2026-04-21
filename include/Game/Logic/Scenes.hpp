// Copyright 2025 chrisfantasy

#pragma once

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
        enum Main_Game_States : uint32_t {
            MG_Null_State = 0,
            MG_Main_Game = 1 << 0,
            MG_Pause = 1 << 1,

            MG_Intro_Sceen = 1 << 16,
            MG_Help_Screen = 1 << 17,

            MG_Market_Prompt = 1 << 18,
            MG_Market_Prompt_SCRIPT_0, 
            MG_Market_Prompt_SCRIPT_0_FINISHED, 
            MG_Market_Prompt_RESIZE_0, 
            MG_Market_Prompt_SCRIPT_1, 
            MG_Market_Prompt_SCRIPT_1_FINISHED, 
            MG_Market_Prompt_RESIZE_1, 
            MG_Market_Prompt_SCRIPT_2, 
            MG_Market_Prompt_SCRIPT_2_FINISHED, 
            MG_Market_Prompt_END,

            MG_Turn_Intro = 1 << 19,
            MG_Text_Prompt = 1 << 20,
            MG_Highlight_Market = 1 << 21,
            MG_Highlight_Action = 1 << 22,
            MG_Choosing_Player_Land = 1 << 23,
            MG_Choosing_Enemy_Land = 1 << 24,
            MG_End_Of_Turn = 1 << 25,
            MG_Market_Action = 1 << 26
        };

        static constexpr uint32_t Main_Game_Timeline_States
        { MG_Intro_Sceen | MG_Help_Screen | MG_Market_Prompt | MG_Turn_Intro | MG_Text_Prompt | MG_Highlight_Market | MG_Highlight_Action | MG_Choosing_Player_Land | MG_Choosing_Enemy_Land |
            MG_End_Of_Turn };

        Market_Game();
        explicit Market_Game(std::vector<std::shared_ptr<TR::Player_Data>> players);

        bool create() override;
        void update() override;

        void Market_Prompt_States(TextBoxComponent* textbox, ButtonPromptComponent* prompt);

    private:
        uint32_t _market_scene_state{ MG_Null_State };
    };

    

}
// namespace TR