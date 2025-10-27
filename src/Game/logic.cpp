// Copyright 2025 chrisfantasy

#include "Game/logic.hpp"
#include <chrono>

#include "Engine/Graphics/AssetManager.hpp"


using namespace std::chrono_literals;

typedef std::chrono::steady_clock::time_point current_time;
typedef std::chrono::seconds seconds;
typedef std::chrono::duration<double> timer;

namespace TR {

// Timer Functions

Timer::Timer(seconds new_dur) {
    _start = std::chrono::steady_clock::now();
    _dur = new_dur;
    _curr_left = _dur;
}

timer Timer::time_left() {
    _curr_left = _dur - (std::chrono::steady_clock::now() - _start);
    return _curr_left;
}

void Timer::timer_reset(seconds new_dur) {
    *this = Timer(new_dur);
}


Game_States::Game_States() {}
Game_States::~Game_States() {}


void Game_States::update(float deltaTime) {}

void Game_States::move_state(std::unique_ptr<Game_States> newState) {}

Char_Select::Char_Select() {}

Char_Select::~Char_Select() {}

bool Char_Select::create(SDL_Renderer* renderer, Engine::Engine* gEngine) {
    gEngine->getAssetManager()->loadTexture("assets/gfx/sprites/Char_Select/Placeholder_CharS_BG.png", "BGO", renderer);
    _sprite_set.insert({ "background",
        std::make_unique<Engine::Sprite>(gEngine->getAssetManager()->getTexture("BGO"), 800, 600) });
    return true;
}

void Char_Select::update(float deltaTime) {}

void Char_Select::render(SDL_Renderer* renderer) {
    _sprite_set["background"]->draw(renderer, Engine::Vector2i(0, 0));
}

Market_Game::Market_Game() {}

Market_Game::Market_Game(std::vector<std::shared_ptr<TR::Player_Data>> players) {}

Market_Game::~Market_Game() {}

bool Market_Game::create(SDL_Renderer* renderer, Engine::Engine* gEngine) {
    gEngine->getAssetManager()->loadTexture("assets/gfx/sprites/Market_Game/Placeholder_Game_BGLand.png", "BGO", renderer);
    _sprite_set.insert({ "background",
        std::make_unique<Engine::Sprite>(gEngine->getAssetManager()->getTexture("BGO"), 800, 600) });
    return true;
}

void Market_Game::update(float deltaTime) {}

void Market_Game::render(SDL_Renderer* renderer) {
    _sprite_set["background"]->draw(renderer, Engine::Vector2i(0, 0));
}

}  // namespace TR
