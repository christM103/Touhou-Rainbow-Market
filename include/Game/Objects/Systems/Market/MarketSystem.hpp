#pragma once

#include "Engine/ECS/System/BaseSystem.hpp"
#include "Game/Objects/Components/Common/PlayerComponent.hpp"
#include "Game/Objects/Components/Market/MarketComponent.hpp"

namespace TR {
	class MarketSystem {
	public:
		MarketSystem() = default;
		~MarketSystem() = default;

		void marketInit(Engine::ComponentManager* componentManager);
		void renderInit(Engine::ComponentManager* componentManager, Engine::Window* windowManager, Engine::AssetManager* assetManager);

		void updateEntities(Engine::EntityManager* entityManager, Engine::ComponentManager* componentManager, Engine::Window* windowManager, Engine::AssetManager* assetManager);

		void marketUpdate(Engine::EntityManager* entityManager, Engine::ComponentManager* componentManager, Engine::Window* windowManager);
		void renderUpdate(Engine::EntityManager* entityManager, Engine::ComponentManager* componentManager, Engine::Window* windowManager);

		

		// Overloaded functions

		void create(const Engine::SystemContext& ctx);

		void update(const Engine::SystemContext& ctx);

		void render(const Engine::SystemContext& ctx);

		void quit(const Engine::SystemContext& ctx);
	private:
		std::map<Engine::Entity, MarketComponent*> _markets{ };
	};
}