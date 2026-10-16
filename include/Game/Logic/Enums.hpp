#pragma once

#include <cstdint>

namespace TR {

    /// @brief Current Scene States
    enum class Scene_ID : uint8_t {
        Null, Title, CharS, Main
    };

    /// @brief List of prompt flags
    enum class Prompt_Flags : uint8_t {
        Null = 0,

        PRM_YN_NO = 1, PRM_YN_YES = 0,                                                

        PRM_LD_1 = 1, PRM_LD_2, PRM_LD_3, PRM_LD_4, PRM_LD_5, PRM_LD_6,               
        PRM_LD_CONFIRM = 1 << 7,
    };

    /// @brief List of possible game states
    enum class Game_States : uint16_t {
        MG_Null_State,

        MG_Welcome_Screen,
        MG_First_Turn_Question,
        MG_Guide_Screen,
        MG_Intro_Market,
        MG_Market_Prompt,
        MG_Turn_Start,

        MG_Main_Game,
        MG_Highlight_Lot,
        MG_Highlight_Portrait,

        MG_Land_Action_Prompt,
        MG_Land_Action_Event,

        MG_Player_Action_Prompt,
        MG_Player_Action_Event,

        MG_Market_Choice,
        MG_Player_Choice,

        MG_Turn_End,
        MG_Turn_Debrief,

        MG_Game_End,

        MG_Paused = 1 << 15,

    };

    enum class Char_State : uint8_t {
        Null, Reimu, Marisa, Sanae, Flandre, Youmu, Tewi, Koishi
    };

}