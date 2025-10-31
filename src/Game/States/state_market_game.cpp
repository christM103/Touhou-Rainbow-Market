#include "Game/logic.hpp"
#include "Engine/Graphics/AssetManager.hpp"

namespace TR {

	Market_Game::Market_Game() {}

	Market_Game::Market_Game(std::vector<std::shared_ptr<TR::Player_Data>> players) {}

	Market_Game::~Market_Game() {}

	bool Market_Game::create(SDL_Renderer* renderer, Engine::Engine* gEngine, Sprite_Map& sprite_set) {
		// Loading Background Sprite
		gEngine->getAssetManager()->loadTexture("assets/gfx/sprites/Market_Game/Placeholder_Game_BGLand.png", "BGO", renderer);
		sprite_set.insert({ "background",
			std::make_unique<Engine::Sprite>(gEngine->getAssetManager()->getTexture("BGO"), 800, 600) });

		// Loading Market Sprites
		gEngine->getAssetManager()->loadTexture("assets/gfx/sprites/Market_Game/Placeholder_Game_MarketFree.png", "MKT_NULL", renderer);
		sprite_set.insert({ "MID_Null",
			std::make_unique<Engine::Sprite>(gEngine->getAssetManager()->getTexture("MKT_NULL"), 128, 128) });
		gEngine->getAssetManager()->loadTexture("assets/gfx/sprites/Market_Game/Placeholder_Game_MarketWriggle.png", "MKT_WRIG", renderer);
		sprite_set.insert({ "MID_Wriggle",
			std::make_unique<Engine::Sprite>(gEngine->getAssetManager()->getTexture("MKT_WRIG"), 128, 128) });
		return true;
	}

	void Market_Game::update(Engine::Engine* gEngine, Sprite_Map& sprite_set, Player_Set& player_set) {
		if (gEngine->getInput()->isKeyPressed(SDL_SCANCODE_UP)) {
			sprite_set.at("MID_Null")->setAlpha(100);
		}
	
	}

	void Market_Game::render(SDL_Renderer* renderer, Sprite_Map& sprite_set, Player_Set& player_set) {
		sprite_set.at("background")->draw(renderer, Engine::Vector2i(0, 0));
		for (int i = 0; i < 5; ++i) {
			sprite_set.at(player_set[0]->getLand()->getMarketStr(i))->draw(renderer, Engine::Vector2i(30 + i * 150, 250 + 50 * (i % 2)));
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