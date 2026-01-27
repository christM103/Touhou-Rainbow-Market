#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Engine/Graphics/AssetManager.hpp"

namespace Engine {
    AssetManager::AssetManager() {}

    AssetManager::~AssetManager() {
        clear();
    }

    bool AssetManager::loadTexture(const char* filePath, const char* assetName, SDL_Renderer* renderer) {
        SDL_Surface* surface = IMG_Load(filePath);
        if (!surface) {
            return false;
        }

        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);

        if (!texture) {
            return false;
        }

        textures[assetName] = texture;
        return true;
    }

    bool AssetManager::storeTexture(SDL_Texture* texture, const char* assetName, SDL_Renderer* renderer) {

        if (!texture) {
            return false;
        }

        textures[assetName] = texture;
        return true;
    }

    SDL_Texture* AssetManager::getTexture(const char* assetName) const {
        auto it = textures.find(assetName);
        if (it != textures.end()) {
            return it->second;
        }
        return nullptr;
    }

    bool AssetManager::destroyTexture(const char* assetName) {
        auto tex = textures.find(assetName);
        SDL_DestroyTexture(tex->second);
        textures.erase(tex);

        return true;
    }

    void AssetManager::clear() {
        for (auto& pair : textures) {
            SDL_DestroyTexture(pair.second);
        }
        textures.clear();
    }
} // namespace Engine