#include "Engine/Graphics/Sprite.hpp"
#include "engine/Math/Vector2.hpp"

Engine::Sprite::Sprite(std::string texture, int width, int height)
 : _textureID(texture), _dest_rect(Recti(0,0,width,height)) {}

Engine::Sprite::Sprite(int width, int height)
    : _dest_rect(Recti(0, 0, width, height)) {}

Engine::Sprite::~Sprite() = default;

void Engine::Sprite::draw(SDL_Renderer* renderer, const AssetManager* manager, int x, int y) {
    SDL_Texture* texture = manager->getTexture(_textureID.c_str());

    if (renderer && texture) {
        // Location initilization
        SDL_Rect dest = { x, y, _dest_rect.size.x, _dest_rect.size.y };
        SDL_Rect crop = { _src_rect.position.x, _src_rect.position.y, _src_rect.size.x, _src_rect.size.y };

        // Flip initilization
        SDL_RendererFlip flip = SDL_FLIP_NONE;
        if (_flip & Flip_Horizontal) {
            flip = static_cast<SDL_RendererFlip>(static_cast<Uint32>(flip) ^ static_cast<Uint32>(SDL_FLIP_HORIZONTAL));
        }
        if (_flip & Flip_Vertical) {
            flip = static_cast<SDL_RendererFlip>(static_cast<Uint32>(flip) ^ static_cast<Uint32>(SDL_FLIP_VERTICAL));
        }

        // Set alpha values
        SDL_SetTextureAlphaMod(texture, _alpha);

        // Drawing the loaded texture
        int rc = SDL_RenderCopyEx(renderer, texture, &crop, &dest, _angle, nullptr, flip);
        if (rc != 0) {
            SDL_LogError(SDL_LOG_CATEGORY_RENDER, "SDL_RenderCopyEx (drawCrop) failed: %s (dest=%d,%d,%d,%d src=%d,%d,%d,%d)",
                SDL_GetError(),
                dest.x, dest.y, dest.w, dest.h,
                crop.x, crop.y, crop.w, crop.h);
        }
    }
}

void Engine::Sprite::draw(SDL_Renderer* renderer, const AssetManager* manager, const Vector2i& position) {
    draw(renderer, manager, position.x, position.y);
}

void Engine::Sprite::draw(SDL_Renderer* renderer, const AssetManager* manager) {
    draw(renderer, manager, _dest_rect.position.x, _dest_rect.position.y);
}


void Engine::Sprite::draw_center(SDL_Renderer* renderer, const AssetManager* manager) {
    draw(renderer, manager, _dest_rect.position - (_dest_rect.size / 2));
}


void Engine::Sprite::swapTexture(std::string tex, int x, int y) {
    _textureID = tex;
    _dest_rect.size.x = x;
    _dest_rect.size.y = y;
}

void Engine::Sprite::setAlpha(float a) {
    if (a <= 255 && a >= 0) {
        _alpha = static_cast<uint8_t>(a);
    }
    
}