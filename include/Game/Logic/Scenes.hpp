// Copyright 2025 chrisfantasy

#pragma once

#include "Game/Logic/Globals.hpp"
#include "Game/Logic/Player.hpp"
#include "Game/Logic/Common.hpp"

namespace TR {

    struct LocalGameState {
        Player_ID current_player{ Player_ID::Player_Null };
        Land_ID current_land{ Land_ID::Land_Null };

        Player_ID selected_player{ Player_ID::Player_Null };
        Land_ID selected_land_index{ Land_ID::Land_Null };
        Market_ID selected_market{ Market_ID::MID_Null };

        uint8_t text_index{ 0 };
        Prompt_Flags prompt_flags{ Prompt_Flags::Null };
        std::string current_text_string{ "" };
        std::string current_prompt{ "" };

        std::vector<std::string> market_queue{};
    };

    /// @brief Generic Game Scene
    class Scene {
    public:
        Scene() {
            _currState = Scene_ID::Null;
            _nextState = _currState;
        }

        ~Scene() = default;

        virtual bool create() = 0;
        virtual void update() = 0;

        inline Scene_ID getSceneCurr() { return _currState; }
        inline Scene_ID getSceneNext() { return _nextState; }

        inline void setSceneCurr(Scene_ID state) { _currState = state; }
        inline void setSceneNext(Scene_ID state) { _nextState = state; }

        inline auto& getDebugManager() {
            return Engine::DebugManager::instance();
        }

        inline std::string getYAMLPath() { return _yaml_path; }
        inline void setYAMLPath(std::string path) { _yaml_path = path; }
        void appendYAMLString(std::string str);

        inline constexpr uint8_t getTextIndex() const { return _state_data.text_index; }
        inline constexpr void setTextIndex(uint8_t ind) { _state_data.text_index = ind; }
        inline constexpr void textIndexNext() {
            _state_data.text_index++;
        }
        inline constexpr void textIndexPrev() {
            _state_data.text_index--;
        }
        inline constexpr void textIndexReset() {
            _state_data.text_index = 0;
        }

        inline constexpr std::string getGameTextString() { 
            return _state_data.current_text_string; 
        }
        inline constexpr void setGameTextString(std::string_view str) { 
            _state_data.current_text_string = str;
        }
        inline constexpr void clearGameTextString() { 
            _state_data.current_text_string = ""; 
        }
        inline constexpr void appendGameTextString(std::string_view str) { 
            _state_data.current_text_string += str; 
        }
        inline constexpr bool isGameTextStringEmpty() { 
            return _state_data.current_text_string.empty(); 
        }

        inline void setPromptAction(std::string action) {
            _state_data.current_prompt = action;
        }
        inline void resetPromptAction() {
            _state_data.current_prompt = "";
            getDebugManager().hidePrompt();
        }
        void parsePromptAction();
        void selectionPromptAction();

        void substitutePlaceholder();

    protected:

        Scene_ID _currState{ Scene_ID::Null }, _nextState{ Scene_ID::Null };
        std::string _yaml_path{ "" };
        inline static LocalGameState _state_data;
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
        Market_Game();

        bool create() override;
        void update() override;

        inline void swapState(Game_States state) {
            _market_scene_state = state;
            clearGameTextString();
            textIndexReset();
            if (getDebugManager().isEnabled()) {
                if (getDebugManager().isPromptShown()) {
                    getDebugManager().hidePrompt();
                }
            }
            
        }

        /* Start of turn Actions */
        void introScreen();
        void firstTurnQuestion();
        void guideScreen();
        void marketPrompt(uint8_t tier = 1);
        void marketSelection();
        void addingMarket(Market_ID newMarket, MarketComponent* current_land);
        void removingMarket(MarketComponent* current_land);
        void turnStart();
        void landEffect();
        /* Helper HUD Actions */
        void showHUD();
        void hideHUD();
        bool isHUDRunning();
        bool countdownTimer();
        /* Main Game Screen */
        void mainGameScreen();
        /* Market Actions */
        void highlightLand();
        void landActionPrompt(); // Checks for 2 actions from the market
        /* Player Actions */
        void highlightPlayer();
        void playerActionPrompt(); // Checks for 1 action from the player
        /* Actions */
        void actionPrompt(Game_States prev_state);
        void actionManager();
        void actionFailed();
        void actionSuccess();
        /* End of turn Actions */
        void turnEnd();
        void debriefScreen();
        void gameComplete();


    private:
        Game_States _market_scene_state{ Game_States::MG_Null_State };
    };

}
// namespace TR