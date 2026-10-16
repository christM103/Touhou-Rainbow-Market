#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <map>

#include "Game/Logic/Enums.hpp"

namespace TR {

    /// @brief Char_State to String dictionary
    inline const std::map<Char_State, std::string> CHAR_STATE_TO_STR{
        { Char_State::Null, "Null" },
        { Char_State::Reimu, "Reimu" },
        { Char_State::Marisa, "Marisa" },
        { Char_State::Sanae, "Sanae" },
        { Char_State::Flandre, "Flandre" },
        { Char_State::Youmu, "Youmu" },
        { Char_State::Tewi, "Tewi" },
        { Char_State::Koishi, "Koishi" }
    };

    /// @brief YAML Placeholder dictionary
    inline std::unordered_map<std::string, std::string> TEXT_TEMP_VALUE = {
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