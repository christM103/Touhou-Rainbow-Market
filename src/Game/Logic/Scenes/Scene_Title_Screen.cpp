#include "Game/Logic/Scenes.hpp"
#include "Engine/Graphics/AssetManager.hpp"

namespace TR {

    Title_Screen::Title_Screen() {
        _currState = Scene_ID::Title;
        _nextState = _currState;
        setYAMLPath(PATH_YAML_TITLE);
    }

    bool Title_Screen::create() {
        if (isGameTextStringEmpty()) {
            appendYAMLString("title_debug");
        }

        if (!getDebugManager().isEnabled()) {
            // Load the background texture
            gState.gAssets->loadTexture(GFX_FOLDER + "Title_Screen/Placeholder_Title.png", "TITLE", gState.gRenderer);

            // Creates the BGO
            Engine::Entity BGO = gState.gECS->createEntity("BGO");
            gState.gECS->addComponent<Engine::TransformComponent>(BGO);
            gState.gECS->addComponent<Engine::SpriteComponent>(BGO, Engine::Recti(Engine::Vector2i{}, gState.gWindow->getSize()), gState.gWindow->getSize(), "TITLE");

            // Creates the Text
            Engine::Entity TEXT = gState.gECS->createEntity("TEXT");
            gState.gECS->addComponent<Engine::TransformComponent>(TEXT, Engine::Vector2i{ (gState.gWindow->getWidth() / 2), 600 }).centered = true;
            gState.gECS->addComponent<Engine::TextComponent>(TEXT, "Press Space to play!", 60, Engine::Vector4i(0, 0, 0, 255));
        }

        return true;
    }

    void Title_Screen::update() {
        if (gState.gInput->keyPressed(SDL_SCANCODE_SPACE)) {
            this->setSceneNext(Scene_ID::CharS);
            gState.gECS->destroyEntity("BGO");
            gState.gECS->destroyEntity("TEXT");
        }
    }

}