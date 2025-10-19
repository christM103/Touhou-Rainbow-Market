#pragma once

namespace Engine {
    class Application {
    public:
        Application() = default;
        virtual ~Application() = default;

        virtual bool create() = 0;
        virtual void update(float deltaTime) = 0;
        virtual void render() = 0;
        virtual void quit() = 0;
    };
} // namespace Engine