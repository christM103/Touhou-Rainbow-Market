#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <map>

#include "Game/Logic/Enums.hpp"

namespace TR {

    // Const Game Values
    inline const int NUMBER_OF_LOTS = 6;

    /// @brief Player_ID to String dictionary
    inline const std::unordered_map<Player_ID, std::string_view> PLAYER_STATE_TO_STR{
        { Player_ID::Player_Null, "PLAYER0" },
        { Player_ID::Player_1, "PLAYER1" },
        { Player_ID::Player_2, "PLAYER2" },
        { Player_ID::Player_3, "PLAYER3" },
        { Player_ID::Player_4, "PLAYER4" }
    };

    /// @brief Char_State to String dictionary
    inline const std::unordered_map<Char_State, std::string> CHAR_STATE_TO_STR{
        { Char_State::Null, "Null" },
        { Char_State::Reimu, "Reimu" },
        { Char_State::Marisa, "Marisa" },
        { Char_State::Sanae, "Sanae" },
        { Char_State::Flandre, "Flandre" },
        { Char_State::Youmu, "Youmu" },
        { Char_State::Tewi, "Tewi" },
        { Char_State::Koishi, "Koishi" }
    };

    /// @brief Land_ID to Entity Name dictionary
    inline const std::unordered_map<Land_ID, std::string_view> LAND_STATE_TO_STR = {
        { Land_ID::Land_1, "MARKET0" },
        { Land_ID::Land_2, "MARKET1" },
        { Land_ID::Land_3, "MARKET2" },
        { Land_ID::Land_4, "MARKET3" },
        { Land_ID::Land_5, "MARKET4" },
        { Land_ID::Land_6, "MARKET5" }
    };

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