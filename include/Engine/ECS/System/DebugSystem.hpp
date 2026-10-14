#pragma once

#include <Engine/ECS/System/BaseSystem.hpp>

namespace Engine {
	class DebugSystem {
	public:
		DebugSystem() = default;
		~DebugSystem() = default;

		// Overloaded functions

		void create(const SystemContext& ctx);

		void update(const SystemContext& ctx);

		void render(const SystemContext& ctx);

		void quit(const SystemContext& ctx);
	private:
		// Debug UI constants
		static constexpr Vector2i DEBUG_TEXT_POSITION{ 32, 32 };
		static constexpr Vector2i DEBUG_TEXT_SIZE{ 1216, 200 };
		static constexpr Vector2i DEBUG_PROMPT_POSITION{ 32, 160 };
		static constexpr Vector2i DEBUG_PROMPT_SIZE{ 1216, 500 };
		static constexpr int DEBUG_FONT_SIZE = 20;
		static constexpr Vector4i DEBUG_TEXT_COLOR{ 255, 255, 255, 255 };

		static constexpr std::string_view DEBUG_TEXT_ENTITY_NAME = "DEBUG_TEXT";
		static constexpr std::string_view DEBUG_PROMPT_ENTITY_NAME = "DEBUG_PROMPT";


		bool _is_init{ false };
		Entity _debug_entity_text, _debug_entity_prompt;
		InputComponent* _screen_input;

		void initDebug(EntityManager* entityManager, ComponentManager* componentManager);
		void updateText(EntityManager* entityManager, ComponentManager* componentManager);
		void updatePrompt(EntityManager* entityManager, ComponentManager* componentManager);
		void updateInput(ComponentManager* componentManager);
		void updateEntities(EntityManager* entityManager, ComponentManager* componentManager);
	};
}