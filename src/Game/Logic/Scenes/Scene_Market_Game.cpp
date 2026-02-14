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

	bool Market_Game::create(SDL_Renderer* renderer, Engine::Engine* gEngine) {

		/* Texture Initialization */

		// Loading Background
		gEngine->getAssetManager()->loadTexture("assets/gfx/sprites/Market_Game/Placeholder_Game_BGO.png", "BGO", renderer);

		// Loading Character Portraits
		gEngine->getAssetManager()->loadTexture("assets/gfx/sprites/Common/Placeholder_Portrait_Null.png", "CHAR_NUL", renderer);
		gEngine->getAssetManager()->loadTexture("assets/gfx/sprites/Market_Game/Placeholder_Portrait_R_S.png", "CHAR_REI", renderer);
		gEngine->getAssetManager()->loadTexture("assets/gfx/sprites/Market_Game/Placeholder_Portrait_M_S.png", "CHAR_MAR", renderer);

		// Loading Markets

		// Loading Text
		//gEngine->getAssetManager()->storeTexture(balance_text.load(renderer), "TEXT_PBAL", renderer);
		gEngine->getAssetManager()->loadTexture("assets/gfx/sprites/Common/Placeholder_Box_BGO.png", "TXT_BOX_BG", renderer);
		gEngine->getAssetManager()->loadTexture("assets/gfx/sprites/Common/Placeholder_Box_Frame.png", "TXT_BOX_F", renderer);

		/* Sprite Creation */

		// Create Background Sprite
		Engine::Entity BGO = gEngine->getECSManager()->createEntity("BGO");
		gEngine->getECSManager()->addComponent<Engine::TransformComponent>(BGO, Engine::Vector2i{ -100,-600 });
		gEngine->getECSManager()->addComponent<Engine::SpriteComponent>(BGO, Engine::Recti{ 0,0,1500,1500 }, Engine::Vector2i(1500, 1500), "BGO");

		
		// Creating Character Portraits Sprites
		Engine::Entity PLAYER_PORTRAIT = gEngine->getECSManager()->createEntity("PLAYER_PORTRAIT");
		gEngine->getECSManager()->addComponent<Engine::TransformComponent>(PLAYER_PORTRAIT, Engine::Vector2i{ 980,0 }, 0.0f, Engine::Vector2f{ 0.0f,0.0f });

		if (gEngine->getECSManager()->getComponent<PlayerComponent>(gEngine->getECSManager()->getEntities().at("PLAYER"))->current_char == Player_Data::S_Reimu) {
			gEngine->getECSManager()->addComponent<Engine::SpriteComponent>(PLAYER_PORTRAIT, Engine::Recti{ 0,0,300,300 }, Engine::Vector2i(300, 300), "CHAR_REI");
		}
		else if (gEngine->getECSManager()->getComponent<PlayerComponent>(gEngine->getECSManager()->getEntities().at("PLAYER"))->current_char == Player_Data::S_Marisa) {
			gEngine->getECSManager()->addComponent<Engine::SpriteComponent>(PLAYER_PORTRAIT, Engine::Recti{ 0,0,300,300 }, Engine::Vector2i(300, 300), "CHAR_MAR");
		}
		else {
			gEngine->getECSManager()->addComponent<Engine::SpriteComponent>(PLAYER_PORTRAIT, Engine::Recti{ 0,0,300,300 }, Engine::Vector2i(300, 300), "CHAR_NUL");
		}


		for (int index = 0; index < 6; index++) {
			Engine::Entity entity = gEngine->getECSManager()->createEntity("Market" + std::to_string(index));
			auto* market = gEngine->getECSManager()->getComponent<PlayerComponent>(gEngine->getECSManager()->getEntities().at("PLAYER"))->player_data->getLand()->getMarket(index);
			gEngine->getECSManager()->addComponent<MarketComponent>(entity, market);
		}

		gEngine->getECSManager()->addSystem<MarketSystem>();

		// Text Box Entity

		Engine::Entity TEXTBOX_TEST = gEngine->getECSManager()->createEntity("TEXTBOX_TEST");

		gEngine->getECSManager()->addComponent<TextBoxComponent>(TEXTBOX_TEST, 
			R"(Welcome to the Touhou Rainbow Market Game Beta!)",
			240, 240, 5, TextBoxComponent::TXTBOX_NULL | TextBoxComponent::ENTER | TextBoxComponent::TRANSITION_UP);
		gEngine->getECSManager()->addSystem<TextboxSystem>();

		return true;
		
	}

	void Market_Game::update(Engine::Engine* gEngine) {

		if (gEngine->getECSManager()->componentExists<TextBoxComponent>()) {
			if (gEngine->getECSManager()->isSystemRunning<TextboxSystem>()) {
				gEngine->getECSManager()->toggleSystem<TextboxSystem>(true);
			}
		}
		else {
			gEngine->getECSManager()->toggleSystem<TextboxSystem>(false);
		}

	}

}