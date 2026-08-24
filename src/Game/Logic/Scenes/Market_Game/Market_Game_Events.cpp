#include "Engine/Graphics/AssetManager.hpp"

#include "Game/Logic/Scenes.hpp"
#include "Game/Objects/Components/MarketGameComponents.hpp"
#include "Game/Objects/Systems/MarketGameSystems.hpp"

namespace TR {

	void Market_Game::introScreen() {
		if (gState.gCMD) {
			if (TextManager::textIsActive()) {
				std::cout << "\n" << gState.gYAML["Game_Intro"]["text"].as<std::string>();
				TextManager::textDeactivate();
			}
			else {
				if (gState.gInput->keyPressed(SDL_SCANCODE_RETURN)) {
					_market_scene_state = MG_First_Turn_Question;
					TextManager::textActivate();
				}
			}
		}
		else {
			/* Display intro textbox */
		}
	}

	void Market_Game::firstTurnQuestion() {
		if (gState.gCMD) {
			if (TextManager::textIsActive()) {
				std::cout << "\n" << gState.gYAML["First_Turn"]["text"] << "\n";
				TextManager::activatePrompt(TextManager::PROMPT_YN);
			}
		}
		else {
			/* Display dialogue for first time playing game */
		}

		TextManager::promptYN(
			[=]() {_market_scene_state = MG_Guide_Screen; },
			[=]() {_market_scene_state = MG_Market_Prompt;}
		);

	}

	void Market_Game::guideScreen() {
		if (gState.gCMD) {
			if (TextManager::textIsActive()) {
				std::cout << "\n";
				std::cout << gState.gYAML["Game_Explanation"][TextManager::_text_index]["text"].as<std::string>();
				if (gState.gYAML["Game_Explanation"][TextManager::_text_index]["prompt_type"].IsDefined()) {
					TextManager::activatePrompt(TextManager::PROMPT_YN);
				}
				else {
					TextManager::_text_index++;
				}
				TextManager::textDeactivate();
			}
			else {
				if (TextManager::promptIsActive()) {
					TextManager::promptYN(
						[=]() {TextManager::resetText();},
						[=]() {TextManager::resetText(); _market_scene_state = MG_Market_Prompt;}
					);
				}
				else {
					if (gState.gInput->keyPressed(SDL_SCANCODE_RETURN)) {
						TextManager::textActivate();
					}
				}
			}
		}
		else {
			/* Display all guide directions with the textboxes */
		}
	}

	void Market_Game::marketPrompt(uint8_t tier) {
		static Market_ID* new_market = new Market_ID(MID_Null);
		auto isTier = [&](YAML::detail::iterator_value item) 
			{return item["tier"].as<int>() > tier;};
		auto currentScript = gState.gYAML["Market_Preview"][TextManager::_text_index];

		if (gState.gCMD) {
			if (TextManager::textIsActive()) {
				std::cout << "\n\n";
				std::cout << currentScript["text"].as<std::string>() << "\n";
				TextManager::_text_index++;
				TextManager::textDeactivate();

				if (currentScript["prompt_type"].as<std::string>() == "market_display") {
					if (auto market = std::find_if(gState.gMarket.begin(), gState.gMarket.end(), isTier); 
						market != gState.gMarket.end()) {
						std::cout << (*market)["name"].as<std::string>();
					}
				}
				else if (currentScript["prompt_type"].as<std::string>() == "market_prompt") {
					TextManager::activatePrompt(TextManager::PROMPT_MARKET);
				}
				else if (currentScript["prompt_type"].as<std::string>() == "land_prompt") {
					TextManager::activatePrompt(TextManager::PROMPT_LAND);
				}
			}
			else {
				if (TextManager::promptIsActive()) {
					if (TextManager::_prompt_type == TextManager::PROMPT_MARKET) {
						if (auto market_index = TextManager::promptMarket(1, 2, 3); market_index >= 0) {
							*new_market = marketStrToID.at(gState.gMarket[market_index]["ID"].as<std::string>());
						}
					}
					else if (TextManager::_prompt_type == TextManager::PROMPT_LAND) {
						auto& current_player = gState.gPlayer->player_data->getLand();
						if (auto land_index = TextManager::promptLand(current_player->availableLand());
							land_index != -1) {
							this->addingMarket(*new_market, land_index);
							delete new_market;
							new_market = nullptr;
							_market_scene_state = MG_Turn_Start;
							TextManager::textActivate();
						}
					}
				}
				else {
					if (gState.gInput->keyPressed(SDL_SCANCODE_RETURN)) {
						TextManager::textActivate();
					}
				}
			}
		}
		else {
			/* Display market prompt dialogue */
		}

	}

	void Market_Game::addingMarket(Market_ID newMarket, int index) {
		auto market_name = "MARKET" + std::to_string(index);
		MarketComponent* market = gState.gECS->getComponent<MarketComponent>(gState.gECS->getEntity(market_name));
		market->market_ID = newMarket;
		*(market->data) = Market(newMarket);
	}

	void Market_Game::removingMarket() {

	}

	void Market_Game::turnStart() {
		if (gState.gCMD) {
			if (TextManager::textIsActive()) {
				std::cout << "\n" << gState.gYAML["Turn_Start"]["text"].as<std::string>() << "\n";
				TextManager::textDeactivate();
			}
			else {
				if (gState.gInput->keyPressed(SDL_SCANCODE_RETURN)) {
					_market_scene_state = MG_Main_Game;
					TextManager::textActivate();
				}
			}
		}
		else {

		}
	}

	void Market_Game::showHUD() {
		if (gState.gCMD) {
			if (TextManager::textIsActive()) {
				auto& player_data = gState.gPlayer->player_data;

				std::cout << "\nCurrent Player: " <<  gState.gPlayer->_char_dict.at(gState.gPlayer->current_char) << " " << player_data->getType();
				std::cout << "\nTotal Current Profit: " << std::to_string(player_data->getProfit());
				std::cout << "\nCurrent Markets: " << player_data->getLand()->getMarketList();
				TextManager::textDeactivate();
			}
			else {
				if (gState.gInput->keyPressed(SDL_SCANCODE_RETURN)) {
					TextManager::textActivate();
				}
			}
		}
		else {

		}
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