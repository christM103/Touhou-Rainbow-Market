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

    enum class Land_ID : uint8_t {
        Land_1, Land_2, Land_3, Land_4, Land_5, Land_6, Land_Null = 255
    };

    enum class Market_ID : uint8_t { 
        MID_Null, 
        MID_Myst, 
        MID_Koga, 
        MID_Wrig, 
        MID_Kein, 
        MID_Suwa, 
        MID_Rema, 
    };

    /// @brief Land States
    enum class Land_States : uint64_t {
        Bitmask_Enabled = 0,

        Null = 0ULL,                             // (Null)
        Free = 1ULL << 0,                        // (Free or Occupied)
        Active = 1ULL << 1,                      // (Active or Shut Down)
        Immunity = 1ULL << 2,                    // (Land Immunity)

        Reimu_Orb = 1ULL << 16,                   // (Reimu Orb protection)
        Reimu_TalisA = 1ULL << 17,                // (Reimu Talisman A (Seal), Shut down a select open market for 2 turns
        Reimu_TalisB = 1ULL << 18,                // (Reimu Talisman B (Barrier), Grant immunity to a select open market for 2 turns

        Kogasa_Token = 1ULL << 32,
        Keine_Shutdown = 1ULL << 33,
    };

    enum class Action_ID : uint8_t {
        A_NULL = 0,

        // Player Character Actions
        A_REIA = 1,
        A_REIB = 2,
        A_MARA = 3,
        A_MARB = 4,


        // Market Actions
        A_MYST = 33,
        A_KOGA = 34,
        A_WRIG = 35,
        A_KEIN = 36,
        A_MORI = 37,
        A_HIFU = 38,
    };

    enum class Action_Type : uint8_t {
        Null, Profit, Shutdown, Immunity, Profit_Rates, Sell, Destroy, Other,
    };

    enum class Action_States : uint8_t {
        Null = 0,
        Bitmask_Enabled = 0,

        Active = 1 << 0,
        Successful = 1 << 1,
        Animated = 1 << 2,
        Complete = 1 << 7,
    };

    /// @brief List of possible game states
    enum class Game_States : uint16_t {
        MG_Null_State,

        MG_Welcome_Screen,
        MG_First_Turn_Question,
        MG_Guide_Screen,
        MG_Intro_Market,

        MG_Market_Prompt,
        MG_Market_Select,

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

    enum class Player_ID : uint8_t {
        Player_Null, Player_1, Player_2, Player_3, Player_4
    };

    enum class Player_Type : bool {
        Type_1, Type_2
    };

    enum class Action_Flags : uint8_t {
        Null = 0,
        Market_Action_1 = 1 << 0,
        Market_Action_2 = 1 << 1,
        Player_Action = 1 << 2,
    };

    enum class HUD_Flags : uint32_t {
        Null = 0,
        Bitmask_Enabled = 0,

        Enable_HUD = 1 << 0,
        Allow_Input = 1 << 1,

        Show_Portrait = 1 << 8,
        Show_Profits = 1 << 9,
        Show_Power = 1 << 10,
        Show_Markets = 1 << 11,
        Show_Timer = 1 << 12,

        Focus_Market = 1 << 16,
        Focus_Player = 1 << 17,
    };

    // Enum Bitmask Definitions

    template <typename E>
    struct enable_bitmask : std::false_type {};

    template <typename E>
    concept Bitmask = std::is_enum_v<E> && requires { E::Bitmask_Enabled; };

    // Bitmask Operator Overloading

    template <Bitmask E>
    constexpr E operator|(E a, E b) {
        using T = std::underlying_type_t<E>;
        return static_cast<E>(static_cast<T>(a) | static_cast<T>(b));
    }

    template <Bitmask E>
    constexpr E operator&(E a, E b) {
        using T = std::underlying_type_t<E>;
        return static_cast<E>(static_cast<T>(a) & static_cast<T>(b));
    }

    template <Bitmask E>
    constexpr E operator^(E a, E b) {
        using T = std::underlying_type_t<E>;
        return static_cast<E>(static_cast<T>(a) ^ static_cast<T>(b));
    }

    template <Bitmask E>
    constexpr E operator~(E a) {
        using T = std::underlying_type_t<E>;
        return static_cast<E>(~static_cast<T>(a));
    }

    template <Bitmask E> constexpr E& operator|=(E& a, E b) { return a = a | b; }
    template <Bitmask E> constexpr E& operator&=(E& a, E b) { return a = a & b; }
    template <Bitmask E> constexpr E& operator^=(E& a, E b) { return a = a ^ b; }

    template <Bitmask E>
    constexpr bool has_flag(E value, E flag) {
        return (value & flag) == flag;
    }

    template <Bitmask E>
    constexpr void enable_flag(E value, E flag) {
        value |= flag;
    }

    template <Bitmask E>
    constexpr void disable_flag(E value, E flag) {
        value &= ~flag;
    }
}