#pragma once

#include "Engine/ECS/System/BaseSystem.hpp"
#include "Engine/Time/Timer.hpp"
#include "Game/Objects/Components/Market/TurnComponent.hpp"

namespace TR {
	class TurnSystem {
	public:
		TurnSystem() = default;
		~TurnSystem();

		void initTurns(Engine::ComponentManager* componentManager);
		void initRender(Engine::ComponentManager* componentManager, Engine::Window* windowManager, Engine::AssetManager* assetManager);
		void updateEntites(Engine::ComponentManager* componentManager, Engine::Window* windowManager, Engine::AssetManager* assetManager);
		void updateTurns(Engine::ComponentManager* componentManager);
		void updateRender(Engine::ComponentManager* componentManager, Engine::Window* windowManager);

		// Overloaded functions

		void create(const Engine::SystemContext& ctx);

		void update(const Engine::SystemContext& ctx);

		void render(const Engine::SystemContext& ctx);

		void quit(const Engine::SystemContext& ctx);
		
	private:
		std::pair<const Engine::Entity*, TurnsComponent*> active_entity;
		std::unique_ptr<Engine::Timer> timer;
	};
}