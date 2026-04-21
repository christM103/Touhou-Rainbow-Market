#pragma once

#include "Engine/ECS/System/BaseSystem.hpp"
#include "Game/Objects/Components/Common/ButtonPromptComponent.hpp"

namespace TR {
	class ButtonSystem {

	public:
		ButtonSystem() = default;
		~ButtonSystem() = default;

		void initButtonPrompt(Engine::ComponentManager* componentManager, Engine::Window* windowManager, Engine::AssetManager* assetManager);
		void updateEntity(const Engine::EntityManager* entityManager, Engine::ComponentManager* componentManager, Engine::Window* windowManager, Engine::AssetManager* assetManager);
		void updateButtons(Engine::ComponentManager* componentManager, Engine::Window* windowManager);

		// Overloaded functions

		void create(const Engine::SystemContext& ctx);

		void update(const Engine::SystemContext& ctx);

		void render(const Engine::SystemContext& ctx);

		void quit(const Engine::SystemContext& ctx);

	private:
		std::unordered_map<Engine::Entity, ButtonPromptComponent*> _buttonPrompts{ }; // Set of button objects
	};
}