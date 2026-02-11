// Copyright 2025 Chrisfantasy
#pragma once
#include "Engine/Core/Application.hpp"
#include "Engine/Graphics/Sprite.hpp"
#include "Game/Logic/Scenes.hpp"

class Game : public Engine::Application {
public:
    Game();
    virtual ~Game();

    virtual bool create() override;
    virtual void update(float deltaTime) override;
    virtual void render() override;
    virtual void quit() override;

    void move_state(std::unique_ptr<TR::Scene> newState);

private:
    // Game-specific data and methods

    std::unique_ptr<TR::Scene> _currScene;
};

