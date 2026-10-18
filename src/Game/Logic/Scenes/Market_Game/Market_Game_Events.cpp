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
			// If timer is on, show alternative string
			bool timer = true;
			(timer) ? appendYAMLString("mkt_add_start") : appendYAMLString("mkt_add");
		}

		if (gState.gInput->keyPressed(SDL_SCANCODE_RETURN)) {
			clearGameTextString();

			if (_state_data.current_prompt == "prompt_yn") {
				if (_state_data.prompt_flags == Prompt_Flags::PRM_YN_NO) {
					swapState(Game_States::MG_Turn_Start);
					resetPromptAction();
					return;
				}
				resetPromptAction();

				if (tier == 1) {
					appendYAMLString("mkt_intro_1");
				}
				else if (tier == 2) {
					appendYAMLString("mkt_intro_2");
				}
				else if (tier == 3) {
					appendYAMLString("mkt_intro_3");
				}
				else {
					appendYAMLString("mkt_intro_all");
				}
			}
			else {
				resetPromptAction();
				swapState(Game_States::MG_Market_Select);
			}
		}
	}
	
	void Market_Game::marketSelection() {
		const auto& selectMarket = [=]() {
			resetPromptAction();
			uint8_t market_ind = static_cast<int>(_state_data.prompt_flags);
			std::string market_name = _state_data.market_queue[market_ind];
			_state_data.selected_market = Market::marketStrToID(market_name);
		};

		const auto& selectLot = [=]() -> MarketComponent* {
			resetPromptAction();
			uint8_t land_num = static_cast<uint8_t>(_state_data.prompt_flags);
			auto market_name = "MARKET" + std::to_string(land_num);
			auto market_entity = gState.gECS->getEntity(market_name);

			return gState.gECS->getComponent<MarketComponent>(market_entity);
		};

		if (isGameTextStringEmpty()) {
			appendYAMLString("mkt_add_sel");
		}
		
		if (gState.gInput->keyPressed(SDL_SCANCODE_RETURN)) {
			clearGameTextString();
			if (_state_data.current_prompt == "prompt_market") {
				selectMarket();
				appendYAMLString("mkt_add_loc");
			}
			else if (_state_data.current_prompt == "prompt_land") {
				
				MarketComponent* selected_lot = selectLot();

				if (selected_lot->market_active) {
					appendYAMLString("mkt_err_occup");
				}
				else {
					this->addingMarket(_state_data.selected_market, selected_lot);
					swapState(Game_States::MG_Turn_Start);
				}
			}
			else if (_state_data.current_prompt == "prompt_yn") {
				if (_state_data.prompt_flags == Prompt_Flags::PRM_YN_YES) {
					MarketComponent* selected_lot = selectLot();

					this->removingMarket(selected_lot);
					this->addingMarket(_state_data.selected_market, selected_lot);
					swapState(Game_States::MG_Turn_Start);
				}
				else {
					resetPromptAction();
					appendYAMLString("mkt_add_loc");
				}
			}
			
		}
	}

	void Market_Game::addingMarket(Market_ID newMarket, MarketComponent* current_land) {
		current_land->market_ID = newMarket;
		current_land->market_active = true;
		*(current_land->data) = Market(newMarket);
	}

	void Market_Game::removingMarket(MarketComponent* current_land) {
		current_land->market_ID = Market_ID::MID_Null;
		current_land->market_active = false;
		*(current_land->data) = Market(Market_ID::MID_Null);
	}

	void Market_Game::turnStart() {
		if (isGameTextStringEmpty()) {
			TEXT_TEMP_VALUE.at("turn_number") = std::to_string(gState.gTurns->current_turn);
			appendYAMLString("turn_start");
			substitutePlaceholder();
		}

		if (gState.gInput->keyPressed(SDL_SCANCODE_RETURN)) {
			showHUD();
			swapState(Game_States::MG_Main_Game);
		}
	}

	void Market_Game::mainGameScreen() {
		auto entity_name = gState.gECS->getEntity("HUD_DISPLAY");
		HUDComponent* hud_comp = gState.gECS->getComponent<HUDComponent>(entity_name);

		if (isHUDRunning()) {
			if (getDebugManager().isEnabled()) {
				if (isGameTextStringEmpty()) {
					appendYAMLString("hud_debug_text");
					substitutePlaceholder();
				}
			}
			
			if (gState.gInput->keyPressed(SDL_SCANCODE_X)) {
				swapState(Game_States::MG_Market_Prompt);
				hideHUD();
			}
		}

		if (has_flag(hud_comp->hudFlags, HUD_Flags::Focus_Market)) {
			swapState(Game_States::MG_Highlight_Lot);
		} else if (has_flag(hud_comp->hudFlags, HUD_Flags::Focus_Player)) {
			swapState(Game_States::MG_Highlight_Portrait);
		}
	}

	void Market_Game::highlightLand() {
		auto entity_name = gState.gECS->getEntity("HUD_DISPLAY");
		HUDComponent* hud_comp = gState.gECS->getComponent<HUDComponent>(entity_name);

		if (getDebugManager().isEnabled()) {
			if (isGameTextStringEmpty()) {
				appendYAMLString("land_debug_txt");
				substitutePlaceholder();
			}
		}
		else {
			/* Display highlighted land */
		}

		if (gState.gInput->keyPressed(SDL_SCANCODE_Z)) {
			auto market_name = LAND_STATE_TO_STR.at(hud_comp->highlightedLand).data();
			auto market_entity = gState.gECS->getEntity(market_name);
			MarketComponent* market = gState.gECS->getComponent<MarketComponent>(market_entity);

			if (gState.gPlayer->market_actions && market->market_ID != Market_ID::MID_Null) {
				swapState(Game_States::MG_Land_Action_Prompt);
			}
			else {
				// "Nope, can't use anymore actions for this turn..."
			}
		}
		else if (gState.gInput->keyPressed(SDL_SCANCODE_X)) {
			hud_comp->highlightedLand = Land_ID::Land_Null;
			hud_comp->hudFlags &= ~HUD_Flags::Focus_Market;
			swapState(Game_States::MG_Main_Game);
		}

	}

	void Market_Game::landActionPrompt() {
		actionPrompt(Game_States::MG_Highlight_Lot);
	}

	void Market_Game::highlightPlayer() {
		auto entity_name = gState.gECS->getEntity("HUD_DISPLAY");
		HUDComponent* hud_comp = gState.gECS->getComponent<HUDComponent>(entity_name);

		if (getDebugManager().isEnabled()) {
			if (isGameTextStringEmpty()) {
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
			hud_comp->hudFlags &= ~HUD_Flags::Focus_Player;
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
				auto entity_name = gState.gECS->getEntity("HUD_DISPLAY");
				HUDComponent* hud_comp = gState.gECS->getComponent<HUDComponent>(entity_name);

				if (prev_state == Game_States::MG_Highlight_Lot) {
					gState.gPlayer->market_actions--;
					hud_comp->highlightedLand = Land_ID::Land_Null;
					hud_comp->hudFlags &= ~HUD_Flags::Focus_Market;
				}
				else if (prev_state == Game_States::MG_Highlight_Portrait) {
					hud_comp->hudFlags &= ~HUD_Flags::Focus_Player;
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

	void Market_Game::showHUD() {
		auto entity_name = gState.gECS->getEntity("HUD_DISPLAY");
		HUDComponent* hud_comp = gState.gECS->getComponent<HUDComponent>(entity_name);

		if (!hud_comp->isHUDEnabled) {
			hud_comp->isHUDEnabled = true;
		}
	}

	void Market_Game::hideHUD() {
		auto entity_name = gState.gECS->getEntity("HUD_DISPLAY");
		HUDComponent* hud_comp = gState.gECS->getComponent<HUDComponent>(entity_name);

		if (hud_comp->isHUDEnabled) {
			hud_comp->isHUDEnabled = false;
		}
	}

	bool Market_Game::isHUDRunning() {
		auto entity_name = gState.gECS->getEntity("HUD_DISPLAY");
		HUDComponent* hud_comp = gState.gECS->getComponent<HUDComponent>(entity_name);

		return hud_comp->isHUDEnabled;
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
}