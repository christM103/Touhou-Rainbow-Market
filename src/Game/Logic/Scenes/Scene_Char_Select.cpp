#include "Game/Logic/Scenes.hpp"
#include "Game/Objects/Components/CharSelectComponents.hpp"
#include "Game/Objects/Systems/CharSelectSystems.hpp"
#include "Engine/Graphics/AssetManager.hpp"

namespace TR {
    Char_Select::Char_Select() {
        _currState = SC_CharS;
        _nextState = _currState;
    }

    bool Char_Select::create() {
		// Load the background and portrait textures
        gState.gAssets->loadTexture(gState.GFX_FOLDER + "Char_Select/Placeholder_CharS_BG.png", "BGO", gState.gRenderer);
        gState.gAssets->loadTexture(gState.GFX_FOLDER + "Common/Placeholder_Portrait_R.png", "Portait_R", gState.gRenderer);
        gState.gAssets->loadTexture(gState.GFX_FOLDER + "Common/Placeholder_Portrait_M.png", "Portait_M", gState.gRenderer);

        // Creates the Backgrounds
        Engine::Entity BGO = gState.gECS->createEntity("BGO");
        gState.gECS->addComponent<Engine::TransformComponent>(BGO);
        gState.gECS->addComponent<Engine::SpriteComponent>(BGO, Engine::Recti(Engine::Vector2i{}, gState.gWindow->getSize()), gState.gWindow->getSize(), "BGO");
        gState.gECS->addComponent<Engine::RenderLayerComponent>(BGO, Engine::RenderLayerComponent::BG);

        // Creates the Portaits
        Engine::Entity REIMU = gState.gECS->createEntity("REIMU");
        gState.gECS->addComponent<Engine::TransformComponent>(REIMU, Engine::Vector2i{ 20,30 }, 0.0f, Engine::Vector2f{ 0.0f,0.0f });
        gState.gECS->addComponent<Engine::SpriteComponent>(REIMU, Engine::Recti{ 0,0,600,600 }, Engine::Vector2i(600, 600), "Portait_R");
        gState.gECS->addComponent<Engine::RenderLayerComponent>(REIMU, Engine::RenderLayerComponent::SPRITE);

        Engine::Entity MARISA = gState.gECS->createEntity("MARISA");
        gState.gECS->addComponent<Engine::TransformComponent>(MARISA, Engine::Vector2i{ 660,30 }, 0.0f, Engine::Vector2f{ 0.0f,0.0f });
        gState.gECS->addComponent<Engine::SpriteComponent>(MARISA, Engine::Recti{ 0,0,600,600 }, Engine::Vector2i(600, 600), "Portait_M");
        gState.gECS->addComponent<Engine::RenderLayerComponent>(MARISA, Engine::RenderLayerComponent::SPRITE);

        // Creates the Text
        Engine::Entity TEXT = gState.gECS->createEntity("TEXT");
        gState.gECS->addComponent<Engine::TransformComponent>(TEXT, Engine::Vector2i{ gState.gWindow->getWidth() / 2, 650 }).centered = true;
        gState.gECS->addComponent<Engine::TextComponent>(TEXT, "Choose your character using the left and right arrow keys", 40, Engine::Vector4i(0, 0, 0, 255));
        gState.gECS->addComponent<Engine::RenderLayerComponent>(TEXT, Engine::RenderLayerComponent::FG);

		// Initialize the input for the scene
        gState.gInput->newKey(SDL_SCANCODE_LEFT);
        gState.gInput->newKey(SDL_SCANCODE_RIGHT);

        return true;
    }

    void Char_Select::update() {
        if (gState.gInput->keyPressed(SDL_SCANCODE_LEFT) || gState.gInput->keyPressed(SDL_SCANCODE_RIGHT)) {

            this->setSceneNext(SC_Main);

            gState.gECS->destroyEntity("REIMU");
            gState.gECS->destroyEntity("MARISA");
            gState.gECS->destroyEntity("TEXT");

            Engine::Entity PLAYER = gState.gECS->createEntity("PLAYER");
            if (gState.gInput->keyPressed(SDL_SCANCODE_LEFT)) {
                gState.gPlayer = &gState.gECS->addComponent<PlayerComponent>(PLAYER, Player_Data::S_Reimu, Player_Data::PI_Player_1);
            }
            else if (gState.gInput->keyPressed(SDL_SCANCODE_RIGHT)) {
                gState.gPlayer = &gState.gECS->addComponent<PlayerComponent>(PLAYER, Player_Data::S_Marisa, Player_Data::PI_Player_1);
            }
            gState.gECS->addSystem<PlayerSystem>();
            gState.gECS->destroyEntity("BGO");

        }
    }
}