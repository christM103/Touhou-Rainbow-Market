#include "Game/logic.hpp"
#include "Engine/Graphics/AssetManager.hpp"

namespace TR {
    Char_Select::Char_Select() {
        _currState = SC_CharS;
        _nextState = _currState;
    }

    Char_Select::~Char_Select() {}

    bool Char_Select::create(SDL_Renderer* renderer, Engine::Engine* gEngine, Sprite_Map& sprite_set, Player_Set& player_set) {
        gEngine->getAssetManager()->loadTexture("assets/gfx/sprites/Char_Select/Placeholder_CharS_BG.png", "BGO", renderer);
        gEngine->getAssetManager()->loadTexture("assets/gfx/sprites/Common/Placeholder_Portrait_R.png", "Portait_R", renderer);
        gEngine->getAssetManager()->loadTexture("assets/gfx/sprites/Common/Placeholder_Portrait_M.png", "Portait_M", renderer);
        gEngine->getAssetManager()->storeTexture(char_choice_prompt.load(renderer, Engine::Recti{ 0, 0, 720 * SCREEN_SCALE, 200 * SCREEN_SCALE }), "TEXT", renderer);

        sprite_set.insert({ "background",
            std::make_unique<Engine::Sprite>(gEngine->getAssetManager()->getTexture("BGO"), 1280, 720) });
        sprite_set.insert({ "reimu",
            std::make_unique<Engine::Sprite>(gEngine->getAssetManager()->getTexture("Portait_R"), 600, 600) });
        sprite_set.insert({ "marisa",
            std::make_unique<Engine::Sprite>(gEngine->getAssetManager()->getTexture("Portait_M"), 600, 600) });
        sprite_set.insert({ "text",
            std::make_unique<Engine::Sprite>(gEngine->getAssetManager()->getTexture("TEXT"), char_choice_prompt.getRenderSize().size.x, char_choice_prompt.getRenderSize().size.y) });
        return true;
    }

    void Char_Select::update(Engine::Engine* gEngine, Sprite_Map& sprite_set, Player_Set& player_set) {
        if (gEngine->getInput()->isKeyPressed(SDL_SCANCODE_LEFT)) {
            player_set.insert(player_set.end(), std::make_shared<TR::Player_Reimu>(TR::PI_Player_1, 1));
            _nextState = SC_Main;
        }
        else if (gEngine->getInput()->isKeyPressed(SDL_SCANCODE_RIGHT)) {
            player_set.insert(player_set.end(), std::make_shared<TR::Player_Marisa>(TR::PI_Player_1, 1));
            _nextState = SC_Main;
        }
    }

    void Char_Select::render(SDL_Renderer* renderer, Engine::Engine* gEngine, Sprite_Map& sprite_set, Player_Set& player_set) {
        sprite_set.at("background")->draw(renderer, Engine::Vector2i(0, 0));
        sprite_set.at("text")->draw(renderer, Engine::Vector2i((gEngine->getWindow()->getWidth() / 2) - (char_choice_prompt.getRenderSize().size.x / 2), 650));
        sprite_set.at("reimu")->draw(renderer, Engine::Vector2i(20, 30));
        sprite_set.at("marisa")->draw(renderer, Engine::Vector2i(660, 30));
    }
}