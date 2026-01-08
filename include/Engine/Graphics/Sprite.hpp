#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Engine/Math/Vector2.hpp"

namespace Engine {
    class Sprite {
    public:
        /// -- Constructor & Destructor -- ///


        Sprite(SDL_Texture* texture, int width, int height);
        ~Sprite();


        /// -- Helper Functions -- ///


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
        /// @param position Vector2i for the sprite's x and y position
        /// @param size Vector2i for the sprite's width and height
        /// @param crop The area that actually gets rendered on screen
        void drawCrop(SDL_Renderer* renderer, const Vector2i pos, const Vector2i size, const SDL_Rect& crop);

        /// @brief Swaps the pre-existing texture with a different texture
        /// @param tex The texture that will be swapped
        /// @param x Width of the new texture
        /// @param y Height of the new texture
        void swapTexture(SDL_Texture* tex, int x, int y);

        /// @brief Updates the internal position of the object based on velocity and acceleration.
        void movement();


        /// -- Accessor & Mutator Functions -- ///
        

        // Position Accessor & Mutators

        /// @brief Gets the X Position of the sprite.
        /// @return X Position of the sprite
        int getX() const { return static_cast<int>(_pos.x); }

        /// @brief Gets the Y Position of the sprite.
        /// @return Y Position of the sprite
        int getY() const { return static_cast<int>(_pos.y); }

        /// @brief Gets the position of the sprite.
        /// @return Position of the sprite
        Vector2f getPosition() const { return _pos; }

        /// @brief Gets the angle of the sprite.
        /// @return Angle of the sprite
        int getAngle() const { return _angle; }

        /// @brief Gets the flip value of the sprite.
        /// @return Flip value of the sprite
        SDL_RendererFlip getFlip() const { return _flip; }

        /// @brief Sets the X Position of the sprite.
        /// @param X Position of the sprite
        void setX(int x) { _pos.x = static_cast<float>(x); }

        /// @brief Sets the Y Position of the sprite.
        /// @param Y Position of the sprite
        void setY(int y) { _pos.y = static_cast<float>(y); }

        /// @brief Sets the position of the sprite.
        /// @param A Vector2i of the size of the sprite
        void setPos(Vector2f pos) { _pos = pos; }

        /// @brief Sets the position using a scalar.
        /// @param scale A float for the scalar
        void setPosScale(float scale) { _pos *= scale; }

        /// @brief Sets the angle of the sprite
        /// @param Updated angle value
        void setAngle(int a) { _angle = a % 360; }


        // Size Accessor & Mutators

        /// @brief Gets the width of the sprite.
        /// @return Width of the sprite
        int getWidth() const { return static_cast<int>(_size.x); }

        /// @brief Gets the height of the sprite.
        /// @return Height of the sprite
        int getHeight() const { return static_cast<int>(_size.y); }

        /// @brief Gets the Y Position of the sprite.
        /// @return Y Position of the sprite
        Vector2f getSize() const { return _size; }

        /// @brief Sets the width of the sprite.
        /// @param Width of the sprite
        void setWidth(int w) { _size.x = static_cast<float>(w); }

        /// @brief Sets the height of the sprite.
        /// @param Height of the sprite
        void setHeight(int h) { _size.y = static_cast<float>(h); }

        /// @brief Sets the size of the sprite.
        /// @param A Vector2i of the size of the sprite
        void setSize(Vector2f size) { _size = size; }

        /// @brief Changes the size using a scalar.
        /// @param scale A float for the scalar
        void setSizeScale(float scale) { _size *= scale; }


        // Kinematics Accessor & Mutators

        /// @brief Gets the X Velocity of the sprite.
        /// @return X Velocity of the sprite
        float getXVel() const { return _vel.x; }

        /// @brief Gets the Y Velocity of the sprite.
        /// @return Y Velocity of the sprite
        float getYVel() const { return _vel.y; }

        /// @brief Gets the X Acceleration of the sprite.
        /// @return X Acceleration of the sprite
        float getXAccel() const { return _accel.x; }

        /// @brief Gets the Y Acceleration of the sprite.
        /// @return Y Acceleration of the sprite
        float getYAccel() const { return _accel.y; }

        /// @brief Sets the X Velocity of the sprite.
        /// @param X Velocity of the sprite
        void setXVel(float x) { _vel.x = x; }

        /// @brief Sets the Y Velocity of the sprite.
        /// @param Y Velocity of the sprite
        void setYVel(float y) { _vel.y = y; }

        /// @brief Sets the X Acceleration of the sprite.
        /// @param X Acceleration of the sprite
        void setXAccel(float x) { _accel.x = x; }

        /// @brief Sets the Y Acceleration of the sprite.
        /// @param Y Acceleration of the sprite
        void setYAccel(float y) { _accel.y = y; }


        // Color Accessor & Mutators

        /// @brief Gets the alpha value of the sprite.
        /// @return Alpha value of the sprite
        int getAlpha() const { return _alpha; }

        /// @brief Sets the alpha value of the sprite
        /// @param Updated alpha value (Between 0 and 1)
        void setAlpha(float a);

    private:
        SDL_Texture* _texture;
        Vector2f _pos{ 0.0,0.0 }, _size{ 0.0,0.0 }, _vel{ 0.0,0.0 }, _accel{ 0.0,0.0 };
        int _angle{ 0 };
        uint8_t _alpha { 255 };
        SDL_RendererFlip _flip{ SDL_FLIP_NONE };
    };
} // namespace Engine