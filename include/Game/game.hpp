// Copyright 2025 Chrisfantasy
#pragma once
#include "Engine/Core/Application.hpp"

class Game : public Engine::Application {
public:
    Game();
    virtual ~Game();

    virtual bool create() override;
    virtual void update(float deltaTime) override;
    virtual void render() override;
    virtual void quit() override;

private:
    // Game-specific data and methods
};
