#pragma once

#include "Engine/ECS/System/InputSystem.hpp"



void Engine::InputSystem::init(const EntityManager* entityManager, ComponentManager* componentManager) {


	const auto* buttonEntities = componentManager->allEntities<InputComponent>();
	const auto* keyboardEntities = componentManager->allEntities<KeyboardComponent>();
	const auto* mouseEntities = componentManager->allEntities<MouseComponent>();

	if (buttonEntities) {
		for (auto& entity : *buttonEntities) {
			if (entity_inputs.at(Button).find(entity) == entity_inputs.at(Button).end()) {
				for (auto& keys : componentManager->getComponent<InputComponent>(entity)->scancode) {
					entity_inputs.at(Button).emplace(entity);
					keyboard_keys.emplace(keys.first, KeyComponent(keys.first));
					if (keys.second == nullptr) {
						keys.second = &(keyboard_keys.at(keys.first));
					}
				}
			}
		}
	}

	if (keyboardEntities) {
		for (auto& entity : *keyboardEntities) {
			if (entity_inputs.at(Keyboard).find(entity) == entity_inputs.at(Keyboard).end()) {
				entity_inputs.at(Keyboard).emplace(entity);
				componentManager->getComponent<KeyboardComponent>(entity)->key = &current_key;
			}
		}
	}

	if (mouseEntities) {
		for (auto& entity : *mouseEntities) {
			if (entity_inputs.at(Mouse).find(entity) == entity_inputs.at(Mouse).end()) {
				entity_inputs.at(Mouse).emplace(entity);
				componentManager->getComponent<MouseComponent>(entity)->position = &mouse_position;
				componentManager->getComponent<MouseComponent>(entity)->buttonL = &(mouse_buttons.at(1));
				componentManager->getComponent<MouseComponent>(entity)->buttonM = &(mouse_buttons.at(2));
				componentManager->getComponent<MouseComponent>(entity)->buttonR = &(mouse_buttons.at(3));
			}
		}
	}

}

void Engine::InputSystem::updateInput(const EntityManager* entityManager, ComponentManager* componentManager, const Input* inputManager) {


	// Erases any entity that no longer exists
	for (auto cat : { Button, Keyboard, Mouse }) {
		std::erase_if(entity_inputs.at(cat), [&](const auto& item) {
			const auto& entity = item;
			const auto& entMap = entityManager->getEntities();
			const auto it = std::find_if(entMap.begin(), entMap.end(), [&](const auto& pair) {
				return pair.second == entity;
				});
			return (it == entMap.end());
			});
	}

	/* Potentially implement lambda for searching through the entity list to remove an entity */

	// Update for any added entites within the engine
	init(entityManager, componentManager);

	// Updates all stored keys
	if (!keyboard_keys.empty()) {
		for (auto& key : keyboard_keys) {
			if (inputManager->isKeyPressed(static_cast<SDL_Scancode>(key.first))) {
				if (!key.second.isPressed && !key.second.isHeld) {
					key.second.isPressed = true;
					key.second.isHeld = false;
				}
				else {
					key.second.isHeld = true;
					key.second.isPressed = false;
				}
				key.second.isReleased = false;
			}
			else {
				if (key.second.isPressed || key.second.isHeld) {
					key.second.isReleased = true;
				}
				else if (key.second.isReleased) {
					key.second.isReleased = false;
				}
				key.second.isPressed = false;
				key.second.isHeld = false;
			}
		}
	}

	// Updates the mouse buttons
	if (!mouse_buttons.empty()) {
		mouse_position = inputManager->getMousePosition();

		for (auto& button : mouse_buttons) {
			if (inputManager->isMouseClicked(button.first)) {
				if (!button.second.isPressed && !button.second.isHeld) {
					button.second.isPressed = true;
					button.second.isHeld = false;
				}
				else {
					button.second.isHeld = true;
					button.second.isPressed = false;
				}
				button.second.isReleased = false;
			}
			else {
				if (button.second.isPressed || button.second.isHeld) {
					button.second.isReleased = true;
				}
				else if (button.second.isReleased) {
					button.second.isReleased = false;
				}
				button.second.isPressed = false;
				button.second.isHeld = false;
			}
		}
	}	

	// Updates the current keyboard
	if (!entity_inputs.at(Keyboard).empty()) {
		auto key = inputManager->getCurrentKey();
		if (key.second == false) {
			current_key = 0;
		}
		else {
			current_key = key.first;
		}
	}

}

// Overloaded functions

void Engine::InputSystem::create(const SystemContext& ctx) {
	if (!ctx.entityManager || !ctx.componentManager) {
		return;
	}
	else {
		this->init(ctx.entityManager, ctx.componentManager);
	}
}

void Engine::InputSystem::update(const SystemContext& ctx) {
	if (!ctx.entityManager || !ctx.componentManager || !ctx.input) {
		return;
	}
	else {
		this->updateInput(ctx.entityManager, ctx.componentManager, ctx.input);
	}

}

void Engine::InputSystem::render(const SystemContext& ctx) {

}

void Engine::InputSystem::quit(const SystemContext& ctx) {
	entity_inputs.clear();
	keyboard_keys.clear();
	mouse_buttons.clear();
}