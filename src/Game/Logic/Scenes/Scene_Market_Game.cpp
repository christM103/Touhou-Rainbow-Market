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
		const std::string CHAR_NUL = GFX_FOLDER + "Market_Game/Placeholder_Portrait_Null.png";
		const std::string CHAR_REI = GFX_FOLDER + "Market_Game/Placeholder_Portrait_R_S.png";
		const std::string CHAR_MAR = GFX_FOLDER + "Market_Game/Placeholder_Portrait_M_S.png";
		const std::string TXT_BOX_BG = GFX_FOLDER + "Common/Placeholder_Box_BGO.png";
		const std::string TXT_BOX_F = GFX_FOLDER + "Common/Placeholder_Box_Frame.png";

		Engine::ECSManager* ecsManager = gEngine->getECSManager();


		/* Texture Initialization */

		// Loading Background
		const std::string BGO_GFX = GFX_FOLDER + "Market_Game/Placeholder_Game_BGO.png";
		gEngine->getAssetManager()->loadTexture(BGO_GFX, "BGO_GFX", renderer);

		// Loading Character Portraits
		gEngine->getAssetManager()->loadTexture(CHAR_NUL, "CHAR_NUL", renderer);
		gEngine->getAssetManager()->loadTexture(CHAR_REI, "CHAR_REI", renderer);
		gEngine->getAssetManager()->loadTexture(CHAR_MAR, "CHAR_MAR", renderer);

		// Loading Text
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

		ecsManager->addComponent<Engine::RenderLayerComponent>(PLAYER_PORTRAIT, Engine::RenderLayerComponent::HUD);


		/* Object Creation */
		
		// Initialize Market Entities
		for (int index = 0; index < 6; index++) {
			Engine::Entity entity = ecsManager->createEntity("Market" + std::to_string(index));
			Player_Data* player = ecsManager->getComponent<PlayerComponent>(ecsManager->getEntities().at("PLAYER"))->player_data;
			auto* market = player->getLand()->getMarket(index);
			ecsManager->addComponent<MarketComponent>(entity, market);
		}
		ecsManager->addSystem<MarketSystem>();

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
		switch (uint16_t state = (_market_scene_state & Main_Game_Timeline_States)) {
			TextBoxComponent* textbox;

			case MG_Intro_Sceen:
				// Initialize Text Box Entity
				if (ecsManager->getEntities().find("TEXTBOX_TEST") == ecsManager->getEntities().end()) {
					Engine::Entity TEXTBOX_TEST = ecsManager->createEntity("TEXTBOX_TEST");
					ecsManager->addComponent<TextBoxComponent>(TEXTBOX_TEST,
						"Welcome to the Touhou Rainbow Market Game Beta!",
						240, 240, 5, TextBoxComponent::TXTBOX_NULL | TextBoxComponent::ENTER | TextBoxComponent::TRANSITION_UP,
						TextBoxComponent::WIDTH_MEDIUM | TextBoxComponent::HEIGHT_MEDIUM, 30);
				}
				textbox = ecsManager->getComponent<TextBoxComponent>(ecsManager->getEntities().at("TEXTBOX_TEST"));

				if ((textbox->_textbox_flags & textbox->TXT_COMPLETE) != textbox->TXTBOX_NULL) {
					_market_scene_state ^= MG_Intro_Sceen;
					_market_scene_state ^= MG_Market_Prompt;
				}
				break;
			case MG_Market_Prompt:
				textbox = ecsManager->getComponent<TextBoxComponent>(ecsManager->getEntities().at("TEXTBOX_TEST"));
				if (textbox->_textbox_next.empty() && (textbox->_textbox_flags & textbox->TXT_COMPLETE) != textbox->TXTBOX_NULL) {
					if (textbox->_textbox_text != "Would you like to have Mystia's market?\n") {
						textbox->_textbox_next = "Would you like to have Mystia's market?\n";
					}
				}
				if ((textbox->_textbox_flags & textbox->INPUT_PRESSED) != textbox->TXTBOX_NULL && 
					(textbox->_textbox_style & textbox->WIDTH_MEDIUM) != textbox->NULL_BOX) {
					textbox->_textbox_style ^= TextBoxComponent::WIDTH_SMALL;
					textbox->_textbox_style ^= TextBoxComponent::WIDTH_MEDIUM;
				}
				
				break;
			default:
				break;
		}


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