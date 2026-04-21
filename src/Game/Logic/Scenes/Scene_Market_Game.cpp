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

		const std::string MARK_MYST = gState.GFX_FOLDER + "Market_Game/Placeholder_Game_MarketMystia.png";
		const std::string MARK_MYST_S = gState.GFX_FOLDER + "Market_Game/Placeholder_Game_MarketMystia_S.png";

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

		// Loading Markets
		gState.gAssets->loadTexture(MARK_MYST, "MARK_MYST", gState.gRenderer);
		gState.gAssets->loadTexture(MARK_MYST_S, "MARK_MYST_S", gState.gRenderer);

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
			Engine::Entity entity = gState.gECS->createEntity("MARKET" + std::to_string(index));
			auto* market = gState.gPlayer->player_data->getLand()->getMarket(index);
			gState.gECS->addComponent<MarketComponent>(entity, market);
		}

		gState.gECS->addSystem<MarketSystem>();
		gState.gECS->addSystem<TextboxSystem>();
		gState.gECS->addSystem<ButtonSystem>();

		gState.gInput->newKey(SDL_SCANCODE_SPACE);

		return true;
	}

	void Market_Game::update() {

		auto switchState = [&](Main_Game_States state_var, Main_Game_States new_state) {
			_market_scene_state ^= state_var;
			_market_scene_state ^= new_state;
			};

		switch (uint32_t state = (_market_scene_state & Main_Game_Timeline_States)) {
			TextBoxComponent* textbox;
			ButtonPromptComponent* prompt;


			case MG_Intro_Sceen:
				// Initialize Text Box Entity
				if (gState.gECS->getEntities().find("TEXTBOX_TEST") == gState.gECS->getEntities().end()) {
					Engine::Entity TEXTBOX_TEST = gState.gECS->createEntity("TEXTBOX_TEST");
					gState.gECS->addComponent<TextBoxComponent>(TEXTBOX_TEST, "Welcome to the Touhou Rainbow Market Game Beta!", 240, 240, 5,
						TextBoxComponent::ENTER | TextBoxComponent::ACTIVATE, TextBoxComponent::WIDTH_MEDIUM | TextBoxComponent::HEIGHT_MEDIUM, 30);
				}
				textbox = gState.gECS->getComponent<TextBoxComponent>(gState.gECS->getEntities().at("TEXTBOX_TEST"));
				_market_scene_state = MG_Market_Prompt_SCRIPT_0;
				break;

			case MG_Market_Prompt:
				gState.gECS->getEntities().contains("TEXTBOX_TEST") ? 
					textbox = gState.gECS->getComponent<TextBoxComponent>(gState.gECS->getEntities().at("TEXTBOX_TEST")) : textbox = nullptr;
				gState.gECS->getEntities().contains("BUTTON_PROMPT") ? 
					prompt = gState.gECS->getComponent<ButtonPromptComponent>(gState.gECS->getEntities().at("BUTTON_PROMPT")) : prompt = nullptr;

				if (!textbox) {
					break;
				}

				gState.gInput->keyPressed(SDL_SCANCODE_SPACE) ? 
					textbox->_textbox_flags |= TextBoxComponent::INPUT_PRESSED : textbox->_textbox_flags &= ~TextBoxComponent::INPUT_PRESSED;

				this->Market_Prompt_States(textbox, prompt);
				
				break;

			case MG_Turn_Intro:
				if (gState.gECS->getEntities().contains("TEXTBOX_TEST")) {
					textbox = gState.gECS->getComponent<TextBoxComponent>(gState.gECS->getEntities().at("TEXTBOX_TEST"));
					if ((textbox->_textbox_flags & textbox->EXIT) == textbox->TXTBOX_NULL) {
						gState.gECS->destroyEntity("TEXTBOX_TEST");
					}
				}
				break;

			default:
				break;
		}

	}

	void Market_Game::Market_Prompt_States(TextBoxComponent* textbox, ButtonPromptComponent* prompt) {
		switch (_market_scene_state) {
			case MG_Market_Prompt_SCRIPT_0:
				if ((textbox->_textbox_flags & textbox->TXT_COMPLETE) != textbox->TXTBOX_NULL) {
					_market_scene_state = MG_Market_Prompt_SCRIPT_0_FINISHED;
				}
				break;
			case MG_Market_Prompt_SCRIPT_0_FINISHED:
				if (textbox->_textbox_text != "Would you like to have Mystia's market?\n") {
					textbox->_textbox_next = "Would you like to have Mystia's market?\n";
				}
				if ((textbox->_textbox_flags & textbox->INPUT_PRESSED) != textbox->TXTBOX_NULL) {
					textbox->_textbox_position = Engine::Vector2i{ 140, 80 };
					textbox->_textbox_style ^= TextBoxComponent::WIDTH_SMALL;
					textbox->_textbox_style ^= TextBoxComponent::WIDTH_MEDIUM;
					textbox->_textbox_style ^= TextBoxComponent::HEIGHT_MEDIUM;
					textbox->_textbox_style ^= TextBoxComponent::HEIGHT_LARGE;
					_market_scene_state = MG_Market_Prompt_RESIZE_0;
				}
				break;
			case MG_Market_Prompt_RESIZE_0:
				if (textbox->_textbox_position == Engine::Vector2i{ 140, 80 } &&
					(textbox->_textbox_flags & textbox->RESIZE) == textbox->TXTBOX_NULL &&
					(textbox->_textbox_flags & textbox->REFACTOR) == textbox->TXTBOX_NULL) {
					_market_scene_state = MG_Market_Prompt_SCRIPT_1;
				}
				break;
			case MG_Market_Prompt_SCRIPT_1:
				if (!gState.gECS->getEntities().contains("MYSTIA_GFX")) {
					Engine::Entity MYSTIA_GFX = gState.gECS->createEntity("MYSTIA_GFX");
					gState.gECS->addComponent<Engine::TransformComponent>(MYSTIA_GFX, Engine::Vector2i{ 240, 200 });
					gState.gECS->addComponent<Engine::SpriteComponent>(MYSTIA_GFX, Engine::Recti{ 0,0,400,400 }, Engine::Vector2i(400, 400), "MARK_MYST");
					gState.gECS->addComponent<Engine::RenderLayerComponent>(MYSTIA_GFX, Engine::RenderLayerComponent::TEXTBOX + 1);
				}

				if (!gState.gECS->getEntities().contains("BUTTON_PROMPT")) {
					Engine::Entity BUTTON_PROMPT = gState.gECS->createEntity("BUTTON_PROMPT");
					prompt = &gState.gECS->addComponent<ButtonPromptComponent>(BUTTON_PROMPT, Engine::Vector2i{ 300, 150 }, ButtonPromptComponent::HORIZONTAL);
				}

				if ((textbox->_textbox_flags & textbox->ACTIVATE) != textbox->TXTBOX_NULL) {
					textbox->_textbox_flags &= ~TextBoxComponent::ACTIVATE;
				}

				if ((textbox->_textbox_flags & textbox->TXT_COMPLETE) != textbox->TXTBOX_NULL) {
					_market_scene_state = MG_Market_Prompt_SCRIPT_1_FINISHED;
				}
				break;
			case MG_Market_Prompt_SCRIPT_1_FINISHED:
				if (prompt->_buttonFalse.activated) {
					textbox->_textbox_flags |= TextBoxComponent::INPUT_PRESSED | TextBoxComponent::ACTIVATE;
					_market_scene_state = MG_Market_Prompt_END;
				}
				if (prompt->_buttonTrue.activated) {
					if (textbox->_textbox_text != "Where do you want to put it?\n") {
						textbox->_textbox_next = "Where do you want to put it?\n";
					}
					textbox->_textbox_flags |= TextBoxComponent::INPUT_PRESSED | TextBoxComponent::ACTIVATE;
					textbox->_textbox_position = Engine::Vector2i{ 240, 80 };
					textbox->_textbox_style ^= TextBoxComponent::WIDTH_SMALL;
					textbox->_textbox_style ^= TextBoxComponent::WIDTH_MEDIUM;
					textbox->_textbox_style ^= TextBoxComponent::HEIGHT_TINY;
					textbox->_textbox_style ^= TextBoxComponent::HEIGHT_LARGE;
					_market_scene_state = MG_Market_Prompt_RESIZE_1;
				}

				break;
			case MG_Market_Prompt_RESIZE_1:
				if (gState.gECS->getEntities().contains("MYSTIA_GFX")) {
					gState.gECS->destroyEntity("MYSTIA_GFX");
				}
				if (gState.gECS->getEntities().contains("BUTTON_PROMPT")) {
					gState.gECS->destroyEntity("BUTTON_PROMPT");
				}
				if (textbox->_textbox_position == Engine::Vector2i{ 240, 80 } &&
					(textbox->_textbox_flags & textbox->RESIZE) == textbox->TXTBOX_NULL &&
					(textbox->_textbox_flags & textbox->REFACTOR) == textbox->TXTBOX_NULL) {
					_market_scene_state = MG_Market_Prompt_SCRIPT_2;
				}
				break;
			case MG_Market_Prompt_SCRIPT_2:
				if ((textbox->_textbox_flags & textbox->TXT_COMPLETE) != textbox->TXTBOX_NULL) {
					_market_scene_state = MG_Market_Prompt_SCRIPT_2_FINISHED;
				}
				break;
			case MG_Market_Prompt_SCRIPT_2_FINISHED:

				if ((textbox->_textbox_flags & textbox->ACTIVATE) != textbox->TXTBOX_NULL) {
					textbox->_textbox_flags &= ~TextBoxComponent::ACTIVATE;
				}

				MarketComponent* market;
				for (const auto& entity : *gState.gECS->allEntities<MarketComponent>()) {
					market = gState.gECS->getComponent<MarketComponent>(entity);
					if (market->market_active) {
						market->market_ID = Market_ID::MID_Mystia;
						textbox->_textbox_flags |= TextBoxComponent::INPUT_PRESSED | TextBoxComponent::ACTIVATE;
						_market_scene_state = MG_Market_Prompt_END;
					}
				}
				
				break;
			case MG_Market_Prompt_END:
				if ((textbox->_textbox_flags & textbox->EXIT) != textbox->TXTBOX_NULL) {
					if (gState.gECS->getEntities().contains("MYSTIA_GFX")) {
						gState.gECS->destroyEntity("MYSTIA_GFX");
					}
					if (gState.gECS->getEntities().contains("BUTTON_PROMPT")) {
						gState.gECS->destroyEntity("BUTTON_PROMPT");
					}
					if ((textbox->_textbox_flags & textbox->TXT_COMPLETE) != textbox->TXTBOX_NULL) {
						_market_scene_state = MG_Turn_Intro;
					}
				}
				break;
			default:
				break;
			}
		}

}