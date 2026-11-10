#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <map>

#include "Game/Logic/Enums.hpp"

namespace TR {

    // Const Game Values
    inline const int NUMBER_OF_LOTS = 6;
    inline const int NUMBER_OF_CHARACTERS = 8;

    // Action States Values
    inline const Land_States ACTION_INFLICTED_FLAGS = Land_States::Kogasa_Token;

    /// @brief Player_ID to String
    inline static constexpr std::string PlayerIDToStr(Player_ID id) noexcept
    {
        switch (id) {
            case Player_ID::Player_Null: return "PLAYER0";
            case Player_ID::Player_1:    return "PLAYER1";
            case Player_ID::Player_2:    return "PLAYER2";
            case Player_ID::Player_3:    return "PLAYER3";
            case Player_ID::Player_4:    return "PLAYER4";
        }
        return {};
    }

    /// @brief Char_State to String
    inline static constexpr std::string CharStateToStr(Char_State state) noexcept
    {
        switch (state) {
            case Char_State::Null:    return "Null";
            case Char_State::Reimu:   return "Reimu";
            case Char_State::Marisa:  return "Marisa";
            case Char_State::Sanae:   return "Sanae";
            case Char_State::Flandre: return "Flandre";
            case Char_State::Youmu:   return "Youmu";
            case Char_State::Tewi:    return "Tewi";
            case Char_State::Koishi:  return "Koishi";
        }
        return {};
    }

    /// @brief Land_ID to Entity Name
    inline static constexpr std::string LandIDToStr(Land_ID id) noexcept
    {
        switch (id) {
            case Land_ID::Land_1: return "MARKET0";
            case Land_ID::Land_2: return "MARKET1";
            case Land_ID::Land_3: return "MARKET2";
            case Land_ID::Land_4: return "MARKET3";
            case Land_ID::Land_5: return "MARKET4";
            case Land_ID::Land_6: return "MARKET5";
        }
        return {};
    }

    /// @brief Action_ID to Entity Name
    constexpr std::string_view ActionIDToStr(Action_ID id) noexcept
    {
        switch (id) {
            case Action_ID::A_NULL: return "A_NULL";

                // Player Character Actions
            case Action_ID::A_REIA: return "A_REIA";
            case Action_ID::A_REIB: return "A_REIB";
            case Action_ID::A_MARA: return "A_MARA";
            case Action_ID::A_MARB: return "A_MARB";

                // Market Actions
            case Action_ID::A_MYST: return "A_MYST";
            case Action_ID::A_KOGA: return "A_KOGA";
            case Action_ID::A_WRIG: return "A_WRIG";
            case Action_ID::A_KEIN: return "A_KEIN";
            case Action_ID::A_MORI: return "A_MORI";
            case Action_ID::A_HIFU: return "A_HIFU";
        }
        return {};
    }

    inline static constexpr std::string PlayerLandIDToStr(Player_ID p, Land_ID l) noexcept
    {
        return PlayerIDToStr(p) + LandIDToStr(l);
    }

    inline static constexpr std::string PlayerLandIDToStr(Player_ID p, int l) noexcept
    {
        return PlayerLandIDToStr(p, static_cast<Land_ID>(l));
    }

    constexpr Market_ID MarketStrToID(std::string str) {
        if (str == "MID_Null") { return Market_ID::MID_Null; }
        else if (str == "MID_Myst") { return Market_ID::MID_Myst; }
        else if (str == "MID_Koga") { return Market_ID::MID_Koga; }
        else if (str == "MID_Wrig") { return Market_ID::MID_Wrig; }
        else if (str == "MID_Kein") { return Market_ID::MID_Kein; }
        else if (str == "MID_Suwa") { return Market_ID::MID_Suwa; }
        else if (str == "MID_Rema") { return Market_ID::MID_Rema; }

        return Market_ID::MID_Null;
    }

    constexpr Action_ID ActionStrToID(std::string_view str) noexcept
    {
        if (str == "A_NULL") return Action_ID::A_NULL;

        // Player Character Actions
        if (str == "A_REIA") return Action_ID::A_REIA;
        else if (str == "A_REIB") { return Action_ID::A_REIB; }
        else if (str == "A_MARA") { return Action_ID::A_MARA; }
        else if (str == "A_MARB") { return Action_ID::A_MARB; }

        // Market Actions
        else if (str == "A_MYST") { return Action_ID::A_MYST; }
        else if (str == "A_KOGA") { return Action_ID::A_KOGA; }
        else if (str == "A_WRIG") { return Action_ID::A_WRIG; }
        else if (str == "A_KEIN") { return Action_ID::A_KEIN; }
        else if (str == "A_MORI") { return Action_ID::A_MORI; }
        else if (str == "A_HIFU") { return Action_ID::A_HIFU; }

        return Action_ID::A_NULL;
    }

    /// @brief YAML Placeholder dictionary
    inline std::unordered_map<std::string_view, std::string> TEXT_TEMP_VALUE = {
        { "turn_number", "" },
        { "player_char", "" },
        { "player_type", "" },
        { "player_profit", "" },
        { "player_lot", "" },
        { "game_timer", "" },
        { "player_act_mar", "" },
        { "market_active", "" },
        { "market_id", "" },
        { "player_act_pla", "" },
    };

    

    /* Prompt Enums */
    inline const std::vector<std::string> PROMPT_YN = { "Yes", "No" };
    inline const std::vector<std::string> PROMPT_LIST_CHAR = { "Null", "Reimu", "Marisa", "Sanae", "Flandre", "Youmu", "Tewi", "Koishi" };
    inline const std::vector<std::string> PROMPT_LIST_LOT = { "1", "2", "3", "4", "5", "6" };

    /* Paths */
    inline const std::string GFX_FOLDER = "assets/gfx/sprites/";
    inline const std::string TEXT_FOLDER = "assets/text/";
    inline const std::string DATA_FOLDER = "assets/data/";

    inline const std::string PATH_YAML_TITLE = TEXT_FOLDER + "text_title_screen.yaml";
    inline const std::string PATH_YAML_CHARSELECT = TEXT_FOLDER + "text_character_select.yaml";
    inline const std::string PATH_YAML_MARKETGAME = TEXT_FOLDER + "text_market_game.yaml";

    inline const std::string PATH_JSON_MARKET = DATA_FOLDER + "markets.json";
    inline const std::string PATH_JSON_ACTION = DATA_FOLDER + "actions.json";
}