#include "Engine/Input/Input.hpp"

namespace Engine {
    Input::Input() {
        // Constructor implementation
    }

    Input::~Input() {
        // Destructor implementation
    }

    void Input::pollEvent() {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYUP:
                    keyStates[event.key.keysym.scancode] = false;
                    break;
                case SDL_KEYDOWN:
                    keyStates[event.key.keysym.scancode] = true;
                    break;
                case SDL_MOUSEMOTION:
                    mousePosition = Vector2i(event.motion.x, event.motion.y);
                    break;
                case SDL_MOUSEBUTTONUP:
                    mouseStates[SDL_BUTTON(event.button.button)] = false;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    mouseStates[SDL_BUTTON(event.button.button)] = true;
                    break;
                case SDL_QUIT:
                    quitRequested = true;
                    break;
                default:
                    break;
            }
        }
    }

    bool Input::isKeyPressed(SDL_Scancode key) const {
        auto it = keyStates.find(key);
        if (it != keyStates.end()) {
            return it->second;
        }
        return false;
    }

    bool Input::isMouseClicked(int click) const {
        auto it = mouseStates.find(click);
        if (it != mouseStates.end()) {
            return it->second;
        }
        return false;
    }

} // namespace Engine