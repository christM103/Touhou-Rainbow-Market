#pragma once
#include <unordered_map>
#include <SDL2/SDL.h>
#include "Engine/Math/Vector2.hpp"

namespace Engine {
class Input {
public:
    Input();
    ~Input();

    // Poll for events and update key states
    void pollEvent();

    // Check if a key was pressed (transition from up to down)
    bool isKeyPressed(SDL_Scancode key) const;

    /// @brief Track the current position of the mouse on the screen
    /// @return The current mouse position
    Vector2i getMousePosition() const { return mousePosition; }

    /// @brief Check if the quit event has been requested.
    /// @return True if quit is requested, false otherwise.
    bool isQuitRequested() const { return quitRequested; }

private:
    std::unordered_map<SDL_Scancode, bool> keyStates;
    Vector2i mousePosition;
    bool quitRequested = false;
};
} // namespace Engine