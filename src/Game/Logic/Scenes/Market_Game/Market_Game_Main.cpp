#include "Engine/Graphics/AssetManager.hpp"

#include "Game/Logic/Scenes.hpp"
#include "Game/Objects/Components/MarketGameComponents.hpp"
#include "Game/Objects/Systems/MarketGameSystems.hpp"



namespace TR {
	Market_Game::Market_Game() {
		_currState = Scene_ID::Main;
		_nextState = _currState;
		setYAMLPath(PATH_YAML_MARKETGAME);
		_market_scene_state = Game_States::MG_Welcome_Screen;
	}

	bool Market_Game::create() {

		// Lambda for checking current player
		auto playerCheck = [](Char_State player_data) {
			return gState.gPlayer->current_char == player_data;
			};
		
		if (getDebugManager().isEnabled()) {
			
		}
		else {
			// Variable definitions

			const std::string CHAR_NUL = GFX_FOLDER + "Market_Game/Placeholder_Portrait_Null.png";
			const std::string CHAR_REI = GFX_FOLDER + "Market_Game/Placeholder_Portrait_R_S.png";
			const std::string CHAR_MAR = GFX_FOLDER + "Market_Game/Placeholder_Portrait_M_S.png";

			const std::string MARK_MYST = GFX_FOLDER + "Market_Game/Placeholder_Game_MarketMystia.png";
			const std::string MARK_MYST_S = GFX_FOLDER + "Market_Game/Placeholder_Game_MarketMystia_S.png";

			const std::string TXT_BOX_BG = GFX_FOLDER + "Common/Placeholder_Box_BGO.png";
			const std::string TXT_BOX_F = GFX_FOLDER + "Common/Placeholder_Box_Frame.png";


			/* Texture Initialization */

			// Loading Background
			const std::string BGO_GFX = GFX_FOLDER + "Market_Game/Placeholder_Game_BGO.png";
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
			if (playerCheck(Char_State::Reimu)) {
				gState.gECS->addComponent<Engine::SpriteComponent>(PLAYER_PORTRAIT, Engine::Recti{ 0,0,300,300 }, Engine::Vector2i(300, 300), "CHAR_REI");
			}
			else if (playerCheck(Char_State::Marisa)) {
				gState.gECS->addComponent<Engine::SpriteComponent>(PLAYER_PORTRAIT, Engine::Recti{ 0,0,300,300 }, Engine::Vector2i(300, 300), "CHAR_MAR");
			}
			else {
				gState.gECS->addComponent<Engine::SpriteComponent>(PLAYER_PORTRAIT, Engine::Recti{ 0,0,300,300 }, Engine::Vector2i(300, 300), "CHAR_NUL");
			}
			gState.gECS->addComponent<Engine::RenderLayerComponent>(PLAYER_PORTRAIT, Engine::RenderLayerComponent::HUD);
		}

		/* Object Creation */

		// Initialize Market Entities
		for (int index = 0; index < 6; index++) {
			Engine::Entity entity = gState.gECS->createEntity("MARKET" + std::to_string(index));
			auto* market = gState.gPlayer->player_data->getLand()->getMarket(index);
			gState.gECS->addComponent<MarketComponent>(entity, market);
		}

		Engine::Entity TURNS = gState.gECS->createEntity("TURNS_TEST");
		gState.gECS->addComponent<TurnsComponent>(TURNS, 5);

		gState.gTurns = gState.gECS->getComponent<TurnsComponent>(TURNS);

		gState.gECS->addSystem<MarketSystem>();
		gState.gECS->addSystem<TextboxSystem>();
		gState.gECS->addSystem<ButtonSystem>();
		gState.gECS->addSystem<TurnSystem>();

		return true;
	}

	void Market_Game::update() {
		if (getDebugManager().isEnabled()) {
			_state_data.prompt_flags = static_cast<Prompt_Flags>(getDebugManager().getSelectedPromptIndex());	
		}


		switch (_market_scene_state) {
		case Game_States::MG_Welcome_Screen:
			this->introScreen();
			break;
		case Game_States::MG_First_Turn_Question:
			this->firstTurnQuestion();
			break;
		case Game_States::MG_Guide_Screen:
			this->guideScreen();
			break;
		case Game_States::MG_Market_Prompt:
			this->marketPrompt();
			break;
		case Game_States::MG_Turn_Start:
			this->turnStart();
			break;
		case Game_States::MG_Main_Game:
			this->showHUD();
			break;
		case Game_States::MG_Highlight_Lot:
			this->highlightLand();
			break;
		case Game_States::MG_Land_Action_Prompt:
			this->landActionPrompt();
			break;
		case Game_States::MG_Land_Action_Event:
			this->actionManager();
			break;

		case Game_States::MG_Highlight_Portrait:
			this->highlightPlayer();
			break;
		case Game_States::MG_Player_Action_Prompt:
			this->playerActionPrompt();
			break;
		}

	}
}