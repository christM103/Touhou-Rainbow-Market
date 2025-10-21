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
}

Game::~Game() {
    // Destructor implementation
}

bool Game::create() {
    // Initialization code for the game
    SDL_Renderer* renderer = gEngine->getWindow()->getRenderer();
    gEngine->getAssetManager()->loadTexture("assets/player.png", "player", renderer);
    playerSprite = new Engine::Sprite(gEngine->getAssetManager()->getTexture("player"), 64, 64);
    return true;
}

void Game::update(float deltaTime) {
    // Update logic for the game
}

void Game::render() {
    // Get the renderer from the engine's window
    SDL_Renderer* renderer = gEngine->getWindow()->getRenderer();

    // Example rendering code
    playerSprite->draw(renderer, Engine::Vector2i(300, 100));
}
void Game::quit() {
    // Shutdown code for the game
    delete playerSprite;
}