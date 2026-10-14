#include <format>

#include "Engine/Graphics/AssetManager.hpp"

#include "Game/Logic/Scenes.hpp"
#include "Game/Objects/Components/MarketGameComponents.hpp"
#include "Game/Objects/Systems/MarketGameSystems.hpp"

using Engine::DebugComponent;

namespace TR {
	

	void Market_Game::introScreen() {
		if (isGameTextStringEmpty()) {
			appendYAMLString("game_intro");
		}

		if (getDebugManager().isEnabled()) {
			if (gState.gInput->keyPressed(SDL_SCANCODE_RETURN)) {
				swapState(Game_States::MG_First_Turn_Question);
			}
		}
		else {
			/* Display intro textbox */
		}
	}

	void Market_Game::firstTurnQuestion() {
		if (isGameTextStringEmpty()) {
			appendYAMLString("first_turn");
		}

		if (!getDebugManager().isEnabled()) {
			/* Display dialogue for first time playing game */
		}

		if (gState.gInput->keyPressed(SDL_SCANCODE_RETURN)) {
			(_state_data.prompt_flags == Prompt_Flags::PRM_YN_YES)
				? swapState(Game_States::MG_Guide_Screen) 
				: swapState(Game_States::MG_Market_Prompt);
			resetPromptAction();
		}
	}

	void Market_Game::guideScreen() {
		if (isGameTextStringEmpty()) {
			appendYAMLString("game_explain");
		}

		if (!getDebugManager().isEnabled()) {
			/* Display all guide directions with the textboxes */
		}

		if (gState.gInput->keyPressed(SDL_SCANCODE_RETURN)) {
			if (getDebugManager().isPromptShown()) {
				(_state_data.prompt_flags == Prompt_Flags::PRM_YN_NO) 
					? swapState(Game_States::MG_Market_Prompt) 
					: swapState(Game_States::MG_Guide_Screen);
				resetPromptAction();
				return;
			}
			clearGameTextString();
			textIndexNext();
		}
	}

	void Market_Game::marketPrompt(uint8_t tier) {		
		if (isGameTextStringEmpty()) {
			appendYAMLString("market_intro");
		}

		if (gState.gInput->keyPressed(SDL_SCANCODE_RETURN)) {
			if (_state_data.current_prompt == "prompt_market") {
				uint8_t market_ind = static_cast<int>(_state_data.prompt_flags);
				std::string market_name = _state_data.market_queue[market_ind];
				_state_data.selected_market = Market::marketStrToID(market_name);
			}
			else if (_state_data.current_prompt == "prompt_land") {
				uint8_t land_num = static_cast<uint8_t>(_state_data.prompt_flags);
				this->addingMarket(_state_data.selected_market, land_num);
				swapState(Game_States::MG_Turn_Start);
				resetPromptAction();
				return;
			}
			resetPromptAction();
			clearGameTextString();
			textIndexNext();
		}

	}

	void Market_Game::addingMarket(Market_ID newMarket, int index) {
		auto market_name = "MARKET" + std::to_string(index);
		auto market_entity = gState.gECS->getEntity(market_name);
		MarketComponent* market = gState.gECS->getComponent<MarketComponent>(market_entity);
		market->market_ID = newMarket;
		*(market->data) = Market(newMarket);
	}

	void Market_Game::removingMarket() {
		/* Removing the Market*/
	}

	void Market_Game::turnStart() {
		if (isGameTextStringEmpty()) {
			// TEXT_TEMP_VALUE.at("turn_number") for replacing turn numbers;
			appendYAMLString("turn_start");
		}

		if (gState.gInput->keyPressed(SDL_SCANCODE_RETURN)) {
			swapState(Game_States::MG_Main_Game);
		}
	}

	void Market_Game::showHUD() {
		if (getDebugManager().isEnabled()) {
			auto& player_data = gState.gPlayer->player_data;
			if (isGameTextStringEmpty()) {
				TEXT_TEMP_VALUE.at("player_char") = CHAR_STATE_TO_STR.at(gState.gPlayer->current_char);
				TEXT_TEMP_VALUE.at("player_type") = std::to_string(player_data->getType());
				TEXT_TEMP_VALUE.at("player_profit") = std::format("{:.2f}", player_data->getProfit());
				TEXT_TEMP_VALUE.at("player_lot") = player_data->getLand()->getMarketList();
				TEXT_TEMP_VALUE.at("game_timer") = std::to_string(0);

				appendYAMLString("hud_debug_text");
				substitutePlaceholder();
			}
		}
		else {
			/* Display HUD graphics */
		}

		if (gState.gInput->keyPressed(SDL_SCANCODE_Z)) {
			swapState(Game_States::MG_Highlight_Portrait);
		}
		else if (gState.gInput->keyPressed(SDL_SCANCODE_1)) {
			_state_data.current_land = Land_ID::Land_1;
		}
		else if (gState.gInput->keyPressed(SDL_SCANCODE_2)) {
			_state_data.current_land = Land_ID::Land_2;
		}
		else if (gState.gInput->keyPressed(SDL_SCANCODE_3)) {
			_state_data.current_land = Land_ID::Land_3;
		}
		else if (gState.gInput->keyPressed(SDL_SCANCODE_4)) {
			_state_data.current_land = Land_ID::Land_4;
		}
		else if (gState.gInput->keyPressed(SDL_SCANCODE_5)) {
			_state_data.current_land = Land_ID::Land_5;
		}
		else if (gState.gInput->keyPressed(SDL_SCANCODE_6)) {
			_state_data.current_land = Land_ID::Land_6;
		}

		if (_state_data.current_land != Land_ID::Land_Null) {
			swapState(Game_States::MG_Highlight_Lot);
		}
	}

	void Market_Game::hideHUD() {
		if (getDebugManager().isEnabled()) {

		}
		else {

		}
	}
	void Market_Game::landEffect() {
		if (getDebugManager().isEnabled()) {

		}
		else {

		}
	}
	bool Market_Game::countdownTimer() {
		return false;
	}

	void Market_Game::highlightLand() {
		auto market_name = "MARKET" + std::to_string(static_cast<int>(_state_data.current_land));
		auto market_entity = gState.gECS->getEntity(market_name);
		MarketComponent* market = gState.gECS->getComponent<MarketComponent>(market_entity);

		if (getDebugManager().isEnabled()) {
			if (isGameTextStringEmpty()) {
				TEXT_TEMP_VALUE.at("player_act_mar") = std::to_string(gState.gPlayer->market_actions);
				TEXT_TEMP_VALUE.at("market_active") = std::to_string(market->market_active);
				TEXT_TEMP_VALUE.at("market_id") = std::to_string(static_cast<int>(market->market_ID));

				appendYAMLString("land_debug_txt");
				substitutePlaceholder();
			}
		}
		else {
			/* Display highlighted land */
		}

		if (gState.gInput->keyPressed(SDL_SCANCODE_Z)) {
			if (gState.gPlayer->market_actions && market->market_ID != Market_ID::MID_Null) {
				swapState(Game_States::MG_Land_Action_Prompt);
			}
			else {
				// "Nope, can't use anymore actions for this turn..."
			}
		}
		else if (gState.gInput->keyPressed(SDL_SCANCODE_X)) {
			_state_data.current_land = Land_ID::Land_Null;
			swapState(Game_States::MG_Main_Game);
		}

	}

	void Market_Game::landActionPrompt() {
		actionPrompt(Game_States::MG_Highlight_Lot);
	}

	void Market_Game::highlightPlayer() {
		if (getDebugManager().isEnabled()) {
			if (isGameTextStringEmpty()) {
				TEXT_TEMP_VALUE.at("player_char") = CHAR_STATE_TO_STR.at(gState.gPlayer->current_char);
				TEXT_TEMP_VALUE.at("player_act_pla") = TEXT_TEMP_VALUE.at("player_act_mar");

				appendYAMLString("plyr_debug_txt");
				substitutePlaceholder();
			}
		}
		else {
			/* Display portrait highlight */
		}

		if (gState.gInput->keyPressed(SDL_SCANCODE_Z)) {
			if (gState.gPlayer->player_actions) {
				swapState(Game_States::MG_Player_Action_Prompt);
			}
			else {
				// "Nope, can't use anymore actions for this turn..."
			}
		}
		else if (gState.gInput->keyPressed(SDL_SCANCODE_X)) {
			swapState(Game_States::MG_Main_Game);
		}
	}

	void Market_Game::playerActionPrompt() {
		actionPrompt(Game_States::MG_Highlight_Portrait);
	}

	void Market_Game::actionPrompt(Game_States prev_state) {
		if (getDebugManager().isEnabled()) {
			getDebugManager().showPrompt(PROMPT_YN);
		}
		else {
			/* Display action prompt (probably textbox) */
		}

		if (isGameTextStringEmpty()) {
			appendYAMLString("action_prompt");
		}

		if (gState.gInput->keyPressed(SDL_SCANCODE_RETURN)) {
			if (_state_data.prompt_flags == Prompt_Flags::PRM_YN_YES) {
				if (prev_state == Game_States::MG_Highlight_Lot) {
					gState.gPlayer->market_actions--;
					_state_data.current_land = Land_ID::Land_Null;
				}
				else if (prev_state == Game_States::MG_Highlight_Portrait) {
					gState.gPlayer->player_actions--;
				}
				swapState(Game_States::MG_Main_Game);
			}
			else {
				swapState(prev_state);
			}
			resetPromptAction();
		}
	}

	void Market_Game::actionManager() {
		/* Actions happen here */
	}
	void Market_Game::actionFailed() {
		/* In the case the action fails */
	}
	void Market_Game::actionSuccess() {
		/* In the case the action succeeds */
	}
	void Market_Game::turnEnd() {
		/* For the end of the turn */
	}
	void Market_Game::debriefScreen() {
		/* For the debrief screen */
	}
	void Market_Game::gameComplete() {
		/* When all turns have been completed*/
	}
}