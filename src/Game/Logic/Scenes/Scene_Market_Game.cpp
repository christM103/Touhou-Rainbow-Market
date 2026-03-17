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

	bool Market_Game::create() {

		// Lambda for checking current player
		auto playerCheck = [](Player_Data::Char_State player_data) {
			return gState.gPlayer->current_char == player_data;
			};

		
		// Variable definitions

		const std::string CHAR_NUL = gState.GFX_FOLDER + "Market_Game/Placeholder_Portrait_Null.png";
		const std::string CHAR_REI = gState.GFX_FOLDER + "Market_Game/Placeholder_Portrait_R_S.png";
		const std::string CHAR_MAR = gState.GFX_FOLDER + "Market_Game/Placeholder_Portrait_M_S.png";
		const std::string TXT_BOX_BG = gState.GFX_FOLDER + "Common/Placeholder_Box_BGO.png";
		const std::string TXT_BOX_F = gState.GFX_FOLDER + "Common/Placeholder_Box_Frame.png";


		/* Texture Initialization */

		// Loading Background
		const std::string BGO_GFX = gState.GFX_FOLDER + "Market_Game/Placeholder_Game_BGO.png";
		gState.gAssets->loadTexture(BGO_GFX, "BGO_GFX", gState.gRenderer);

		// Loading Character Portraits
		gState.gAssets->loadTexture(CHAR_NUL, "CHAR_NUL", gState.gRenderer);
		gState.gAssets->loadTexture(CHAR_REI, "CHAR_REI", gState.gRenderer);
		gState.gAssets->loadTexture(CHAR_MAR, "CHAR_MAR", gState.gRenderer);

		// Loading Text
		gState.gAssets->loadTexture(TXT_BOX_BG, "TXT_BOX_BG", gState.gRenderer);
		gState.gAssets->loadTexture(TXT_BOX_F, "TXT_BOX_F", gState.gRenderer);


		/* Sprite Creation */

		// Create Background Sprite
		Engine::Entity BGO = gState.gECS->createEntity("BGO");
		gState.gECS->addComponent<Engine::TransformComponent>(BGO, Engine::Vector2i{ -100,-600 });
		gState.gECS->addComponent<Engine::SpriteComponent>(BGO, Engine::Recti{ 0,0,1500,1500 }, Engine::Vector2i(1500, 1500), "BGO_GFX");
		
		// Creating Character Portraits Sprites
		Engine::Entity PLAYER_PORTRAIT = gState.gECS->createEntity("PLAYER_PORTRAIT");
		gState.gECS->addComponent<Engine::TransformComponent>(PLAYER_PORTRAIT, Engine::Vector2i{ 980,0 }, 0.0f, Engine::Vector2f{ 0.0f,0.0f });
		
		// Initialize Portrait
		if (playerCheck(Player_Data::S_Reimu)) {
			gState.gECS->addComponent<Engine::SpriteComponent>(PLAYER_PORTRAIT, Engine::Recti{ 0,0,300,300 }, Engine::Vector2i(300, 300), "CHAR_REI");
		}
		else if (playerCheck(Player_Data::S_Marisa)) {
			gState.gECS->addComponent<Engine::SpriteComponent>(PLAYER_PORTRAIT, Engine::Recti{ 0,0,300,300 }, Engine::Vector2i(300, 300), "CHAR_MAR");
		}
		else {
			gState.gECS->addComponent<Engine::SpriteComponent>(PLAYER_PORTRAIT, Engine::Recti{ 0,0,300,300 }, Engine::Vector2i(300, 300), "CHAR_NUL");
		}
		gState.gECS->addComponent<Engine::RenderLayerComponent>(PLAYER_PORTRAIT, Engine::RenderLayerComponent::HUD);


		/* Object Creation */
		
		// Initialize Market Entities
		for (int index = 0; index < 6; index++) {
			Engine::Entity entity = gState.gECS->createEntity("Market" + std::to_string(index));
			auto* market = gState.gPlayer->player_data->getLand()->getMarket(index);
			gState.gECS->addComponent<MarketComponent>(entity, market);
		}

		gState.gECS->addSystem<MarketSystem>();
		gState.gECS->addSystem<TextboxSystem>();

		return true;
	}

	void Market_Game::update() {

		switch (uint16_t state = (_market_scene_state & Main_Game_Timeline_States)) {
			TextBoxComponent* textbox;

			case MG_Intro_Sceen:
				// Initialize Text Box Entity
				if (gState.gECS->getEntities().find("TEXTBOX_TEST") == gState.gECS->getEntities().end()) {
					Engine::Entity TEXTBOX_TEST = gState.gECS->createEntity("TEXTBOX_TEST");
					gState.gECS->addComponent<TextBoxComponent>(TEXTBOX_TEST,
						"Welcome to the Touhou Rainbow Market Game Beta!",
						240, 240, 5, TextBoxComponent::TXTBOX_NULL | TextBoxComponent::ENTER | TextBoxComponent::TRANSITION_UP,
						TextBoxComponent::WIDTH_MEDIUM | TextBoxComponent::HEIGHT_MEDIUM, 30);
				}
				textbox = gState.gECS->getComponent<TextBoxComponent>(gState.gECS->getEntities().at("TEXTBOX_TEST"));

				if ((textbox->_textbox_flags & textbox->TXT_COMPLETE) != textbox->TXTBOX_NULL) {
					_market_scene_state ^= MG_Intro_Sceen;
					_market_scene_state ^= MG_Market_Prompt;
				}
				break;
			case MG_Market_Prompt:
				textbox = gState.gECS->getComponent<TextBoxComponent>(gState.gECS->getEntities().at("TEXTBOX_TEST"));
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

	}

}