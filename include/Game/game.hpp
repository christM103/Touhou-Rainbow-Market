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
    Player_Set _player_set;
    int _beat{ 0 };
    std::unordered_map<SDL_Scancode, bool> _input_pressed{ 
        {SDL_SCANCODE_Q, false }, {SDL_SCANCODE_W, false }, {SDL_SCANCODE_Z, false }, };
};

