#include "Game/Logic/Scenes.hpp"
#include "Engine/Graphics/AssetManager.hpp"

namespace TR {
    Char_Select::Char_Select() {
        _currState = SC_CharS;
        _nextState = _currState;
    }

    bool Char_Select::create(SDL_Renderer* renderer, Engine::Engine* gEngine, Player_Set& player_set) {
        gEngine->getAssetManager()->loadTexture("assets/gfx/sprites/Char_Select/Placeholder_CharS_BG.png", "BGO", renderer);
        gEngine->getAssetManager()->loadTexture("assets/gfx/sprites/Common/Placeholder_Portrait_R.png", "Portait_R", renderer);
        gEngine->getAssetManager()->loadTexture("assets/gfx/sprites/Common/Placeholder_Portrait_M.png", "Portait_M", renderer);

        // Creates the Backgrounds
        Engine::Entity BGO = gEngine->getECSManager()->createEntity();
        gEngine->getECSManager()->addComponent<Engine::TransformComponent>(BGO, Engine::Vector2i{ 0,0 }, 0.0f, Engine::Vector2f{ 0.0f,0.0f });
        gEngine->getECSManager()->addComponent<Engine::SpriteComponent>(BGO, Engine::Recti{ 0,0,1280,720 }, Engine::Vector2i(1280, 720), "BGO");
        gEngine->getECSManager()->addComponent<Engine::RenderLayerComponent>(BGO, Engine::RenderLayerComponent::BG);
        auto& input = gEngine->getECSManager()->addComponent<Engine::InputComponent>(BGO);
        input.newKey(SDL_SCANCODE_LEFT);
        input.newKey(SDL_SCANCODE_RIGHT);
        active_entities.emplace("BGO", BGO);

        // Creates the Portaits
        Engine::Entity REIMU = gEngine->getECSManager()->createEntity();
        gEngine->getECSManager()->addComponent<Engine::TransformComponent>(REIMU, Engine::Vector2i{ 20,30 }, 0.0f, Engine::Vector2f{ 0.0f,0.0f });
        gEngine->getECSManager()->addComponent<Engine::SpriteComponent>(REIMU, Engine::Recti{ 0,0,600,600 }, Engine::Vector2i(600, 600), "Portait_R");
        gEngine->getECSManager()->addComponent<Engine::RenderLayerComponent>(REIMU, Engine::RenderLayerComponent::SPRITE);
        active_entities.emplace("BGO", REIMU);

        Engine::Entity MARISA = gEngine->getECSManager()->createEntity();
        gEngine->getECSManager()->addComponent<Engine::TransformComponent>(MARISA, Engine::Vector2i{ 660,30 }, 0.0f, Engine::Vector2f{ 0.0f,0.0f });
        gEngine->getECSManager()->addComponent<Engine::SpriteComponent>(MARISA, Engine::Recti{ 0,0,600,600 }, Engine::Vector2i(600, 600), "Portait_M");
        gEngine->getECSManager()->addComponent<Engine::RenderLayerComponent>(MARISA, Engine::RenderLayerComponent::SPRITE);
        active_entities.emplace("BGO", MARISA);

        // Creates the Text
        Engine::Entity TEXT = gEngine->getECSManager()->createEntity();
        gEngine->getECSManager()->addComponent<Engine::TransformComponent>(TEXT, Engine::Vector2i{ gEngine->getWindow()->getWidth() / 2, 650 }, 0.0f, Engine::Vector2f{ 0.0f,0.0f }, true);
        gEngine->getECSManager()->addComponent<Engine::TextComponent>(TEXT, "Choose your character using the left and right arrow keys", 40, Engine::Vector4i(0, 0, 0, 255));
        gEngine->getECSManager()->addComponent<Engine::RenderLayerComponent>(TEXT, Engine::RenderLayerComponent::FG);
        active_entities.emplace("BGO", TEXT);

        return true;
    }

    void Char_Select::update(Engine::Engine* gEngine, Player_Set& player_set) {
        if (gEngine->getECSManager()->getComponent<Engine::InputComponent>(active_entities.at("BGO"))->keyPressed(SDL_SCANCODE_LEFT)) {
            player_set.insert(player_set.end(), std::make_shared<TR::Player_Reimu>(TR::PI_Player_1, 1));
            _nextState = SC_Main;
            active_entities.clear();
        }
        else if (gEngine->getECSManager()->getComponent<Engine::InputComponent>(active_entities.at("BGO"))->keyPressed(SDL_SCANCODE_RIGHT)) {
            player_set.insert(player_set.end(), std::make_shared<TR::Player_Marisa>(TR::PI_Player_1, 1));
            _nextState = SC_Main;
            active_entities.clear();
        }
    }
}