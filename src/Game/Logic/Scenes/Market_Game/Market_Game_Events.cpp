#include "Engine/Graphics/AssetManager.hpp"

#include "Game/Logic/Scenes.hpp"
#include "Game/Objects/Components/MarketGameComponents.hpp"
#include "Game/Objects/Systems/MarketGameSystems.hpp"

namespace TR {
	void Market_Game::introScreen() {
		static bool text_completed = false;
		if (gState.gCMD) {
			if (!text_completed) {
				std::cout << "\n" << gState.gYAML["Game_Intro"]["text"].as<std::string>();
				text_completed = true;
			}
			if (gState.gInput->keyPressed(SDL_SCANCODE_RETURN)) {
				_market_scene_state = MG_First_Turn_Question;
			}
		}
		else {
		}
	}

	void Market_Game::firstTurnQuestion() {
		static bool text_completed = false;
		if (gState.gCMD) {
			if (!text_completed) {
				std::cout << "\n" << gState.gYAML["First_Turn"]["text"];
				text_completed = true;
			}
			/* Implement Yes/No Prompt */
			if (gState.gInput->keyPressed(SDL_SCANCODE_LEFT)) {								// Yss Selection
				_market_scene_state = MG_Guide_Screen;
			}
			else if (gState.gInput->keyPressed(SDL_SCANCODE_RIGHT)) {						// No Selection
				_market_scene_state = MG_Market_Prompt;
			}
		}
		else {
		}
	}

	void Market_Game::guideScreen() {
		static uint8_t text_index;
		enum Text_Flags : uint8_t { TXT_WAIT = 1 << 7, PROMPT_WAIT = 1 << 6 };
		if (text_index & TXT_WAIT) {
			if (text_index & PROMPT_WAIT) {
				/* Implement Yes/No Prompt */
				if (gState.gInput->keyPressed(SDL_SCANCODE_LEFT)) {								// Yss Selection
					text_index = 0;
				}
				else if (gState.gInput->keyPressed(SDL_SCANCODE_RIGHT)) {						// No Selection
					_market_scene_state = MG_Market_Prompt;
				}
			}
			else {
				if (gState.gInput->keyPressed(SDL_SCANCODE_RETURN)) {
					text_index -= TXT_WAIT;
				}
			}
		}
		else {
			std::cout << "\n" << gState.gYAML["Game_Explanation"][text_index]["text"].as<std::string>();
			if (gState.gYAML["Game_Explanation"][text_index]["prompt"].as<bool>()) {
				text_index += PROMPT_WAIT;
			}
			text_index++;
			text_index += TXT_WAIT;
		}
	}

	void Market_Game::marketPrompt() {
		static bool text_completed = false;
		if (!text_completed) {
			std::cout << "\n" << gState.gYAML["Market_Preview"]["text"].as<std::string>();
			std::cout << "\n" << gState.gYAML["Market_Preview"]["markets"][0].as<std::string>();
			text_completed = true;
		}

	}

	void Market_Game::addingMarket() {

	}
	void Market_Game::removingMarket() {

	}
	void Market_Game::turnStart() {

	}
	void Market_Game::showHUD() {

	}
	void Market_Game::hideHUD() {

	}
	void Market_Game::landEffect() {

	}
	bool Market_Game::countdownTimer() {
		return false;
	}

	void Market_Game::highlightMarket() {

	}
	void Market_Game::marketActionPrompt() {

	}
	void Market_Game::highlightPlayer() {

	}
	void Market_Game::playerActionPrompt() {

	}
	void Market_Game::actionSelf() {

	}
	void Market_Game::actionSelfAll() {

	}
	void Market_Game::actionOther() {

	}
	void Market_Game::actionOtherAll() {

	}
	void Market_Game::actionFailed() {

	}
	void Market_Game::actionSuccess() {

	}
	void Market_Game::turnEnd() {

	}
	void Market_Game::debriefScreen() {

	}
	void Market_Game::gameComplete() {

	}
}