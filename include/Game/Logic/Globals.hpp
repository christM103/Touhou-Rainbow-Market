#pragma once

#include <SDL2/SDL.h>
#include "Engine/Core/Engine.hpp"
#include "Game/Logic/Player.hpp"
#include "Game/Objects/Components/CommonComponents.hpp"

struct GlobalGameState
{
    // Global pointers to engine managers
    Engine::ECSManager* gECS;
    Engine::AssetManager* gAssets;
    Engine::Window* gWindow;
    SDL_Renderer* gRenderer;

	// Global pointers to commonly used components
    Engine::CameraComponent* gCamera;
    Engine::InputComponent* gInput;
    Engine::MouseComponent* gMouse;
    TR::PlayerComponent* gPlayer;

	// Global game data
	int gSize = 1;

    // Scene specific data
    const std::string GFX_FOLDER = "assets/gfx/sprites/";
	
};

extern GlobalGameState gState;