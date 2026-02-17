#include "Engine/Graphics/AssetManager.hpp"

#include "Game/Logic/Scenes.hpp"
#include "Game/Objects/Components/MarketGameComponents.hpp"
#include "Game/Objects/Systems/MarketGameSystems.hpp"





namespace TR {
	Market_Game::Market_Game() {
		_currState = SC_Main;
		_nextState = _currState;
		_market_scene_state ^= MG_Intro_Sceen;
	}

	bool Market_Game::create(SDL_Renderer* renderer, Engine::Engine* gEngine) {

		// Lambda for checking current player
		auto playerCheck = [](Engine::ECSManager* ecsManager, Player_Data::Char_State player_data) {
			return ecsManager->getComponent<PlayerComponent>(ecsManager->getEntities().at("PLAYER"))->current_char == player_data;
			};

		
		// Variable definitions
		const std::string GFX_FOLDER = "assets/gfx/sprites/";
		Engine::ECSManager* ecsManager = gEngine->getECSManager();


		/* Texture Initialization */

		// Loading Background
		const std::string BGO_GFX = GFX_FOLDER + "Market_Game/Placeholder_Game_BGO.png";
		gEngine->getAssetManager()->loadTexture(BGO_GFX, "BGO_GFX", renderer);

		// Loading Character Portraits
		const std::string CHAR_NUL = GFX_FOLDER + "Market_Game/Placeholder_Portrait_Null.png";
		const std::string CHAR_REI = GFX_FOLDER + "Market_Game/Placeholder_Portrait_R_S.png";
		const std::string CHAR_MAR = GFX_FOLDER + "Market_Game/Placeholder_Portrait_M_S.png";
		gEngine->getAssetManager()->loadTexture(CHAR_NUL, "CHAR_NUL", renderer);
		gEngine->getAssetManager()->loadTexture(CHAR_REI, "CHAR_REI", renderer);
		gEngine->getAssetManager()->loadTexture(CHAR_MAR, "CHAR_MAR", renderer);

		// Loading Text
		const std::string TXT_BOX_BG = GFX_FOLDER + "Common/Placeholder_Box_BGO.png";
		const std::string TXT_BOX_F = GFX_FOLDER + "Common/Placeholder_Box_Frame.png";
		gEngine->getAssetManager()->loadTexture(TXT_BOX_BG, "TXT_BOX_BG", renderer);
		gEngine->getAssetManager()->loadTexture(TXT_BOX_F, "TXT_BOX_F", renderer);


		/* Sprite Creation */

		// Create Background Sprite
		Engine::Entity BGO = ecsManager->createEntity("BGO");
		ecsManager->addComponent<Engine::TransformComponent>(BGO, Engine::Vector2i{ -100,-600 });
		ecsManager->addComponent<Engine::SpriteComponent>(BGO, Engine::Recti{ 0,0,1500,1500 }, Engine::Vector2i(1500, 1500), "BGO_GFX");

		
		// Creating Character Portraits Sprites
		Engine::Entity PLAYER_PORTRAIT = ecsManager->createEntity("PLAYER_PORTRAIT");
		ecsManager->addComponent<Engine::TransformComponent>(PLAYER_PORTRAIT, Engine::Vector2i{ 980,0 }, 0.0f, Engine::Vector2f{ 0.0f,0.0f });

		
		// Initialize Portrait
		if (playerCheck(ecsManager, Player_Data::S_Reimu)) {
			ecsManager->addComponent<Engine::SpriteComponent>(PLAYER_PORTRAIT, Engine::Recti{ 0,0,300,300 }, Engine::Vector2i(300, 300), "CHAR_REI");
		}
		else if (playerCheck(ecsManager, Player_Data::S_Marisa)) {
			ecsManager->addComponent<Engine::SpriteComponent>(PLAYER_PORTRAIT, Engine::Recti{ 0,0,300,300 }, Engine::Vector2i(300, 300), "CHAR_MAR");
		}
		else {
			ecsManager->addComponent<Engine::SpriteComponent>(PLAYER_PORTRAIT, Engine::Recti{ 0,0,300,300 }, Engine::Vector2i(300, 300), "CHAR_NUL");
		}


		/* Object Creation */
		
		// Initialize Market Entities
		for (int index = 0; index < 6; index++) {
			Engine::Entity entity = ecsManager->createEntity("Market" + std::to_string(index));
			auto* market = ecsManager->getComponent<PlayerComponent>(ecsManager->getEntities().at("PLAYER"))->player_data->getLand()->getMarket(index);
			ecsManager->addComponent<MarketComponent>(entity, market);
		}
		ecsManager->addSystem<MarketSystem>();

		// Initialize Text Box Entity
		Engine::Entity TEXTBOX_TEST = ecsManager->createEntity("TEXTBOX_TEST");
		ecsManager->addComponent<TextBoxComponent>(TEXTBOX_TEST, 
			R"(Welcome to the Touhou Rainbow Market Game Beta!)",
			240, 240, 5, TextBoxComponent::TXTBOX_NULL | TextBoxComponent::ENTER | TextBoxComponent::TRANSITION_UP);
		ecsManager->addSystem<TextboxSystem>();

		// Initialize Mouse Entity
		if (ecsManager->allEntities<Engine::MouseComponent>() == nullptr) {
			Engine::Entity newMouse = ecsManager->createEntity("MOUSE");
			ecsManager->addComponent<Engine::MouseComponent>(newMouse);
		}

		return true;
	}

	void Market_Game::update(Engine::Engine* gEngine) {
		Engine::ECSManager* ecsManager = gEngine->getECSManager();

		if (ecsManager->componentExists<TextBoxComponent>()) {
			if (ecsManager->isSystemRunning<TextboxSystem>()) {
				ecsManager->toggleSystem<TextboxSystem>(true);
			}
		}
		else {
			ecsManager->toggleSystem<TextboxSystem>(false);
		}

	}

}