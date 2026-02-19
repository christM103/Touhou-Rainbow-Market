#pragma once

#include <deque>

#include "Engine/ECS/System/BaseSystem.hpp"
#include "Game/Objects/Components/Common/TextboxComponent.hpp"

namespace TR {
	class TextboxSystem {
        
	public:
		TextboxSystem() = default;
		~TextboxSystem();

		void initTextbox(Engine::ComponentManager* componentManager, Engine::Window* windowManager);

		void updateEntity(const Engine::EntityManager* entityManager, Engine::ComponentManager* componentManager, Engine::Window* windowManager);

		void updateRender(const Engine::EntityManager* entityManager, Engine::ComponentManager* componentManager, Engine::Window* windowManager);

		std::string textFormatting(std::string font, int size, std::string text);

		// Overloaded functions

		void create(const Engine::SystemContext& ctx);

		void update(const Engine::SystemContext& ctx);

		void render(const Engine::SystemContext& ctx);

		void quit(const Engine::SystemContext& ctx);
	private:
		std::unordered_map<Engine::Entity, std::unique_ptr<TextBoxComponent>> _textboxes{ }; // Set of multi sprite objects
	};
}