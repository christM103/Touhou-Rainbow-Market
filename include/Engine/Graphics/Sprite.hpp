#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Engine/Math/Rect.hpp"
#include "Engine/Math/Vector2.hpp"

namespace Engine {
    class Sprite {
    public:
        /// -- Constructor & Destructor -- ///

        Sprite() = default;
        Sprite(int width, int height);
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

        /// @brief Draws the sprite using its stored current center position.
        /// @param renderer SDL_Renderer to draw the sprite on
        void draw_center(SDL_Renderer* renderer);

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


        /// -- Accessor & Mutator Functions -- ///
        

        // Accessors

        /// @brief Gets the X Position of the sprite.
        /// @return X Position of the sprite
        int getX() const { return _dest_rect.position.x; }

        /// @brief Gets the Y Position of the sprite.
        /// @return Y Position of the sprite
        int getY() const { return _dest_rect.position.y; }

        /// @brief Gets the width of the sprite.
        /// @return Width of the sprite
        int getWidth() const { return _dest_rect.size.x; }

        /// @brief Gets the height of the sprite.
        /// @return Height of the sprite
        int getHeight() const { return _dest_rect.size.y; }


        /// @brief Gets the X Position of the crop.
        /// @return X Position of the crop
        int getXCrop() const { return _src_rect.position.x; }

        /// @brief Gets the Y Position of the crop.
        /// @return Y Position of the crop
        int getYCrop() const { return _src_rect.position.y; }

        /// @brief Gets the width of the crop.
        /// @return Width of the crop
        int getWidthCrop() const { return _src_rect.size.x; }

        /// @brief Gets the height of the crop.
        /// @return Height of the crop
        int getHeightCrop() const { return _src_rect.size.y; }


        /// @brief Gets the position of the sprite.
        /// @return Position of the sprite
        Vector2i getPosition() const { return _dest_rect.position; }

        /// @brief Gets the Y Position of the sprite.
        /// @return Y Position of the sprite
        Vector2i getSize() const { return _dest_rect.size; }

        /// @brief Gets the position of the crop.
        /// @return Position of the crop
        Vector2i getPositionCrop() const { return _src_rect.position; }

        /// @brief Gets the Y Position of the crop.
        /// @return Y Position of the crop
        Vector2i getSizeCrop() const { return _src_rect.size; }


        /// @brief Gets the destination render space (render) of the sprite.
        /// @return Position of the sprite
        Recti getDestinationRect() const { return _dest_rect; }

        /// @brief Gets the source render space (crop) of the crop.
        /// @return Position of the crop
        Recti getSourceRect() const { return _src_rect; }


        /// @brief Gets the scale of the sprite.
        /// @return scale of the sprite
        Vector2f getScale() const { return _scale; }

        /// @brief Gets the angle of the sprite.
        /// @return Angle of the sprite
        float getAngle() const { return _angle; }

        /// @brief Gets the flip value of the sprite.
        /// @return Flip value of the sprite
        SDL_RendererFlip getFlip() const { return _flip; }


        /// @brief Gets the alpha value of the sprite.
        /// @return Alpha value of the sprite
        int getAlpha() const { return _alpha; }

        /// @brief Gets the active texture of the sprite.
        /// @return Texture value of the sprite
        SDL_Texture* getTexture() const { return _texture; }


        // Mutators

        /// @brief Sets the X Position of the sprite.
        /// @param X Position of the sprite
        void setX(int x) { _dest_rect.position.x = x; }

        /// @brief Sets the Y Position of the sprite.
        /// @param Y Position of the sprite
        void setY(int y) { _dest_rect.position.y = y; }

        /// @brief Sets the width of the sprite.
        /// @param Width of the sprite
        void setWidth(int w) { _dest_rect.size.x = w; setWidthCrop(w); }

        /// @brief Sets the height of the sprite.
        /// @param Height of the sprite
        void setHeight(int h) { _dest_rect.size.y = h; setHeightCrop(h); }


        /// @brief Sets the X Position of the crop.
        /// @param X Position of the crop
        void setXCrop(int x) { _src_rect.position.x = x; }

        /// @brief Sets the Y Position of the crop.
        /// @param Y Position of the crop
        void setYCrop(int y) { _src_rect.position.y = y; }

        /// @brief Sets the width of the crop.
        /// @param Width of the crop
        void setWidthCrop(int w) { _src_rect.size.x = w; }

        /// @brief Sets the height of the crop.
        /// @param Height of the crop
        void setHeightCrop(int h) { _src_rect.size.y = h; }


        /// @brief Sets the position of the sprite.
        /// @param A Vector2i of the size of the sprite
        void setPos(Vector2i pos) { _dest_rect.position = pos; }

        /// @brief Sets the size of the sprite.
        /// @param A Vector2i of the size of the sprite
        void setSize(Vector2i size) { _dest_rect.position = size; setSizeCrop(size); }
        
        /// @brief Sets the position of the crop.
        /// @param A Vector2i of the size of the crop
        void setPosCrop(Vector2i pos) { _src_rect.position = pos; }

        /// @brief Sets the size of the crop.
        /// @param A Vector2i of the size of the crop
        void setSizeCrop(Vector2i size) { _src_rect.position = size; }
        

        /// @brief Sets the size of the sprite.
        /// @param A Vector2i of the size of the sprite
        void setDestinationRect(Recti rect) { _dest_rect = rect; }

        /// @brief Sets the position of the crop.
        /// @param A Vector2i of the size of the crop
        void setSourceRect(Recti rect) { _src_rect = rect; }


        /// @brief Sets the scale of the sprite.
        /// @param scale A float for the scale of the sprite
        void setScale(Vector2f scale) { _scale = scale; }

        /// @brief Sets the alpha value of the sprite
        /// @param Updated alpha value (Between 0 and 1)
        void setAlpha(float a);

        /// @brief Sets the angle of the sprite
        /// @param Updated angle value
        void setAngle(float a) { _angle = a; }

    protected:
        SDL_Texture* _texture{ nullptr };
        Recti _dest_rect{ 0,0,0,0 }, _src_rect{ 0,0,0,0 };
        Vector2f _scale{ 0.0,0.0 };
        float _angle{ 0.0 };
        uint8_t _alpha { 255 };
        SDL_RendererFlip _flip{ SDL_FLIP_NONE };
    };
} // namespace Engine