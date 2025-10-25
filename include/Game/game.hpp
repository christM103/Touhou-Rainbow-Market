// Copyright 2025 Chrisfantasy
#pragma once
#include "Engine/Core/Application.hpp"
#include "Engine/Graphics/Sprite.hpp"
#include "Game/mechanics.hpp"

class Game : public Engine::Application {
public:
    Game();
    virtual ~Game();

    virtual bool create() override;
    virtual void update(float deltaTime) override;
    virtual void render() override;
    virtual void quit() override;


    void terminalTest();
    void timerTest();
    void characterSelect(TR::Player_Data& Player_1);
    void marketTransaction(TR::Player_Data& Player_1);

private:
    // Game-specific data and methods
    Engine::Sprite* playerSprite = nullptr;
};
