// Copyright 2025 chrisfantasy

#include "Game/logic.hpp"
#include <chrono>

#include "Engine/Graphics/AssetManager.hpp"


using namespace std::chrono_literals;

typedef std::chrono::steady_clock::time_point current_time;
typedef std::chrono::seconds seconds;
typedef std::chrono::duration<double> timer;

namespace TR {

Scene::Scene() {
	_currState = SC_Null;
	_nextState = _currState;
}
Scene::~Scene() {}


void Scene::update(Engine::Engine* gEngine, Sprite_Map& sprite_set, Player_Set& player_set) {}


}  // namespace TR
