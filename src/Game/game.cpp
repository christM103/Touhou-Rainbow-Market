// Copyright 2025 Chrisfantasy
#include <iostream>
#include <SDL2/SDL.h>
#include "Game/game.hpp"
#include "Engine/Core/Engine.hpp"
extern Engine::Engine* gEngine;

Game::Game() {
    // Constructor implementation
}

Game::~Game() {
    // Destructor implementation
}

bool Game::create() {
    // Initialization code for the game
    return true;
}

void Game::update(float deltaTime) {
    // Update logic for the game
}

void Game::render() {
    // Get the renderer from the engine's window
    SDL_Renderer* renderer = gEngine->getWindow()->getRenderer();

    // Example rendering code
    SDL_SetRenderDrawColor(renderer, 6, 135, 255, 255);
    SDL_Rect rect = { 50, 50, 200, 150 };
    SDL_RenderDrawRect(renderer, &rect);
}
void Game::quit() {
    // Shutdown code for the game
}