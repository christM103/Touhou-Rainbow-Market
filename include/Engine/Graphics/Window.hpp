#pragma once
#include <SDL2/SDL.h>

namespace Engine {
    class Window {
    public:
        Window(const char* title, int width, int height);
        ~Window();

        void clear();
        void present();

        int getWidth() const { return width; }
        int getHeight() const { return height; }

        SDL_Renderer* getRenderer() const { return renderer; }
        SDL_Window* getWindow() const { return window; }

    private:
        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;
        int width;
        int height;
    };
} // namespace Engine