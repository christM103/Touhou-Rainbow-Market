#include "Engine/Graphics/AssetManager.hpp"

#include "Game/Logic/Scenes.hpp"
#include "Game/Objects/Components/MarketGameComponents.hpp"
#include "Game/Objects/Systems/MarketGameSystems.hpp"





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

	bool Market_Game::create(SDL_Renderer* renderer, Engine::Engine* gEngine, Player_Set& player_set) {

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

		gEngine->getECSManager()->addComponent<TextBoxComponent>(TEXTBOX_TEST, "Testing the component", 240, 240, 1, TextBoxComponent::TXTBOX_NULL | TextBoxComponent::ENTER | TextBoxComponent::TRANSITION_UP | TextBoxComponent::TRANSITION_RIGHT);
		gEngine->getECSManager()->addSystem<TextboxSystem>();
		gEngine->getECSManager()->addSystem<Engine::MotionSystem>();
		
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

	void Market_Game::update(Engine::Engine* gEngine, Player_Set& player_set) {

		if (gEngine->getECSManager()->componentExists<TextBoxComponent>()) {
			if (gEngine->getECSManager()->isSystemRunning<TextboxSystem>()) {
				gEngine->getECSManager()->toggleSystem<TextboxSystem>(true);
			}
		}
		else {
			gEngine->getECSManager()->toggleSystem<TextboxSystem>(false);
		}

	}

	void Market_Game::render(SDL_Renderer* renderer, Engine::Engine* gEngine, Player_Set& player_set) {
		
	}

}