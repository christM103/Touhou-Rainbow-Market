// Copyright 2025 Chrisfantasy
#include <iostream>
#include <SDL2/SDL.h>
#include "Game/game.hpp"
#include "Engine/Core/Engine.hpp"
#include "Engine/Graphics/AssetManager.hpp"
#include "Engine/Graphics/Sprite.hpp"


extern Engine::Engine* gEngine;

Game::Game() {
    // Constructor implementation
    _currScene.reset(new TR::Title_Screen());
}

Game::~Game() {
    // Destructor implementation
    
}

bool Game::create() {
    // Initialization code for the game 
	gState.gECS = gEngine->getECSManager();
	gState.gAssets = gEngine->getAssetManager();
	gState.gWindow = gEngine->getWindow();
    
	// Get the renderer from the engine's window
    gState.gRenderer = gState.gWindow->getRenderer();
    
    // Creates the camera
    Engine::Entity CAMERA = gState.gECS->createEntity("CAMERA");
    gState.gCamera = &gState.gECS->addComponent<Engine::CameraComponent>(CAMERA);

    // Creates the keyboard input
    Engine::Entity KEYBOARD = gState.gECS->createEntity("KEYBOARD");
    gState.gInput = &gState.gECS->addComponent<Engine::InputComponent>(KEYBOARD);

    // Initialize Mouse Entity
    Engine::Entity MOUSE = gState.gECS->createEntity("MOUSE");
    gState.gMouse = &gState.gECS->addComponent<Engine::MouseComponent>(MOUSE);

    // Initilizing the Systems
    gState.gECS->addSystem<Engine::RenderSystem>();
    gState.gECS->addSystem<Engine::MotionSystem>();
    gState.gECS->addSystem<Engine::InputSystem>();
    gState.gECS->addSystem<Engine::CollisionSystem>();
    gState.gECS->addSystem<Engine::CameraSystem>();
    if (getDebugManager().isEnabled()) {
        Engine::DebugComponent::_debug_active = true;
        gState.gECS->addSystem<Engine::DebugSystem>();
    }
    
    // Initialize the input for the game
    gState.gInput->newKey(SDL_SCANCODE_UP);
    gState.gInput->newKey(SDL_SCANCODE_DOWN);
    gState.gInput->newKey(SDL_SCANCODE_LEFT);
    gState.gInput->newKey(SDL_SCANCODE_RIGHT);

    gState.gInput->newKey(SDL_SCANCODE_SPACE);
    gState.gInput->newKey(SDL_SCANCODE_RETURN);

    gState.gInput->newKey(SDL_SCANCODE_1);
    gState.gInput->newKey(SDL_SCANCODE_2);
    gState.gInput->newKey(SDL_SCANCODE_3);
    gState.gInput->newKey(SDL_SCANCODE_4);
    gState.gInput->newKey(SDL_SCANCODE_5);
    gState.gInput->newKey(SDL_SCANCODE_6);

    gState.gInput->newKey(SDL_SCANCODE_Z);
    gState.gInput->newKey(SDL_SCANCODE_X);
    gState.gInput->newKey(SDL_SCANCODE_C);
    gState.gInput->newKey(SDL_SCANCODE_V);

    // Initialize the YAML Files
    gState.gMarket = YAML::LoadFile(TR::PATH_JSON_MARKET);
    gState.gAction = YAML::LoadFile(TR::PATH_JSON_ACTION);

    // Creates the scene
    _currScene->create();

    gState.gECS->create();


    return true;
}

void Game::update(float deltaTime) {

    _currScene->update();
    if (getDebugManager().isEnabled()) {
        getDebugManager().displayText(_currScene->getGameTextString());
    }
    _currScene->parsePromptAction();

    if (_currScene->getSceneCurr() != _currScene->getSceneNext()) {
        TR::Scene_ID state = _currScene->getSceneNext();
        switch (state) {
            case TR::Scene_ID::Title:
                move_state(std::make_unique<TR::Title_Screen>());
                break;
            case TR::Scene_ID::CharS:
                move_state(std::make_unique<TR::Char_Select>());
                break;
            case TR::Scene_ID::Main:
                move_state(std::make_unique<TR::Market_Game>());
                break;
            default:
                break;
        }
        
    }
    
    gState.gECS->update();
    
}

void Game::render() {
    // Get the renderer from the engine's window

    gState.gECS->render();
}
void Game::quit() {
    // Shutdown code for the game
    gState.gECS->quit();
}

void Game::move_state(std::unique_ptr<TR::Scene> newState) {
    SDL_Renderer* renderer = gEngine->getWindow()->getRenderer();
    _currScene = std::move(newState);

	// Reset to current sprite set
	gState.gAssets->clear();
    gState.gECS->create();
    _currScene->create();
}
