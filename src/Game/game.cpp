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
    _currScene->create(renderer, gEngine, _player_set);
    gEngine->getECSManager()->create();
    return true;
}

void Game::update(float deltaTime) {

    _beat++;
    if (_beat % 5 == 0) {
        // Update logic for the game

        _currScene->update(gEngine, _player_set);

        if (gEngine->getInput()->isKeyPressed(SDL_SCANCODE_Z) && (_player_set.size() > 0)) {
            if (!_input_pressed.at(SDL_SCANCODE_Z)) {
                _player_set.at(0)->getLand()->setLand(0, TR::Wriggle());
                _input_pressed.at(SDL_SCANCODE_Z) = true;
            }
        }
        else {
            _input_pressed.at(SDL_SCANCODE_Z) = false;
        }

        _beat = 0;
    }

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
                if (_player_set.size()) {
                    move_state(std::make_unique<TR::Market_Game>());
                }
                break;
            default:
                break;
        }
    }
    
    gEngine->getECSManager()->update();
    
}

void Game::render() {
    // Get the renderer from the engine's window
    SDL_Renderer* renderer = gEngine->getWindow()->getRenderer();

    // Example rendering code
    //playerSprite->draw(renderer, Engine::Vector2i(0, 0));
    _currScene->render(renderer, gEngine, _player_set);
    gEngine->getECSManager()->render();
}
void Game::quit() {
    // Shutdown code for the game
    gEngine->getECSManager()->quit();
    _player_set.clear();
}

void Game::move_state(std::unique_ptr<TR::Scene> newState) {
    SDL_Renderer* renderer = gEngine->getWindow()->getRenderer();
    _currScene = std::move(newState);

	// Reset to current sprite set
    gEngine->getECSManager()->destroyAllEntities();
	gEngine->getAssetManager()->clear();
    _currScene->create(renderer, gEngine, _player_set);
    gEngine->getECSManager()->create();
}
