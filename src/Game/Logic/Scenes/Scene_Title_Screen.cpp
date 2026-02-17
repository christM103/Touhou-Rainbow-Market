#include "Game/Logic/Scenes.hpp"
#include "Engine/Graphics/AssetManager.hpp"

namespace TR {

    Title_Screen::Title_Screen() {
        _currState = SC_Title;
        _nextState = _currState;
    }

    bool Title_Screen::create(SDL_Renderer* renderer, Engine::Engine* gEngine) {

        gEngine->getAssetManager()->loadTexture("assets/gfx/sprites/Title_Screen/Placeholder_Title.png", "TITLE", renderer);

        // Creates the camera
        Engine::Entity CAMERA = gEngine->getECSManager()->createEntity("CAMERA");
        gEngine->getECSManager()->addComponent<Engine::CameraComponent>(CAMERA);

        // Creates the BGO
        Engine::Entity BGO = gEngine->getECSManager()->createEntity("BGO");
        gEngine->getECSManager()->addComponent<Engine::TransformComponent>(BGO, Engine::Vector2i{ 0,0 }, 0.0f, Engine::Vector2f{ 0.0f,0.0f });
        gEngine->getECSManager()->addComponent<Engine::SpriteComponent>(BGO, Engine::Recti{ 0,0,1280,720 }, Engine::Vector2i(1280, 720), "TITLE");
        auto& input = gEngine->getECSManager()->addComponent<Engine::InputComponent>(BGO);
        input.newKey(SDL_SCANCODE_SPACE);

        // Creates the Text
        Engine::Entity TEXT = gEngine->getECSManager()->createEntity("TEXT");
        gEngine->getECSManager()->addComponent<Engine::TransformComponent>(TEXT, Engine::Vector2i{ (gEngine->getWindow()->getWidth() / 2), 600 }, 0.0f, Engine::Vector2f{ 0.0f,0.0f }, true);
        gEngine->getECSManager()->addComponent<Engine::TextComponent>(TEXT, "Press Space to play!", 60, Engine::Vector4i(0, 0, 0, 255));

        // Initilizing the Systems
        gEngine->getECSManager()->addSystem<Engine::RenderSystem>();
        gEngine->getECSManager()->addSystem<Engine::MotionSystem>();
        gEngine->getECSManager()->addSystem<Engine::InputSystem>();
        gEngine->getECSManager()->addSystem<Engine::CollisionSystem>();
        gEngine->getECSManager()->addSystem<Engine::CameraSystem>();

        return true;
    }

    void Title_Screen::update(Engine::Engine* gEngine) {
        if (gEngine->getECSManager()->getComponent<Engine::InputComponent>(gEngine->getECSManager()->getEntities().at("BGO"))->keyPressed(SDL_SCANCODE_SPACE)) {
            _nextState = SC_CharS;
            gEngine->getECSManager()->destroyEntity("BGO");
            gEngine->getECSManager()->destroyEntity("TEXT");
        }
    }

}