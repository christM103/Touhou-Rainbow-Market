#include "Engine/Graphics/Sprite.hpp"
#include "engine/Math/Vector2.hpp"

Engine::Sprite::Sprite(SDL_Texture* texture, int width, int height)
 : _texture(texture) {
    _size.x = static_cast<float>(width);
    _size.y = static_cast<float>(height);
}

Engine::Sprite::~Sprite() {
    if (_texture) {
        SDL_DestroyTexture(_texture);
    }
}

void Engine::Sprite::draw(SDL_Renderer* renderer, int x, int y) {
    if (renderer && _texture) {
        SDL_Rect dest = { x, y, static_cast<int>(_size.x), static_cast<int>(_size.y) };
        SDL_RenderCopyEx(renderer, _texture, nullptr, &dest, _angle, nullptr, _flip);
    }
}

void Engine::Sprite::draw(SDL_Renderer* renderer, const Vector2i& position) {
    draw(renderer, position.x, position.y);
}

void Engine::Sprite::draw(SDL_Renderer* renderer) {
    draw(renderer, static_cast<int>(_pos.x), static_cast<int>(_pos.y));
    movement();
}

void Engine::Sprite::drawCrop(SDL_Renderer* renderer, const Vector2i pos, const Vector2i size, const SDL_Rect& crop) {
    if (renderer && _texture) {
        SDL_Rect dest = { static_cast<int>(pos.x), static_cast<int>(pos.y), 
            static_cast<int>(size.x), static_cast<int>(size.y) };
        SDL_RenderCopyEx(renderer, _texture, &crop, &dest, _angle, nullptr, _flip);
    }
}

void Engine::Sprite::swapTexture(SDL_Texture* tex, int x, int y) {
    std::swap(_texture, tex);
    _size.x = static_cast<float>(x);
    _size.y = static_cast<float>(y);
}

void Engine::Sprite::movement() {
    _pos += _vel + (_accel * .5);
}

void Engine::Sprite::setAlpha(float a) {
    if (a <= 255 && a >= 0) {
        _alpha = static_cast<uint8_t>(a);
    }
    SDL_SetTextureAlphaMod(_texture, _alpha);
}