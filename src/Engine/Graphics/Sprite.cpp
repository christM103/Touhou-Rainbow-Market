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
    movement();
    draw(renderer, pos.x, pos.y);
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