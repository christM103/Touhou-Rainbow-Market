#pragma once

#include "Game/Objects/Systems/Common/ButtonSystem.hpp"

void TR::ButtonSystem::initButtonPrompt(Engine::ComponentManager* componentManager, Engine::Window* windowManager, Engine::AssetManager* assetManager) {
	// Texture Initilization
	if (!assetManager->getTexture("BUTTON_YES")) {
		assetManager->loadTexture("assets/gfx/sprites/Common/Placeholder_Button_Yes.png", "BUTTON_YES", windowManager->getRenderer());
	}
	if (!assetManager->getTexture("BUTTON_NO")) {
		assetManager->loadTexture("assets/gfx/sprites/Common/Placeholder_Button_No.png", "BUTTON_NO", windowManager->getRenderer());
	}

	const auto* entities = componentManager->allEntities<ButtonPromptComponent>();
	ButtonPromptComponent* button_prompt;
	Engine::TransformComponent yesButton, noButton;
	Engine::Vector2i position;

	uint8_t button_layout = ButtonPromptComponent::HORIZONTAL | ButtonPromptComponent::VERTICAL;

	if (!entities) {
		return;
	}

	// Initialize the button_promptes for each entity
	for (const auto& entity : *entities) {
		if (_buttonPrompts.find(entity) == _buttonPrompts.end()) {
			button_prompt = componentManager->getComponent<ButtonPromptComponent>(entity);
			if (button_prompt && _buttonPrompts.try_emplace(entity, button_prompt).second) {

				auto& _transform_comp = componentManager->addComponent<Engine::MultiTransformComponent>(entity);
				auto& _velocity_comp = componentManager->addComponent<Engine::VelocityComponent>(entity, Engine::Vector2f(0, 0));
				auto& _sprite_comp = componentManager->addComponent<Engine::MultiSpriteComponent>(entity);
				auto& _collision_comp = componentManager->addComponent<Engine::MultiColliderComponent>(entity);
				auto& _render_comp = componentManager->addComponent<Engine::RenderLayerComponent>(entity, Engine::RenderLayerComponent::TEXTBOX + 1);

				// Position Calculations
				position = button_prompt->position;

				switch (uint16_t state = (button_prompt->layout & button_layout)) {
					case ButtonPromptComponent::HORIZONTAL:
						yesButton.position = position;
						noButton.position = position + Engine::Vector2i(160, 0);
					break;

					case ButtonPromptComponent::VERTICAL:
						yesButton.position = position;
						noButton.position = position + Engine::Vector2i(0, 120);
					break;

					default:
					break;
				}

				_transform_comp.transforms.emplace(0, std::make_shared<Engine::TransformComponent>(yesButton));
				_transform_comp.transforms.emplace(1, std::make_shared<Engine::TransformComponent>(noButton));

				_collision_comp.colliders.emplace(0, std::make_shared<Engine::ColliderComponent>(Engine::Rectf(yesButton.position.x, yesButton.position.y, 120.0f, 80.0f), Engine::Vector2f(), false, true));
				_collision_comp.colliders.emplace(1, std::make_shared<Engine::ColliderComponent>(Engine::Rectf(noButton.position.x, noButton.position.y, 120.0f, 80.0f), Engine::Vector2f(), false, true));

				_sprite_comp.sprites.emplace(0, std::make_shared<Engine::SpriteComponent>(Engine::Recti(0, 0, 120, 80), Engine::Vector2i(120, 80), "BUTTON_YES"));
				_sprite_comp.sprites.emplace(1, std::make_shared<Engine::SpriteComponent>(Engine::Recti(0, 0, 120, 80), Engine::Vector2i(120, 80), "BUTTON_NO"));

			}
		}
	}
}

void TR::ButtonSystem::updateEntity(const Engine::EntityManager* entityManager, Engine::ComponentManager* componentManager, Engine::Window* windowManager, Engine::AssetManager* assetManager) {
	std::erase_if(_buttonPrompts, [&](const auto& item) {
		const auto& [entity, component] = item;
		const auto& entMap = entityManager->getEntities();
		const auto it = std::find_if(entMap.begin(), entMap.end(), [&](const auto& pair) {
			return pair.second == entity;
			});
		return (it == entMap.end());
		});

	if (auto* entities = componentManager->allEntities<ButtonPromptComponent>()) {
		if (entities->size() > _buttonPrompts.size()) {
			this->initButtonPrompt(componentManager, windowManager, assetManager);
		}
	}
}

void TR::ButtonSystem::updateButtons(Engine::ComponentManager* componentManager, Engine::Window* windowManager) {
	Engine::ColliderComponent* colliderYes, *colliderNo;
	for (const auto& [entity, data] : _buttonPrompts) {
		colliderYes = componentManager->getComponent<Engine::MultiColliderComponent>(entity)->colliders.at(0).get();
		colliderNo = componentManager->getComponent<Engine::MultiColliderComponent>(entity)->colliders.at(1).get();

		if (colliderYes->objPressed()) {
			data->_buttonTrue.activated = true;
		}
		else {
			data->_buttonTrue.activated = false;
		}

		if (colliderNo->objPressed()) {
			data->_buttonFalse.activated = true;
		}
		else {
			data->_buttonFalse.activated = false;
		}
	}
}

// Overloaded functions

void TR::ButtonSystem::create(const Engine::SystemContext& ctx) {
	if (!ctx.entityManager || !ctx.componentManager || !ctx.window || !ctx.assetManager) {
		return;
	}
	else {
		this->initButtonPrompt(ctx.componentManager, ctx.window, ctx.assetManager);
	}
}

void TR::ButtonSystem::update(const Engine::SystemContext& ctx) {
	if (!ctx.entityManager || !ctx.componentManager || !ctx.window || !ctx.assetManager) {
		return;
	}
	else {
		this->updateEntity(ctx.entityManager, ctx.componentManager, ctx.window, ctx.assetManager);
		this->updateButtons(ctx.componentManager, ctx.window);
	}
}

void TR::ButtonSystem::render(const Engine::SystemContext& ctx) {

}

void TR::ButtonSystem::quit(const Engine::SystemContext& ctx) {
	this->~ButtonSystem();
}