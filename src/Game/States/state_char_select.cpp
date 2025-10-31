#include "Game/logic.hpp"
#include "Engine/Graphics/AssetManager.hpp"

namespace TR {
    Char_Select::Char_Select() {}

    Char_Select::~Char_Select() {}

    bool Char_Select::create(SDL_Renderer* renderer, Engine::Engine* gEngine, Sprite_Map& sprite_set) {
        gEngine->getAssetManager()->loadTexture("assets/gfx/sprites/Char_Select/Placeholder_CharS_BG.png", "BGO", renderer);
        sprite_set.insert({ "background",
            std::make_unique<Engine::Sprite>(gEngine->getAssetManager()->getTexture("BGO"), 800, 600) });
        return true;
    }

    void Char_Select::update(Engine::Engine* gEngine, Sprite_Map& sprite_set, Player_Set& player_set) {}

    void Char_Select::render(SDL_Renderer* renderer, Sprite_Map& sprite_set, Player_Set& player_set) {
        sprite_set.at("background")->draw(renderer, Engine::Vector2i(0, 0));
    }
}