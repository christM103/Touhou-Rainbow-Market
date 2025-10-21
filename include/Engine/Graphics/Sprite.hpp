#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Engine/Math/Vector2D.hpp"

namespace Engine {
    class Sprite {
    public:
        Sprite(SDL_Texture* texture, int width, int height);
        ~Sprite();

        /// @brief Draws the sprite at the specified position.
        /// @param renderer SDL_Renderer to draw the sprite on
        /// @param x x position
        /// @param y y position
        void draw(SDL_Renderer* renderer, int x, int y);

        /// @brief Draws the sprite at the specified position.
        /// @param renderer SDL_Renderer to draw the sprite on
        /// @param position Position as a Vector2i
        void draw(SDL_Renderer* renderer, const Vector2i& position);

        /// @brief Gets the width of the sprite.
        /// @return Width of the sprite
        int getWidth() const { return width; }

        /// @brief Gets the height of the sprite.
        /// @return Height of the sprite
        int getHeight() const { return height; }

    private:
        SDL_Texture* texture;
        int width;
        int height;
    };
} // namespace Engine