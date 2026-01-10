#include "Game/logic.hpp"
#include "Game/logic_obj.hpp"
#include "Engine/Graphics/AssetManager.hpp"

namespace TR {
    Title_Screen::Title_Screen() {
        _currState = SC_Title;
        _nextState = _currState;
    }
    Title_Screen::~Title_Screen() {}

    bool Title_Screen::create(SDL_Renderer* renderer, Engine::Engine* gEngine, Sprite_Map& sprite_set, Player_Set& player_set) {

        start_prompt.setColor({ 0,0,0,255 });

        gEngine->getAssetManager()->loadTexture("assets/gfx/sprites/Title_Screen/Placeholder_Title.png", "TITLE", renderer);
        gEngine->getAssetManager()->storeTexture(start_prompt.load(renderer, Engine::Recti{ 0, 0, 370 * SCREEN_SCALE, 200 * SCREEN_SCALE }), "TEXT", renderer);

        sprite_set.insert({ "background",
            std::make_unique<Engine::Sprite>(gEngine->getAssetManager()->getTexture("TITLE"), 1280, 720) });
        sprite_set.insert({ "text",
            std::make_unique<Engine::Sprite>(gEngine->getAssetManager()->getTexture("TEXT"), start_prompt.getRenderSize().size.x, start_prompt.getRenderSize().size.y) });
        
        return true;
    }

    void Title_Screen::update(Engine::Engine* gEngine, Sprite_Map& sprite_set, Player_Set& player_set) {
        if (gEngine->getInput()->isKeyPressed(SDL_SCANCODE_SPACE)) {
            _nextState = SC_CharS;
        }
    }

    void Title_Screen::render(SDL_Renderer* renderer, Engine::Engine* gEngine, Sprite_Map& sprite_set, Player_Set& player_set) {
        sprite_set.at("background")->draw(renderer, Engine::Vector2i(0, 0));
        sprite_set.at("text")->draw(renderer, Engine::Vector2i((gEngine->getWindow()->getWidth() / 2) - (start_prompt.getRenderSize().size.x / 2), 600));
    }
}