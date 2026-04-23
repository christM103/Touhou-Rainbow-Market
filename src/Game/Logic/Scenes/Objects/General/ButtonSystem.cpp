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

				_collision_comp.colliders.emplace(0, std::make_shared<Engine::ColliderComponent>(Engine::Rectf(static_cast<float>(yesButton.position.x), static_cast<float>(yesButton.position.y), 120.0f, 80.0f), Engine::Vector2f(), false, true));
				_collision_comp.colliders.emplace(1, std::make_shared<Engine::ColliderComponent>(Engine::Rectf(static_cast<float>(noButton.position.x), static_cast<float>(noButton.position.y), 120.0f, 80.0f), Engine::Vector2f(), false, true));

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
	Engine::SpriteComponent* spriteYes, *spriteNo;

	for (const auto& [entity, data] : _buttonPrompts) {
		colliderYes = componentManager->getComponent<Engine::MultiColliderComponent>(entity)->colliders.at(0).get();
		colliderNo = componentManager->getComponent<Engine::MultiColliderComponent>(entity)->colliders.at(1).get();

		spriteYes = componentManager->getComponent<Engine::MultiSpriteComponent>(entity)->sprites.at(0).get();
		spriteNo = componentManager->getComponent<Engine::MultiSpriteComponent>(entity)->sprites.at(1).get();

		colliderYes->objPressed() ? data->_buttonTrue.activated = true : data->_buttonTrue.activated = false;
		colliderNo->objPressed() ? data->_buttonFalse.activated = true : data->_buttonFalse.activated = false;


		colliderYes->objHovered() ? data->_buttonTrue.hovered = true : data->_buttonTrue.hovered = false;
		colliderNo->objHovered() ? data->_buttonFalse.hovered = true : data->_buttonFalse.hovered = false;

		if (data->_buttonTrue.hovered) {
			if (spriteYes->getColor()->rgb.x != 55) {
				spriteYes->setColor(Engine::ColorComponent(
					Engine::Vector3<uint8_t>(55, spriteYes->getColor()->rgb.y, spriteYes->getColor()->rgb.z),
					spriteYes->getColor()->alpha));
			}
		}
		else {
			if (spriteYes->getColor()->rgb.x != 255) {
				spriteYes->setColor(Engine::ColorComponent(
					Engine::Vector3<uint8_t>(255, spriteYes->getColor()->rgb.y, spriteYes->getColor()->rgb.z),
					spriteYes->getColor()->alpha));
			}
		}

		if (data->_buttonFalse.hovered) {
			if (spriteNo->getColor()->rgb.x != 55) {
				spriteNo->setColor(Engine::ColorComponent(
					Engine::Vector3<uint8_t>(55, spriteNo->getColor()->rgb.y, spriteNo->getColor()->rgb.z),
					spriteNo->getColor()->alpha));
			}
		}
		else {
			if (spriteNo->getColor()->rgb.x != 255) {
				spriteNo->setColor(Engine::ColorComponent(
					Engine::Vector3<uint8_t>(255, spriteNo->getColor()->rgb.y, spriteNo->getColor()->rgb.z),
					spriteNo->getColor()->alpha));
			}
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