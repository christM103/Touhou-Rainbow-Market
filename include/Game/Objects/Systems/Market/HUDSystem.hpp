#pragma once

#include "Engine/ECS/System/BaseSystem.hpp"
#include "Game/Logic/Common.hpp"
#include "Game/Objects/Components/Common/PlayerComponent.hpp"
#include "Game/Objects/Components/Market/MarketComponent.hpp"
#include "Game/Objects/Components/Market/HUDComponent.hpp"

namespace TR {
	class HUDSystem {
	public:
		HUDSystem() = default;
		~HUDSystem() = default;

		void initHUD(Engine::EntityManager* eM, Engine::ComponentManager* cM, Engine::Window* wM, Engine::AssetManager* aM);
		void updateEntites(Engine::EntityManager* eM, Engine::ComponentManager* cM, Engine::Window* wM, Engine::AssetManager* aM);
		void updateData(Engine::EntityManager* eM, Engine::ComponentManager* cM, Engine::Window* wM);
		void recordInput();

		// Overloaded functions

		void create(const Engine::SystemContext& ctx);

		void update(const Engine::SystemContext& ctx);

		void render(const Engine::SystemContext& ctx);

		void quit(const Engine::SystemContext& ctx);

	private:
		bool _systemEnable{ true };
		HUDComponent* _HUD_Component;
		PlayerComponent* _player_component;
		MarketComponent* _market_component;
		Engine::InputComponent* _input_component;

		static constexpr std::string_view HUD_ENTITY_NAME = "HUD_DISPLAY";
		static constexpr std::string_view PLAYER1_ENTITY_NAME = "PLAYER";
		static constexpr std::string_view KEYBOARD_ENTITY_NAME = "KEYBOARD";
	};
}