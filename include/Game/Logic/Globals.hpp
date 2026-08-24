#pragma once

#include <SDL2/SDL.h>
#include <yaml-cpp/yaml.h>
#include "Engine/Core/Engine.hpp"
#include "Game/Logic/Player.hpp"
#include "Game/Objects/Components/CommonComponents.hpp"
#include "Game/Objects/Components/MarketGameComponents.hpp"

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
    TR::TurnsComponent* gTurns;

	// Global game data
	int gSize = 1;
    bool gCMD = true;

    // Scene specific data
    const std::string GFX_FOLDER = "assets/gfx/sprites/";
    const std::string TEXT_FOLDER = "assets/text/";
    YAML::Node gYAML;
    YAML::Node gMarket;
	
};

extern GlobalGameState gState;