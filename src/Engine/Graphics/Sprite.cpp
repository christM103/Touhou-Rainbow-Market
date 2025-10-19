#include "Engine/Graphics/Sprite.hpp"

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
        SDL_RenderCopy(renderer, texture, nullptr, &dest);
    }
}