#include "Engine/Graphics/Sprite.hpp"
#include "engine/Math/Vector2.hpp"

Engine::Sprite::Sprite(SDL_Texture* texture, int width, int height)
 : texture(texture), width(width), height(height) {}

Engine::Sprite::~Sprite() {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}

void Engine::Sprite::draw(SDL_Renderer* renderer, int x, int y) {
    if (renderer && texture) {
        SDL_Rect dest = { x, y, width, height };
        SDL_RenderCopyEx(renderer, texture, nullptr, &dest, angle, nullptr, flip);
    }
}

void Engine::Sprite::draw(SDL_Renderer* renderer, const Vector2i& position) {
    draw(renderer, position.x, position.y);
}

void Engine::Sprite::draw(SDL_Renderer* renderer) {
    draw(renderer, pos.x, pos.y);
    movement();
}

void Engine::Sprite::draw(SDL_Renderer* renderer, const Vector2i pos, const Vector2i size, const SDL_Rect& crop) {
    if (renderer && texture) {
        SDL_Rect dest = { pos.x, pos.y, size.x, size.y };
        SDL_RenderCopyEx(renderer, texture, &crop, &dest, angle, nullptr, flip);
    }
}

void Engine::Sprite::swapTexture(SDL_Texture* tex, int x, int y) {
    std::swap(texture, tex);
    width = x;
    height = y;
}

void Engine::Sprite::movement() {
    pos.x += vel.x + .5 * accel.x;
    pos.y += vel.y + .5 * accel.y;
}

void Engine::Sprite::setAlpha(float a) {
    if (a <= 255 && a >= 0) {
        alpha = a;
    }
    SDL_SetTextureAlphaMod(texture, alpha);
}