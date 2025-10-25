// Copyright 2025 Chrisfantasy
#include <iostream>
#include <SDL2/SDL.h>
#include "Game/game.hpp"
#include "Engine/Core/Engine.hpp"
#include "Engine/Graphics/AssetManager.hpp"
#include "Engine/Graphics/Sprite.hpp"

extern Engine::Engine* gEngine;

Game::Game() {
    // Constructor implementation
}

Game::~Game() {
    // Destructor implementation
}

bool Game::create() {
    // Initialization code for the game
    SDL_Renderer* renderer = gEngine->getWindow()->getRenderer();
    gEngine->getAssetManager()->loadTexture("assets/player.png", "player", renderer);
    playerSprite = new Engine::Sprite(gEngine->getAssetManager()->getTexture("player"), 64, 64);
    //terminalTest();
    return true;
}

void Game::update(float deltaTime) {
    // Update logic for the game
}

void Game::render() {
    // Get the renderer from the engine's window
    SDL_Renderer* renderer = gEngine->getWindow()->getRenderer();

    // Example rendering code
    playerSprite->draw(renderer, Engine::Vector2i(300, 100));
}
void Game::quit() {
    // Shutdown code for the game
    delete playerSprite;
}


void Game::terminalTest() {
    
    // Testing the timer of the program

    timerTest();
    
    // Testing the character selection and player initilization

    TR::Player_Data current_player = TR::Player_Data();

    characterSelect(current_player);
    
    current_player.showDesc();

    //std::unique_ptr<TR::Land> nPC_1(new TR::Land());

    // Testing land management for the player

    marketTransaction(current_player);

}

void Game::timerTest() {
    TR::Timer test_timer(2s);
    auto curr_time = test_timer.time_left();
    std::cout << "Welcome to the Touhou Rainbow Market Game! (Terminal Edition)";
    std::cout << "\nBut before I do... \n";

    test_timer.timer_reset(2s);
    curr_time = test_timer.time_left();

    while (curr_time >= 0s) {
        std::cout << "Let's start by testing the timer: " << curr_time.count();
        curr_time = test_timer.time_left();
        std::cout << "\r";
    }
}

void Game::characterSelect(TR::Player_Data& Player_1) {
    int char_index;

    std::cout << "\nSelect your character \n{Reimu} {Marisa}\n(Type 1 or 2)\n";
    std::cin >> char_index;

    if (char_index == 1) {
        Player_1 = TR::Player_Reimu(Player_1.getPlayerID(), 1);
    }
    else if (char_index == 2) {
        Player_1 = TR::Player_Marisa(Player_1.getPlayerID(), 1);
    }
    else {
        Player_1 = TR::Player_Null(Player_1.getPlayerID(), 1);
    }
    std::cout << "Ok cool ";

}

void Game::marketTransaction(TR::Player_Data& Player_1) {
    int land_index;
    std::string market_confirm;

    std::cout << Player_1.getPathway() << "\n";
    std::cout << "Here is your current lot for Player 1: \n\n";

    std::cout << Player_1.getLand()->getMarketList();
    std::cout << "\nWould you like to get this cool bug market? (y/n)\n";

    std::cin >> market_confirm;
    if (market_confirm == "y") {
        std::cout << "Where do you want to put it? (lot 1 - 5) \n";
        std::cin >> land_index;
        Player_1.getLand()->setLand(land_index - 1, TR::Wriggle());
    }

    std::cout << Player_1.getLand()->getMarketList();
}
