#include <iostream>
#include <SDL2/SDL.h>

#include "Engine/Core/Engine.hpp"
#include "Engine/Core/Application.hpp"

namespace Engine {
    Engine::Engine() : deltaTime(0.0f), running(false) {}

    Engine::~Engine() {
        SDL_Quit();
    }

    bool Engine::init(const char* title, int width, int height) {
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
            std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
            return false;
        }

        window = std::make_unique<Window>(title, width, height);
        input = std::make_unique<Input>();

        running = true;
        return true;
    }

    void Engine::run(Application* game) {
        if (!game->create()) {
            std::cerr << "Game create() failed." << std::endl;
            return;
        }

        while (running) {
            input->pollEvent();
            if (input->isQuitRequested()) {
                running = false;
                break;
            }

            // Calculate delta time
            Uint64 now = SDL_GetPerformanceCounter();
            deltaTime = static_cast<float>((now - lastFrameTime) / SDL_GetPerformanceFrequency());
            lastFrameTime = now;

            // Update game state
            game->update(deltaTime);

            // Render frame
            window->clear();
            game->render();
            window->present();
            
            SDL_Delay(1);
        }

        game->quit();
    }

    void Engine::quit() {
        if (running) {
            running = false;
        }
    }


}
