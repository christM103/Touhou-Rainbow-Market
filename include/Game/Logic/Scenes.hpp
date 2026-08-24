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

            MG_Paused = 1 << 15,

        };

        Market_Game();
        explicit Market_Game(std::vector<std::shared_ptr<TR::Player_Data>> players);

        bool create() override;
        void update() override;

        /* Start of turn Actions */
        void introScreen();
        void firstTurnQuestion();
        void guideScreen();
        void marketPrompt(uint8_t tier = 1);
        void addingMarket(Market_ID newMarket, int index);
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

    struct TextManager {
        enum Text_Flags : uint16_t {
            TXT_NULL = 0,
            TXT_WAIT_TXT = 1 << 0, TXT_WAIT_PROMPT = 1 << 1,
        };

        enum Prompt_Type : uint8_t {
            PROMPT_NULL, PROMPT_YN, PROMPT_MARKET, PROMPT_LAND,
        };

        enum Prompt_Flags : uint8_t {
            PRM_NULL = 0,
            PRM_YN_YES = 1 << 1, PRM_YN_CONFIRM = 1 << 2,                                // Y/N Prompt: Bit 1 = Yes (1) or No (0), Bit 2 = Confirm (1) or Unconfirmed (0)

            PRM_MK_M1 = 1 << 1, PRM_MK_M2 = 1 << 2, PRM_MK_M3 = 1 << 3,                  // Market Prompt: Bits 1 - 3: Markets 1 - 3, Bit 7 = Confirm (1) or Unconfirmed (0)
            PRM_MK_CONFIRM = 1 << 7,                                                     //

            PRM_LD_1 = 1, PRM_LD_2, PRM_LD_3, PRM_LD_4, PRM_LD_5, PRM_LD_6,              // Land Prompt: Bits 1 - 3: Land Index, Bit 7 = Confirm (1) or Unconfirmed (0)
            PRM_LD_CONFIRM = 1 << 7,
        };

        static inline uint8_t _text_index = 0;
        static inline uint16_t _text_flags = TXT_NULL;
        static inline Prompt_Type _prompt_type = PROMPT_NULL;
        static inline uint8_t _prompt_flags = PRM_NULL;

        static void resetText() {
            _text_index = 0;
            _text_flags = TXT_NULL;
        }

        static bool textIsActive() { return ~_text_flags & TXT_WAIT_TXT; }
        static void textActivate() { _text_flags &= ~TXT_WAIT_TXT; }
        static void textDeactivate() { _text_flags |= TXT_WAIT_TXT; }
        
        static void resetPrompt() {
            _text_flags &= ~TXT_WAIT_PROMPT;
            _prompt_type = PROMPT_NULL;
            _prompt_flags = PRM_NULL;
        }

        static bool promptIsActive() { return _text_flags & TXT_WAIT_PROMPT; }

        static void activatePrompt(Prompt_Type type) {
            textDeactivate();
            _text_flags |= TXT_WAIT_PROMPT;
            _prompt_type = type;
        }

        template <typename Y, typename N>
        static void promptYN(Y actionY, N actionN) {
            if (_prompt_type != PROMPT_YN) {
                return;
            }

            if (gState.gCMD) {
                // Displayed as " ->yes  no  "
                std::string text;

                if (_prompt_flags & PRM_YN_YES) {
                    if (gState.gInput->keyPressed(SDL_SCANCODE_RIGHT)) {
                        _prompt_flags &= ~PRM_YN_YES;
                    }
                }
                else {
                    if (gState.gInput->keyPressed(SDL_SCANCODE_LEFT)) {
                        _prompt_flags |= PRM_YN_YES;
                    }
                }
                if (gState.gInput->keyPressed(SDL_SCANCODE_RETURN)) {
                    _prompt_flags |= PRM_YN_CONFIRM;
                }

                text = (_prompt_flags & PRM_YN_YES) 
                    ? gState.gYAML["Prompt_YN"]["text_y"].as<std::string>()
                    : gState.gYAML["Prompt_YN"]["text_n"].as<std::string>();
                std::cout << "\r" << text << "  ";
            }
            else {
                /* Display Yes/No Component and other stuff */
            }

            if (_prompt_flags & PRM_YN_CONFIRM) {
                (_prompt_flags & PRM_YN_YES) ? actionY() : actionN();
                resetPrompt();
            }
        }

        static int promptMarket(uint8_t m1, uint8_t m2, uint8_t m3) {
            if (_prompt_type != PROMPT_MARKET) {
                return -1;
            }

            if (gState.gCMD) {
                // Displayed as "  ->market_1    market_2    market_3   "
                std::string market_text1, market_text2, market_text3;

                if (_prompt_flags & PRM_MK_M1) {
                    if (gState.gInput->keyPressed(SDL_SCANCODE_RIGHT)) {
                        _prompt_flags ^= PRM_MK_M1;
                        _prompt_flags ^= PRM_MK_M2;
                    }

                    if (_prompt_flags & PRM_MK_CONFIRM) {
                        resetPrompt();
                        return m1;
                    }
                }
                else if (_prompt_flags & PRM_MK_M2) {
                    if (gState.gInput->keyPressed(SDL_SCANCODE_LEFT)) {
                        _prompt_flags ^= PRM_MK_M2;
                        _prompt_flags ^= PRM_MK_M1;
                    }
                    if (gState.gInput->keyPressed(SDL_SCANCODE_RIGHT)) {
                        _prompt_flags ^= PRM_MK_M2;
                        _prompt_flags ^= PRM_MK_M3;
                    }

                    if (_prompt_flags & PRM_MK_CONFIRM) {
                        resetPrompt();
                        return m2;
                    }
                }
                else if (_prompt_flags & PRM_MK_M3) {
                    if (gState.gInput->keyPressed(SDL_SCANCODE_LEFT)) {
                        _prompt_flags ^= PRM_MK_M3;
                        _prompt_flags ^= PRM_MK_M2;
                    }

                    if (_prompt_flags & PRM_MK_CONFIRM) {
                        resetPrompt();
                        return m3;
                    }
                }
                else {
                    _prompt_flags = PRM_MK_M1;
                }

                if (gState.gInput->keyPressed(SDL_SCANCODE_RETURN)) {
                    _prompt_flags |= PRM_MK_CONFIRM;
                }

                market_text1 = ((_prompt_flags & PRM_MK_M1) ? "->" : "    ")
                    + gState.gMarket[m1]["name"].as<std::string>();
                market_text2 = ((_prompt_flags & PRM_MK_M2) ? "->" : "    ")
                    + gState.gMarket[m2]["name"].as<std::string>();
                market_text3 = ((_prompt_flags & PRM_MK_M3) ? "->" : "    ")
                    + gState.gMarket[m3]["name"].as<std::string>();
                
                std::cout << "\r" << market_text1 << "  " << market_text2 << "  " << market_text3 << "  ";
            }
            else {

            }
            return -1;
        }

        static int promptLand(const std::vector<uint8_t>& available_land) {
            if (_prompt_type != PROMPT_LAND) {
                return -1;
            }

            if (gState.gInput->keyPressed(SDL_SCANCODE_RIGHT)) {
                if (_prompt_flags < std::ranges::max(available_land)) {
                    _prompt_flags++;
                    while (std::ranges::find(available_land, _prompt_flags) == available_land.end()) {
                        _prompt_flags++;
                    }
                }
            }
            if (gState.gInput->keyPressed(SDL_SCANCODE_LEFT)) {
                if (_prompt_flags > std::ranges::min(available_land)) {
                    _prompt_flags--;
                    while (std::ranges::find(available_land, _prompt_flags) == available_land.end()) {
                        _prompt_flags--;
                    }
                }
            }
            if (gState.gInput->keyPressed(SDL_SCANCODE_RETURN)) {
                _prompt_flags |= PRM_LD_CONFIRM;
            }

            if (_prompt_flags & PRM_LD_CONFIRM) {
                uint8_t index = _prompt_flags - PRM_LD_CONFIRM;
                resetPrompt();
                return --index;
            }

            if ((_prompt_flags < PRM_LD_1) || (_prompt_flags > PRM_LD_6)) {
                _prompt_flags = PRM_LD_1;
            }

            std::cout << "\r" << " [" << std::to_string(_prompt_flags) << "]  ";

            return -1;
        }

    };

    

}
// namespace TR