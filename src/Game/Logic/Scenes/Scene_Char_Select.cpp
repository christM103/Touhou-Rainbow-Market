#include "Game/Logic/Scenes.hpp"
#include "Game/Logic/Enums.hpp"
#include "Game/Objects/Components/CharSelectComponents.hpp"
#include "Game/Objects/Systems/CharSelectSystems.hpp"
#include "Engine/Graphics/AssetManager.hpp"

namespace TR {
    Char_Select::Char_Select() {
        _currState = Scene_ID::CharS;
        _nextState = _currState;
        setYAMLPath(PATH_YAML_CHARSELECT);
    }

    bool Char_Select::create() {
        if (isGameTextStringEmpty()) {
            appendYAMLString("select_debug");
        }

        if (!getDebugManager().isEnabled()) {
            // Load the background and portrait textures
            gState.gAssets->loadTexture(GFX_FOLDER + "Char_Select/Placeholder_CharS_BG.png", "BGO", gState.gRenderer);
            gState.gAssets->loadTexture(GFX_FOLDER + "Common/Placeholder_Portrait_R.png", "Portait_R", gState.gRenderer);
            gState.gAssets->loadTexture(GFX_FOLDER + "Common/Placeholder_Portrait_M.png", "Portait_M", gState.gRenderer);

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
        }

        Engine::Entity CHAR_SELECT = gState.gECS->createEntity("CHAR_SELECT");
        gState.gECS->addComponent<SelectComponent>(CHAR_SELECT);

        return true;
    }

    void Char_Select::update() {
        SelectComponent* select_component = gState.gECS->getComponent<SelectComponent>(gState.gECS->getEntity("CHAR_SELECT"));
        if (getDebugManager().isEnabled()) {
            _state_data.prompt_flags = static_cast<Prompt_Flags>(getDebugManager().getSelectedPromptIndex());
        }
        else {
            uint8_t new_selected = static_cast<uint8_t>(select_component->_current_selected);

            if (gState.gInput->keyPressed(SDL_SCANCODE_LEFT)) {
                if (new_selected - 1 > 0) {
                    select_component->_current_selected = Char_State(new_selected - 1);
                }
            }
            else if (gState.gInput->keyPressed(SDL_SCANCODE_RIGHT)) {
                if (static_cast<int>(new_selected + 1) < NUMBER_OF_CHARACTERS) {
                    select_component->_current_selected = Char_State(new_selected + 1);
                }
            }
        }
        
        select_component->_current_selected = static_cast<Char_State>(_state_data.prompt_flags);

        if (gState.gInput->keyPressed(SDL_SCANCODE_RETURN)) {
            this->setSceneNext(Scene_ID::Main);
            this->clearGameTextString();
            if (getDebugManager().isEnabled()) {
                resetPromptAction();
            }
            else {

            }

            Engine::Entity PLAYER = gState.gECS->createEntity("PLAYER");
            gState.gPlayer = &gState.gECS->addComponent<PlayerComponent>(PLAYER, select_component->_current_selected, Player_ID::Player_1);
            _state_data.current_player = gState.gPlayer->player_number;
            gState.gECS->addSystem<PlayerSystem>();

            gState.gECS->destroyEntity("CHAR_SELECT");
            gState.gECS->destroyEntity("REIMU");
            gState.gECS->destroyEntity("MARISA");
            gState.gECS->destroyEntity("TEXT");

            gState.gECS->destroyEntity("BGO");
        }
    }
}