#pragma once

namespace Engine {
    class Application {
    public:
        Application() = default;
        virtual ~Application() = default;

        /// @brief Initialize the application
        /// @return True if initialization is successful, false otherwise
        virtual bool create() = 0;

        /// @brief Update the application state
        /// @param deltaTime Time elapsed since the last frame
        virtual void update(float deltaTime) = 0;

        /// @brief Render the application
        virtual void render() = 0;

        /// @brief Clean up resources before quitting the application
        virtual void quit() = 0;
    };
} // namespace Engine