#pragma once
#include <memory>

#include <SDL2/SDL.h>
#include "Engine/Graphics/Window.hpp"
#include "Engine/Graphics/AssetManager.hpp"
#include "Engine/Input/Input.hpp"

namespace Engine {
    class Application;
    class Window;
    class Input;
    class AssetManager;

    class Engine {
    public:
        Engine();
        ~Engine();

        /// @brief Initialize the engine
        /// @param title The window title
        /// @param width The window width
        /// @param height The window height
        /// @return True if initialization is successful, false otherwise
        bool init(const char* title, int width, int height);

        /// @brief Run the engine main loop
        void run(Application* game);

        /// @brief Quit the engine and clean up resources
        void quit();

        /// @brief Get the Delta Time
        /// @return The time elapsed since the last frame
        float getDeltaTime() const { return deltaTime; }

        /// @brief Check if the engine is running
        /// @return True if the engine is running, false otherwise
        bool isRunning() const { return running; }

        /// @brief Gets the window associated with the engine.
        /// @return Pointer to the Window
        Window* getWindow() const { return window.get(); }

        /// @brief Gets the input handler associated with the engine.
        /// @return Pointer to the Input handler
        Input* getInput() const { return input.get(); }

        /// @brief Gets the asset manager associated with the engine.
        /// @return Pointer to the AssetManager
        AssetManager* getAssetManager() const { return assets.get(); }
    private:
        float deltaTime;
        bool running;
        Uint64 lastFrameTime;

        std::unique_ptr<Window> window;
        std::unique_ptr<Input> input;
        std::unique_ptr<AssetManager> assets;
        Application* Game = nullptr;
    };
} // namespace Engine