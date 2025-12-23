#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Engine/Math/Vector2.hpp"

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

        /// @brief Draws the sprite using its stored current position.
        /// @param renderer SDL_Renderer to draw the sprite on
        void draw(SDL_Renderer* renderer);

        /// @brief Draws the sprite at the specified position.
        /// @param renderer SDL_Renderer to draw the sprite on
        /// @param x x position
        /// @param y y position
        /// @param crop The area that actually gets rendered on screen
        void drawCrop(SDL_Renderer* renderer, const Vector2i pos, const Vector2i size, const SDL_Rect& crop);

        /// @brief Swaps the pre-existing texture with a different texture
        /// @param tex The texture that will be swapped
        /// @param x Width of the new texture
        /// @param y Height of the new texture
        void swapTexture(SDL_Texture* tex, int x, int y);

        /// @brief Updates the internal position of the object based on velocity and acceleration.
        void movement();

        /// @brief Gets the width of the sprite.
        /// @return Width of the sprite
        int getWidth() const { return width; }

        /// @brief Gets the height of the sprite.
        /// @return Height of the sprite
        int getHeight() const { return height; }

        /// @brief Gets the X Position of the sprite.
        /// @return X Position of the sprite
        float getXPos() const { return pos.x; }

        /// @brief Gets the Y Position of the sprite.
        /// @return Y Position of the sprite
        float getYPos() const { return pos.y; }

        /// @brief Gets the X Velocity of the sprite.
        /// @return X Velocity of the sprite
        float getXVel() const { return vel.x; }

        /// @brief Gets the Y Velocity of the sprite.
        /// @return Y Velocity of the sprite
        float getYVel() const { return vel.y; }

        /// @brief Gets the X Acceleration of the sprite.
        /// @return X Acceleration of the sprite
        float getXAccel() const { return accel.x; }

        /// @brief Gets the Y Acceleration of the sprite.
        /// @return Y Acceleration of the sprite
        float getYAccel() const { return accel.y; }

        /// @brief Gets the angle of the sprite.
        /// @return Angle of the sprite
        int getAngle() const { return angle; }

        /// @brief Gets the alpha value of the sprite.
        /// @return Alpha value of the sprite
        int getAlpha() const { return alpha; }

        /// @brief Gets the flip value of the sprite.
        /// @return Flip value of the sprite
        int getFlip() const { return flip; }

        /// @brief Sets the width of the sprite.
        /// @param Width of the sprite
        void setWidth(float w) { width = w; }

        /// @brief Sets the height of the sprite.
        /// @param Height of the sprite
        void setHeight(float h) { height = h; }

        /// @brief Sets the X Position of the sprite.
        /// @param X Position of the sprite
        void setXPos(float x) { pos.x = x; }

        /// @brief Sets the Y Position of the sprite.
        /// @param Y Position of the sprite
        void setYPos(float y) { pos.y = y; }

        /// @brief Sets the X Velocity of the sprite.
        /// @param X Velocity of the sprite
        void setXVel(float x) { vel.x = x; }

        /// @brief Sets the Y Velocity of the sprite.
        /// @param Y Velocity of the sprite
        void setYVel(float y) { vel.y = y; }

        /// @brief Sets the X Acceleration of the sprite.
        /// @param X Acceleration of the sprite
        void setXAccel(float x) { accel.x = x; }

        /// @brief Sets the Y Acceleration of the sprite.
        /// @param Y Acceleration of the sprite
        void setYAccel(float y) { accel.y = y; }

        /// @brief Sets the angle of the sprite
        /// @param Updated angle value
        void setAngle(int a) { angle = a % 360; }

        /// @brief Sets the alpha value of the sprite
        /// @param Updated alpha value (Between 0 and 1)
        void setAlpha(float a);

    private:
        SDL_Texture* texture;
        float width, height;
        Vector2f pos{ 0,0 }, vel{ 0,0 }, accel{ 0,0 };
        int angle{ 0 };
        uint8_t alpha { 255 };
        SDL_RendererFlip flip{ SDL_FLIP_NONE };
    };
} // namespace Engine