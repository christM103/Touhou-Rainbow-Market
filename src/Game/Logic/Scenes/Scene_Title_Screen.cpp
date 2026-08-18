#include "Game/Logic/Scenes.hpp"
#include "Engine/Graphics/AssetManager.hpp"

namespace TR {

    Title_Screen::Title_Screen() {
        _currState = SC_Title;
        _nextState = _currState;
    }

    bool Title_Screen::create() {

        if (gState.gCMD) {
            std::cout << "Welcome to the Touhou Rainbow Market Demo!\n\t*- Press Space to play -*\n";
        }
        else {
            // Load the background texture
            gState.gAssets->loadTexture(gState.GFX_FOLDER + "Title_Screen/Placeholder_Title.png", "TITLE", gState.gRenderer);

            // Creates the BGO
            Engine::Entity BGO = gState.gECS->createEntity("BGO");
            gState.gECS->addComponent<Engine::TransformComponent>(BGO);
            gState.gECS->addComponent<Engine::SpriteComponent>(BGO, Engine::Recti(Engine::Vector2i{}, gState.gWindow->getSize()), gState.gWindow->getSize(), "TITLE");

            // Creates the Text
            Engine::Entity TEXT = gState.gECS->createEntity("TEXT");
            gState.gECS->addComponent<Engine::TransformComponent>(TEXT, Engine::Vector2i{ (gState.gWindow->getWidth() / 2), 600 }).centered = true;
            gState.gECS->addComponent<Engine::TextComponent>(TEXT, "Press Space to play!", 60, Engine::Vector4i(0, 0, 0, 255));
        }
		

		// Initialize the input for the scene
        gState.gInput->newKey(SDL_SCANCODE_SPACE);

        return true;
    }

    void Title_Screen::update() {
        if (gState.gInput->keyPressed(SDL_SCANCODE_SPACE)) {
            this->setSceneNext(SC_CharS);
            gState.gECS->destroyEntity("BGO");
            gState.gECS->destroyEntity("TEXT");
			gState.gInput->removeKey(SDL_SCANCODE_SPACE);
        }
    }

}