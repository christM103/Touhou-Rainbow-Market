#pragma once

#include "Engine/ECS/System/BaseSystem.hpp"
#include "Game/Logic/Common.hpp"

#include "Game/Objects/Components/Common/PlayerComponent.hpp"
#include "Game/Objects/Components/Market/MarketComponent.hpp"
#include "Game/Objects/Components/Market/ActionComponent.hpp"

namespace TR {
	class ActionSystem {
	public:
		void actionInit(Engine::ComponentManager* cM);
		void actionUpdate(Engine::ComponentManager* cM);
		void actionEnable(Engine::EntityManager* eM, Engine::ComponentManager* cM);
		void actionAnimate(Engine::ComponentManager* cM, Engine::Window* wM, Engine::AssetManager* aM);

		void profitActions(ActionComponent* action);
		void shutdownActions(ActionComponent* action);
		void immunityActions(ActionComponent* action);
		void profitRatesActions(ActionComponent* action);
		void sellActions(ActionComponent* action);
		void destroyActions(ActionComponent* action);
		void otherActions(ActionComponent* action);

		// Overloaded functions

		void create(const Engine::SystemContext& ctx);

		void update(const Engine::SystemContext& ctx);

		void render(const Engine::SystemContext& ctx);

		void quit(const Engine::SystemContext& ctx);
	private:
		std::vector<ActionComponent*> _action_queue;
	};
}