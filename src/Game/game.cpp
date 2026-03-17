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

	// Creates the scene
    _currScene->create();

    // Initilizing the Systems
    gState.gECS->addSystem<Engine::RenderSystem>();
    gState.gECS->addSystem<Engine::MotionSystem>();
    gState.gECS->addSystem<Engine::InputSystem>();
    gState.gECS->addSystem<Engine::CollisionSystem>();
    gState.gECS->addSystem<Engine::CameraSystem>();
    gState.gECS->create();

    return true;
}

void Game::update(float deltaTime) {

    _currScene->update();

    if (_currScene->getSceneCurr() != _currScene->getSceneNext()) {
        TR::Scene::Scene_ID state = _currScene->getSceneNext();
        switch (state) {
            case TR::Scene::SC_Title:
                move_state(std::make_unique<TR::Title_Screen>());
                break;
            case TR::Scene::SC_CharS:
                move_state(std::make_unique<TR::Char_Select>());
                break;
            case TR::Scene::SC_Main:
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
