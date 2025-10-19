// Copyright 2025 Chrisfantasy
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

#include "Game/game.hpp"
#include "Engine/Core/Engine.hpp"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

Engine::Engine* gEngine = nullptr;

int main(int argc, char* argv[]) {
    Engine::Engine engine;
    if (!engine.init("Touhou Rainbow Market", SCREEN_WIDTH, SCREEN_HEIGHT)) {
        std::cerr << "Failed to initialize the engine." << std::endl;
        return -1;
    }

    gEngine = &engine;

    Game game;
    engine.run(&game);
    
    return 0;
}
