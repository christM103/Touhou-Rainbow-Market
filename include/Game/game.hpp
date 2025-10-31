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

    void move_state(std::unique_ptr<TR::Game_States> newState);

    void terminalTest();
    void timerTest();
    void characterSelect(TR::Player_Data& Player_1);
    void marketTransaction(TR::Player_Data& Player_1);

private:
    // Game-specific data and methods

    std::unique_ptr<TR::Game_States> _game_state;
    Sprite_Map _sprite_set;
    Player_Set _player_set;
    int _beat{ 0 };
    Engine::Sprite* playerSprite = nullptr;
};

/*

*/