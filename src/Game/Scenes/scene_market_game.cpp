#include "Game/logic.hpp"
#include "Game/logic_obj.hpp"
#include "Engine/Graphics/AssetManager.hpp"

namespace TR {
	using Text = TextBox::Text_Box_Transitions;

	Market_Game::Market_Game() {
		_currState = SC_Main;
		_nextState = _currState;
		_market_scene_state ^= MG_Intro_Sceen;

		test_textbox.enableAttr(Text::TXT_ACTIVE);
		test_textbox.enableAttr(Text::TXT_UP_DOWN);
	}

	Market_Game::Market_Game(std::vector<std::shared_ptr<TR::Player_Data>> players) {}

	Market_Game::~Market_Game() {}

	bool Market_Game::create(SDL_Renderer* renderer, Engine::Engine* gEngine, Sprite_Map& sprite_set, Player_Set& player_set) {

		/* Texture Initialization */

		// Loading Background
		gEngine->getAssetManager()->loadTexture("assets/gfx/sprites/Market_Game/Placeholder_Game_BGLand.png", "BGO", renderer);
		gEngine->getAssetManager()->loadTexture("assets/gfx/sprites/Market_Game/Placeholder_Game_BGCLoud.png", "BGOCloud", renderer);
		
		// Loading Character Portraits
		gEngine->getAssetManager()->loadTexture("assets/gfx/sprites/Common/Placeholder_Portrait_Null.png", "CHAR_NUL", renderer);
		gEngine->getAssetManager()->loadTexture("assets/gfx/sprites/Market_Game/Placeholder_Portrait_R_S.png", "CHAR_REI", renderer);
		gEngine->getAssetManager()->loadTexture("assets/gfx/sprites/Market_Game/Placeholder_Portrait_M_S.png", "CHAR_MAR", renderer);

		// Loading Markets
		gEngine->getAssetManager()->loadTexture("assets/gfx/sprites/Market_Game/Placeholder_Game_MarketFree.png", "MKT_NULL", renderer);
		gEngine->getAssetManager()->loadTexture("assets/gfx/sprites/Market_Game/Placeholder_Game_MarketWriggle.png", "MKT_WRIG", renderer);

		// Loading Text
		gEngine->getAssetManager()->storeTexture(balance_text.load(renderer), "TEXT_PBAL", renderer);

		/* Sprite Creation */

		// Create Background Sprite
		sprite_set.insert({ "background",
			std::make_unique<Engine::Sprite>(gEngine->getAssetManager()->getTexture("BGO"), 1280, 720) });
		sprite_set.insert({ "background_cloud",
			std::make_unique<Engine::Sprite>(gEngine->getAssetManager()->getTexture("BGOCloud"), 2444, 144) });
		sprite_set.at("background_cloud")->setX(0);
		sprite_set.at("background_cloud")->setY(0);
		sprite_set.at("background_cloud")->setXVel(-0.05);
		sprite_set.insert({ "background_cloud1",
			std::make_unique<Engine::Sprite>(gEngine->getAssetManager()->getTexture("BGOCloud"), 2444, 72) });
		sprite_set.at("background_cloud1")->setX(-611);
		sprite_set.at("background_cloud1")->setY(150);
		sprite_set.at("background_cloud1")->setXVel(-0.1);

		// Creating Character Portraits Sprites
		sprite_set.insert({ "player",
			std::make_unique<Engine::Sprite>(gEngine->getAssetManager()->getTexture("CHAR_NUL"), 300, 300) });

		if (player_set.size() > 0) {
			if (player_set[0]->getCharState() == S_Reimu) {
				sprite_set.at("player")->swapTexture(gEngine->getAssetManager()->getTexture("CHAR_REI"), 300, 300);
			}
			else if (player_set[0]->getCharState() == S_Marisa) {
				sprite_set.at("player")->swapTexture(gEngine->getAssetManager()->getTexture("CHAR_MAR"), 300, 300);
			}
			else {
				sprite_set.at("player")->swapTexture(gEngine->getAssetManager()->getTexture("CHAR_NUL"), 300, 300);
			}
		}

		// Creating Market Sprites
		sprite_set.insert({ "MID_Null",
			std::make_unique<Engine::Sprite>(gEngine->getAssetManager()->getTexture("MKT_NULL"), 128, 128) });

		test_textbox.init(renderer, gEngine, sprite_set, player_set);

		// Creating Text Sprites

		sprite_set.insert({ "player_balance",
			std::make_unique<Engine::Sprite>(gEngine->getAssetManager()->getTexture("TEXT_PBAL"),
				balance_text.getRenderSize().size.x * SCREEN_SCALE, balance_text.getRenderSize().size.y * SCREEN_SCALE)});
		
		return true;
	}

	void Market_Game::update(Engine::Engine* gEngine, Sprite_Map& sprite_set, Player_Set& player_set) {

		this->state_machine(gEngine, sprite_set, player_set);

		test_textbox.update(gEngine, sprite_set, player_set);

		if (gEngine->getInput()->isKeyPressed(SDL_SCANCODE_EQUALS)) {
			player_set.at(0)->balanceChange(1000);
		}

	}

	void Market_Game::render(SDL_Renderer* renderer, Engine::Engine* gEngine, Sprite_Map& sprite_set, Player_Set& player_set) {
		sprite_set.at("background")->draw(renderer, Engine::Vector2i(0, 0));
		if (sprite_set.at("background_cloud")->getX() < -1222) {
			sprite_set.at("background_cloud")->setX(0);
		}
		sprite_set.at("background_cloud1")->draw(renderer);
		if (sprite_set.at("background_cloud1")->getX() < -1222) {
			sprite_set.at("background_cloud1")->setX(0);
		}
		sprite_set.at("background_cloud")->draw(renderer);
		sprite_set.at("background_cloud1")->draw(renderer);

		sprite_set.at("player")->draw(renderer, Engine::Vector2i(980,0));

		gEngine->getAssetManager()->storeTexture(balance_text.load(renderer), "TEXT_PBAL", renderer);
		sprite_set.at("player_balance")->swapTexture(gEngine->getAssetManager()->getTexture("TEXT_PBAL"), balance_text.getRenderSize().size.x, balance_text.getRenderSize().size.y);
		sprite_set.at("player_balance")->draw(renderer, Engine::Vector2i(960, 300));

		for (int i = 0; i < 5; ++i) {
			sprite_set.at(player_set[0]->getLand()->getMarketStr(i))->draw(renderer, Engine::Vector2i(275 + i * 150, 350 + 50 * (i % 2)));
		}

		test_textbox.draw(renderer, gEngine, sprite_set, player_set);
	}

	void Market_Game::state_machine(Engine::Engine* gEngine, Sprite_Map& sprite_set, Player_Set& player_set) {


		/*  Main Game State */

		if (_market_scene_state & MG_Main_Game) {
			// Sets the new balance for the text

			std::stringstream newBalance;
			newBalance << "Total Balance: " << std::fixed << std::setprecision(2) << player_set.at(0)->getBalance();
			balance_text.setText(newBalance.str().c_str());

		}
		else {

		}

		/* Intro Screen State */

		if (_market_scene_state & MG_Intro_Sceen) {
			// Turning on the textbox

			if (test_textbox.getAttr() & (Text::TXT_UP_DOWN | Text::TXT_ENTER_EXIT)) {
				if (gEngine->getInput()->isMouseClicked(SDL_BUTTON_LEFT)) {
					test_textbox.enableAttr(Text::TXT_ACTIVE);
					test_textbox.enableAttr(Text::TXT_UP_DOWN);
				}
			}
			// Autocompleting the textbox (using Spacebar)

			if ((test_textbox.getAttr() & (Text::TXT_ACTIVE_TEXT_COMPLETE | Text::TXT_ACTIVE_TEXT) & Text::TXT_ACTIVE_TEXT)) {
				if (gEngine->getInput()->isKeyPressed(SDL_SCANCODE_SPACE)) {
					test_textbox.enableAttr(Text::TXT_ACTIVE_TEXT_COMPLETE);
				}
			}
			// Turning off the Intro Scene (closing with Q)

			if (test_textbox.getAttr() & (Text::TXT_ACTIVE_TEXT | Text::TXT_ACTIVE_TEXT_COMPLETE) & Text::TXT_ACTIVE_TEXT_COMPLETE) {
				if (gEngine->getInput()->isKeyPressed(SDL_SCANCODE_Q)) {
					_market_scene_state ^= MG_Intro_Sceen;
				}
			}
		}
		
		else {
			// Reactivate the main game
			if (!(_market_scene_state & MG_Main_Game)) {
				_market_scene_state |= MG_Main_Game;
			}

			// If the textbox still exists, then tell it to leave

			if ((test_textbox.getAttr() & (Text::TXT_ENTER_EXIT))) {
				test_textbox.disableAttr(Text::TXT_ENTER_EXIT);
			}
			if (!(test_textbox.getAttr() & (Text::TXT_ACTIVE))) {
				test_textbox.enableAttr(Text::TXT_ACTIVE);
			}
		}
	}

	// Timer Functions

	Market_Game::Timer::Timer(seconds new_dur) {
		_start = std::chrono::steady_clock::now();
		_dur = new_dur;
		_curr_left = _dur;
	}

	timer Market_Game::Timer::time_left() {
		_curr_left = _dur - (std::chrono::steady_clock::now() - _start);
		return _curr_left;
	}

	void Market_Game::Timer::timer_reset(seconds new_dur) {
		*this = Timer(new_dur);
	}


}