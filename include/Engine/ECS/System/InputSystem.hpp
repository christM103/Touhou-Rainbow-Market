#pragma once

#include <vector>

#include <Engine/ECS/System/BaseSystem.hpp>

namespace Engine {
	class InputSystem {
		enum InputType : uint8_t {
			Button = 1, Keyboard = 2, Mouse = 3
		};

	public:

		InputSystem() = default;
		~InputSystem() = default;

		void init(const EntityManager* entityManager, ComponentManager* componentManager);

		void updateInput(const EntityManager* entityManager, ComponentManager* componentManager, const Input* inputManager);

		// Overloaded functions

		void create(const SystemContext& ctx);

		void update(const SystemContext& ctx);

		void render(const SystemContext& ctx);

		void quit(const SystemContext& ctx);

	private:
		std::unordered_map<InputType, std::unordered_set<Entity>> entity_inputs{ {Button, {}}, {Keyboard, {}}, {Mouse, {}} };

		std::unordered_map<Keycode, KeyComponent> keyboard_keys{};																// Button Key
		Keycode current_key{ 0 };																								// Keyboard Key
		Vector2i mouse_position{ 0,0 };																							// Mouse Position
		std::unordered_map<char, MouseButton> mouse_buttons{ {1, MouseButton()} , {2, MouseButton()} , {3, MouseButton()} };	// Mouse Button
	};
}