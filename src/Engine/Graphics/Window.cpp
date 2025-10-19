#include <iostream>
#include "Engine/Graphics/Window.hpp"

namespace Engine {
    Window::Window(const char* title, int width, int height) : width(width), height(height) {
        window = SDL_CreateWindow(title,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            width,
            height,
            SDL_WINDOW_SHOWN);

        if (!window) {
            std::cerr << "Failed to create SDL Window" << std::endl;
        }

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (!renderer) {
            std::cerr << "Failed to create SDL Renderer" << std::endl;
        }
    }

    Window::~Window() {
        if (renderer) SDL_DestroyRenderer(renderer);
        if (window) SDL_DestroyWindow(window);
    }

    void Window::clear() {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
    }

    void Window::present() {
        SDL_RenderPresent(renderer);
    }
} // namespace Engine