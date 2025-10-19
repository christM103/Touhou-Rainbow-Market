#pragma once
#include <SDL2/SDL.h>

namespace Engine {
    class Window {
    public:
        Window(const char* title, int width, int height);
        ~Window();

        /// @brief Clears the window with a black color.
        void clear();
        
        /// @brief Presents the rendered content to the window.
        void present();

        /// @brief Gets the width of the window.
        /// @return Width of the window
        int getWidth() const { return width; }

        /// @brief Gets the height of the window.
        /// @return Height of the window
        int getHeight() const { return height; }

        /// @brief Gets the SDL_Renderer associated with the window.
        /// @return Pointer to the SDL_Renderer
        SDL_Renderer* getRenderer() const { return renderer; }

        /// @brief Gets the SDL_Window associated with the window.
        /// @return Pointer to the SDL_Window
        SDL_Window* getWindow() const { return window; }

    private:
        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;
        int width;
        int height;
    };
} // namespace Engine