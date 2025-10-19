#pragma once
#include <SDL2/SDL.h>

#include <unordered_map>
#include <string>

namespace Engine {
    class AssetManager {
    public:
        AssetManager();
        ~AssetManager();

        /// @brief Load a texture from a file.
        /// @param filePath path to the texture file
        /// @param assetName name to reference the asset
        /// @param renderer SDL_Renderer to create the texture
        /// @return True if the texture was loaded successfully, false otherwise
        bool loadTexture(const char* filePath, const char* assetName, SDL_Renderer* renderer);
        
        /// @brief Get a texture by its asset name.
        /// @param assetName name of the asset
        /// @return Pointer to the SDL_Texture, or nullptr if not found
        SDL_Texture* getTexture(const char* assetName);

        /// @brief Clear all loaded assets.
        void clear();
    
    private:
        std::unordered_map<std::string, SDL_Texture*> textures;
    };
} // namespace Engine