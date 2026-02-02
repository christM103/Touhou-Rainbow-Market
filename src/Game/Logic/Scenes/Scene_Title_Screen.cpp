#include "Game/Logic/Scenes.hpp"
#include "Engine/Graphics/AssetManager.hpp"

namespace TR {

    Title_Screen::Title_Screen() {
        _currState = SC_Title;
        _nextState = _currState;
    }

    bool Title_Screen::create(SDL_Renderer* renderer, Engine::Engine* gEngine, Player_Set& player_set) {

        gEngine->getAssetManager()->loadTexture("assets/gfx/sprites/Title_Screen/Placeholder_Title.png", "TITLE", renderer);

        gEngine->getECSManager()->addSystem<Engine::RenderSystem>();

        // Creates the BGO
        Engine::Entity BGO = gEngine->getECSManager()->createEntity();
        gEngine->getECSManager()->addComponent<Engine::TransformComponent>(BGO, Engine::Vector2i{ 0,0 }, 0.0f, Engine::Vector2f{ 0.0f,0.0f });
        gEngine->getECSManager()->addComponent<Engine::SpriteComponent>(BGO, Engine::Recti{ 0,0,1280,720 }, Engine::Vector2i(1280, 720), "TITLE");

        // Creates the Text
        Engine::Entity TEXT = gEngine->getECSManager()->createEntity();
        gEngine->getECSManager()->addComponent<Engine::TransformComponent>(TEXT, Engine::Vector2i{ (gEngine->getWindow()->getWidth() / 2), 600 }, 0.0f, Engine::Vector2f{ 0.0f,0.0f }, true);
        gEngine->getECSManager()->addComponent<Engine::TextComponent>(TEXT, "Press Space to play!", 60, Engine::Vector4i(0, 0, 0, 255));

        return true;
    }

    void Title_Screen::update(Engine::Engine* gEngine, Player_Set& player_set) {
        if (gEngine->getInput()->isKeyPressed(SDL_SCANCODE_SPACE)) {
            _nextState = SC_CharS;
            active_entities.clear();
        }
    }

    void Title_Screen::render(SDL_Renderer* renderer, Engine::Engine* gEngine, Player_Set& player_set) {
        
    }
}