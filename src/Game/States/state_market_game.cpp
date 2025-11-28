#include "Game/logic.hpp"
#include "Engine/Graphics/AssetManager.hpp"

namespace TR {

	Market_Game::Market_Game() {}

	Market_Game::Market_Game(std::vector<std::shared_ptr<TR::Player_Data>> players) {}

	Market_Game::~Market_Game() {}

	bool Market_Game::create(SDL_Renderer* renderer, Engine::Engine* gEngine, Sprite_Map& sprite_set, Player_Set& player_set) {

		/* Render Creation */

		// Loading Background
		gEngine->getAssetManager()->loadTexture("assets/gfx/sprites/Market_Game/Placeholder_Game_BGLand.png", "BGO", renderer);
		gEngine->getAssetManager()->loadTexture("assets/gfx/sprites/Market_Game/Placeholder_Game_BGCLoud.png", "BGOCloud", renderer);
		
		// Loading Character Portraits
		gEngine->getAssetManager()->loadTexture("assets/gfx/sprites/Common/Placeholder_Portrait_Null.png", "CHAR_NUL", renderer);
		gEngine->getAssetManager()->loadTexture("assets/gfx/sprites/Common/Placeholder_Portrait_R.png", "CHAR_REI", renderer);
		gEngine->getAssetManager()->loadTexture("assets/gfx/sprites/Common/Placeholder_Portrait_M.png", "CHAR_MAR", renderer);

		// Loading Markets
		gEngine->getAssetManager()->loadTexture("assets/gfx/sprites/Market_Game/Placeholder_Game_MarketFree.png", "MKT_NULL", renderer);
		gEngine->getAssetManager()->loadTexture("assets/gfx/sprites/Market_Game/Placeholder_Game_MarketWriggle.png", "MKT_WRIG", renderer);

		// Loading HUD Decals
		gEngine->getAssetManager()->loadTexture("assets/gfx/sprites/Common/Placeholder_Text.png", "TEXT", renderer);


		/* Sprite Creation */

		// Create Background Sprite
		sprite_set.insert({ "background",
			std::make_unique<Engine::Sprite>(gEngine->getAssetManager()->getTexture("BGO"), 1280, 720) });
		sprite_set.insert({ "background_cloud",
			std::make_unique<Engine::Sprite>(gEngine->getAssetManager()->getTexture("BGOCloud"), 2444, 144) });
		sprite_set.at("background_cloud")->setXPos(0);
		sprite_set.at("background_cloud")->setYPos(0);
		sprite_set.at("background_cloud")->setXVel(-.05);
		sprite_set.insert({ "background_cloud1",
			std::make_unique<Engine::Sprite>(gEngine->getAssetManager()->getTexture("BGOCloud"), 2444, 72) });
		sprite_set.at("background_cloud1")->setXPos(-611);
		sprite_set.at("background_cloud1")->setYPos(150);
		sprite_set.at("background_cloud1")->setXVel(-.1);

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

		// Loading HUD Decals
		sprite_set.insert({ "Text",
			std::make_unique<Engine::Sprite>(gEngine->getAssetManager()->getTexture("TEXT"), 561, 567) });


		return true;
	}

	void Market_Game::update(Engine::Engine* gEngine, Sprite_Map& sprite_set, Player_Set& player_set) {

		// Input Functions

		if (gEngine->getInput()->isKeyPressed(SDL_SCANCODE_UP)) {
			sprite_set.at("MID_Null")->setAlpha(100);
		}
	
	}

	void Market_Game::render(SDL_Renderer* renderer, Sprite_Map& sprite_set, Player_Set& player_set) {
		sprite_set.at("background")->draw(renderer, Engine::Vector2i(0, 0));
		if (sprite_set.at("background_cloud")->getXPos() < -1222) {
			sprite_set.at("background_cloud")->setXPos(0);
		}
		sprite_set.at("background_cloud1")->draw(renderer);
		if (sprite_set.at("background_cloud1")->getXPos() < -1222) {
			sprite_set.at("background_cloud1")->setXPos(0);
		}
		sprite_set.at("background_cloud")->draw(renderer);
		sprite_set.at("background_cloud1")->draw(renderer);

		sprite_set.at("player")->draw(renderer, Engine::Vector2i(980,0));

		for (int i = 0; i < 5; ++i) {
			sprite_set.at(player_set[0]->getLand()->getMarketStr(i))->draw(renderer, Engine::Vector2i(275 + i * 150, 350 + 50 * (i % 2)));
		}
		int newLine = 0;
		int offset = 0;

		for (int i = 0; i < test_string.size(); i++) {
			offset += 28;
			char character = test_string.at(i);
			if (character == '\n') {
				newLine++;
				offset = 0;
			}
			else {
				if ((character >= 97 && character <= 122) || (character == ' ')) {
					offset -= 8;
				}
				sprite_set.at("Text")->draw(renderer, Engine::Vector2i(offset, 600 + 34 * newLine),
					Engine::Vector2i(32, 32), SDL_Rect(_char_map.at(test_string.at(i)).x, _char_map.at(test_string.at(i)).y, 16, 16));
			}
		}
	}
	/*
		gEngine->getAssetManager()->loadTexture("assets/gfx/sprites/Market_Game/Placeholder_Game_MarketKisume.png", "MKT_KISU", renderer);
		sprite_set.insert({ "MID_Kisume",
			std::make_unique<Engine::Sprite>(gEngine->getAssetManager()->getTexture("MKT_KISU"), 128, 128) });
		gEngine->getAssetManager()->loadTexture("assets/gfx/sprites/Market_Game/Placeholder_Game_MarketKogasa.png", "MKT_KOGA", renderer);
		sprite_set.insert({ "MID_Kogasa",
			std::make_unique<Engine::Sprite>(gEngine->getAssetManager()->getTexture("MKT_KOGA"), 128, 128) });
		gEngine->getAssetManager()->loadTexture("assets/gfx/sprites/Market_Game/Placeholder_Game_MarketNazrin.png", "MKT_NAZR", renderer);
		sprite_set.insert({ "MID_Nazrin",
			std::make_unique<Engine::Sprite>(gEngine->getAssetManager()->getTexture("MKT_NAZR"), 128, 128) });

		return true;
	*/
}