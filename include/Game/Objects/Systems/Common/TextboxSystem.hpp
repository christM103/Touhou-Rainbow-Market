#pragma once

#include <deque>

#include "Engine/ECS/System/BaseSystem.hpp"
#include "Game/Objects/Components/Common/TextboxComponent.hpp"

namespace TR {
	class TextboxSystem {
        
	public:
		TextboxSystem() = default;
		~TextboxSystem();

		// System Functions
		void initTextbox(Engine::ComponentManager* componentManager, Engine::Window* windowManager, Engine::AssetManager* assetManager);
		void updateEntity(const Engine::EntityManager* entityManager, Engine::ComponentManager* componentManager, Engine::Window* windowManager, Engine::AssetManager* assetManager);
		void updateRender(Engine::ComponentManager* componentManager, Engine::Window* windowManager);

		// Textbox Utility Functions
		void calculateSize(TextBoxComponent* textbox, bool isDynamic = false, Engine::MultiTransformComponent* transform_comp = nullptr);
		void setStructure(TextBoxComponent* textbox, Engine::MultiSpriteComponent* sprites, Engine::MultiTransformComponent* transform, Engine::Vector2i position);
		Engine::Vector2f textboxTransition(TextBoxComponent* textbox, Engine::TransformComponent* transform, TextBoxComponent::TextBoxFlags direction, Engine::Vector2i window);
		std::string textFormatting(std::string font, int size, uint16_t width, std::string text);

		// Overloaded functions

		void create(const Engine::SystemContext& ctx);

		void update(const Engine::SystemContext& ctx);

		void render(const Engine::SystemContext& ctx);

		void quit(const Engine::SystemContext& ctx);
	private:
		std::unordered_map<Engine::Entity, TextBoxComponent*> _textboxes{ }; // Set of textbox objects
	};
}