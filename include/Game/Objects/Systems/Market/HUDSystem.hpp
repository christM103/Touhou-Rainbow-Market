#pragma once

#include "Engine/ECS/System/BaseSystem.hpp"

#include "Game/Objects/Components/Common/PlayerComponent.hpp"

namespace TR {
	class HUDSystem {
	public:
		HUDSystem() = default;
		~HUDSystem() = default;

		void initHUD(Engine::ComponentManager* componentManager, Engine::Window* windowManager, Engine::AssetManager* assetManagerr);
		void updateEntites(const Engine::EntityManager* entityManager, Engine::ComponentManager* componentManager);
		void updateData(Engine::ComponentManager* componentManager, Engine::Window* windowManager);

		// Overloaded functions

		void create(const Engine::SystemContext& ctx);

		void update(const Engine::SystemContext& ctx);

		void render(const Engine::SystemContext& ctx);

		void quit(const Engine::SystemContext& ctx);

	private:
	};
}