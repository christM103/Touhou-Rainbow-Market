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
    
    SDL_Renderer* renderer = gEngine->getWindow()->getRenderer();
    /*
    gEngine->getAssetManager()->loadTexture("assets/player.png", "player", renderer);
    playerSprite = new Engine::Sprite(gEngine->getAssetManager()->getTexture("player"), 64, 64);
    */
    _currScene->create(renderer, gEngine);
    gEngine->getECSManager()->create();
    return true;
}

void Game::update(float deltaTime) {

    _currScene->update(gEngine);

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
    
    gEngine->getECSManager()->update();
    
}

void Game::render() {
    // Get the renderer from the engine's window

    gEngine->getECSManager()->render();
}
void Game::quit() {
    // Shutdown code for the game
    gEngine->getECSManager()->quit();
}

void Game::move_state(std::unique_ptr<TR::Scene> newState) {
    SDL_Renderer* renderer = gEngine->getWindow()->getRenderer();
    _currScene = std::move(newState);

	// Reset to current sprite set
	gEngine->getAssetManager()->clear();
    gEngine->getECSManager()->create();
    _currScene->create(renderer, gEngine);
}
