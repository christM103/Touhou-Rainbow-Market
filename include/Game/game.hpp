// Copyright 2025 Chrisfantasy
#pragma once
#include "Engine/Core/Application.hpp"
#include "Engine/Graphics/Sprite.hpp"
#include "Game/logic.hpp"

class Game : public Engine::Application {
public:
    Game();
    virtual ~Game();

    virtual bool create() override;
    virtual void update(float deltaTime) override;
    virtual void render() override;
    virtual void quit() override;

    void move_state(std::unique_ptr<TR::Scene> newState);

    void terminalTest();
    void timerTest();
    void characterSelect(TR::Player_Data& Player_1);
    void marketTransaction(TR::Player_Data& Player_1);

private:
    // Game-specific data and methods

    std::unique_ptr<TR::Scene> _game_state;
    Sprite_Map _sprite_set;
    Player_Set _player_set;
    int _beat{ 0 };
    std::unordered_map<SDL_Scancode, bool> _input_pressed{ 
        {SDL_SCANCODE_Q, false }, {SDL_SCANCODE_W, false }, {SDL_SCANCODE_Z, false }, };
    Engine::Sprite* playerSprite = nullptr;
};

/*

*/