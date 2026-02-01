#include "Game/logic.hpp"
#include "Game/logic_obj.hpp"
#include "Engine/Graphics/AssetManager.hpp"

namespace TR {
	//using Text = TextBox::Text_Box_Transitions;

	Market_Game::Market_Game() {
		_currState = SC_Main;
		_nextState = _currState;
		_market_scene_state ^= MG_Intro_Sceen;

		//test_textbox.enableAttr(Text::TXT_ACTIVE);
		//test_textbox.enableAttr(Text::TXT_UP_DOWN);
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
		//gEngine->getAssetManager()->storeTexture(balance_text.load(renderer), "TEXT_PBAL", renderer);
		gEngine->getAssetManager()->loadTexture("assets/gfx/sprites/Common/Placeholder_Box_BGO.png", "TXT_BOX_BG", renderer);
		gEngine->getAssetManager()->loadTexture("assets/gfx/sprites/Common/Placeholder_Box_Frame.png", "TXT_BOX_F", renderer);

		/* Sprite Creation */

		// Create Background Sprite
		Engine::Entity BGO = gEngine->getECSManager()->createEntity();
		gEngine->getECSManager()->addComponent<Engine::TransformComponent>(BGO, Engine::Vector2i{ 0,0 }, 0.0f, Engine::Vector2f{ 0.0f,0.0f });
		gEngine->getECSManager()->addComponent<Engine::SpriteComponent>(BGO, Engine::Recti{ 0,0,1280,720 }, Engine::Vector2i(1280, 720), "BGO");

		Engine::Entity BG_CLOUD1 = gEngine->getECSManager()->createEntity();
		gEngine->getECSManager()->addComponent<Engine::TransformComponent>(BG_CLOUD1, Engine::Vector2i{ 0,0 }, 0.0f, Engine::Vector2f{ 0.0f,0.0f });
		gEngine->getECSManager()->addComponent<Engine::SpriteComponent>(BG_CLOUD1, Engine::Recti{ 0,0,2444,144 }, Engine::Vector2i(2444, 144), "BGOCloud");

		Engine::Entity BG_CLOUD2 = gEngine->getECSManager()->createEntity();
		gEngine->getECSManager()->addComponent<Engine::TransformComponent>(BG_CLOUD2, Engine::Vector2i{ -611,150 }, 0.0f, Engine::Vector2f{ 0.0f,0.0f });
		gEngine->getECSManager()->addComponent<Engine::SpriteComponent>(BG_CLOUD2, Engine::Recti{ 0,0,2444,144 }, Engine::Vector2i(2444, 144), "BGOCloud");

		
		// Creating Character Portraits Sprites
		Engine::Entity PLAYER = gEngine->getECSManager()->createEntity();
		gEngine->getECSManager()->addComponent<Engine::TransformComponent>(PLAYER, Engine::Vector2i{ 980,0 }, 0.0f, Engine::Vector2f{ 0.0f,0.0f });

		if (player_set.size() > 0) {
			if (player_set[0]->getCharState() == S_Reimu) {
				gEngine->getECSManager()->addComponent<Engine::SpriteComponent>(PLAYER, Engine::Recti{ 0,0,300,300 }, Engine::Vector2i(300, 300), "CHAR_REI");
			}
			else if (player_set[0]->getCharState() == S_Marisa) {
				gEngine->getECSManager()->addComponent<Engine::SpriteComponent>(PLAYER, Engine::Recti{ 0,0,300,300 }, Engine::Vector2i(300, 300), "CHAR_MAR");
			}
			else {
				gEngine->getECSManager()->addComponent<Engine::SpriteComponent>(PLAYER, Engine::Recti{ 0,0,300,300 }, Engine::Vector2i(300, 300), "CHAR_NUL");
			}
		}

		// Text Box Entity

		Engine::Entity TEXTBOX_TEST = gEngine->getECSManager()->createEntity();
		auto& Transforms = gEngine->getECSManager()->addComponent<Engine::MultiTransformComponent>(TEXTBOX_TEST);
		Transforms.transforms.emplace(0, std::make_shared<Engine::TransformComponent>(Engine::Vector2i{ 320,240 }));
		Transforms.transforms.emplace(1, std::make_shared<Engine::TransformComponent>(Engine::Vector2i{ 320,240 }));

		auto& Sprites = gEngine->getECSManager()->addComponent<Engine::MultiSpriteComponent>(TEXTBOX_TEST);
		Sprites.sprites.emplace(0, std::make_shared<Engine::SpriteComponent>(Engine::Recti(0, 0, 400, 200), Engine::Vector2i(400, 200), "TXT_BOX_BG"));
		Sprites.sprites.emplace(1, std::make_shared<Engine::SpriteComponent>(Engine::Recti(0, 0, 400, 200), Engine::Vector2i(400, 200), "TXT_BOX_F"));

		/*
		// Creating Market Sprites
		sprite_set.insert({ "MID_Null",
			std::make_unique<Engine::Sprite>(gEngine->getAssetManager()->getTexture("MKT_NULL"), 128, 128) });

		test_textbox.init(renderer, gEngine, sprite_set, player_set);

		// Creating Text Sprites

		sprite_set.insert({ "player_balance",
			std::make_unique<Engine::Sprite>(gEngine->getAssetManager()->getTexture("TEXT_PBAL"),
				balance_text.getSize().x * SCREEN_SCALE, balance_text.getSize().y * SCREEN_SCALE)});
		*/

		return true;
		
	}

	void Market_Game::update(Engine::Engine* gEngine, Sprite_Map& sprite_set, Player_Set& player_set) {
		/*
		this->state_machine(gEngine, sprite_set, player_set);

		test_textbox.update(gEngine, sprite_set, player_set);

		if (gEngine->getInput()->isKeyPressed(SDL_SCANCODE_EQUALS)) {
			player_set.at(0)->balanceChange(1000);
		}
		*/

	}

	void Market_Game::render(SDL_Renderer* renderer, Engine::Engine* gEngine, Sprite_Map& sprite_set, Player_Set& player_set) {
		/*
		gEngine->getAssetManager()->storeTexture(balance_text.load(renderer), "TEXT_PBAL", renderer);
		sprite_set.at("player_balance")->swapTexture(gEngine->getAssetManager()->getTexture("TEXT_PBAL"), balance_text.getSize().x, balance_text.getSize().y);
		sprite_set.at("player_balance")->draw(renderer, Engine::Vector2i(960, 300));

		for (int i = 0; i < 5; ++i) {
			sprite_set.at(player_set[0]->getLand()->getMarketStr(i))->draw(renderer, Engine::Vector2i(275 + i * 150, 350 + 50 * (i % 2)));
		}

		test_textbox.draw(renderer, gEngine, sprite_set, player_set);
	}

	void Market_Game::state_machine(Engine::Engine* gEngine, Sprite_Map& sprite_set, Player_Set& player_set) {


		/*  Main Game State

		if (_market_scene_state & MG_Main_Game) {
			// Sets the new balance for the text

			std::stringstream newBalance;
			newBalance << "Total Balance: " << std::fixed << std::setprecision(2) << player_set.at(0)->getBalance();
			balance_text.setText(newBalance.str().c_str());

		}
		else {

		}

		/* Intro Screen State

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
		*/
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