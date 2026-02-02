#pragma once

#include "Game/Objects/Systems/Common/TextboxSystem.hpp"


TR::TextboxSystem::~TextboxSystem() {

}

void TR::TextboxSystem::init(const Engine::EntityManager* entityManager, const Engine::ComponentManager* componentManager) {

	// Initializes any entities that are textboxes
	for (Engine::Entity entity : entityManager->getEntities()) {
		if (componentManager->hasComponent<TextBoxComponent>(entity)) {
			_textbox_entities.push_back(entity);
		}
	}

	// Initialize the textboxes for each entity
	for (const auto& entity : _textbox_entities) {
		const TextBoxComponent* existing = componentManager->getComponent<TextBoxComponent>(entity);
		if (existing) {
			_textboxes.emplace(entity, std::make_unique<TextBoxComponent>(*existing));
		}
	}

}
void TR::TextboxSystem::updateRender(const Engine::EntityManager* entityManager, Engine::ComponentManager* componentManager) {
	for (auto& entity : _textbox_entities) {
		componentManager->addComponent<Engine::MultiTransformComponent>(entity, _textboxes[entity].get()->getMultiTransComponent());
		componentManager->addComponent<Engine::MultiSpriteComponent>(entity, _textboxes[entity].get()->getMultiSpriteComponent());
		componentManager->addComponent<Engine::MultiTextComponent>(entity, _textboxes[entity].get()->getMultiTextComponent());
		componentManager->addComponent<Engine::RenderLayerComponent>(entity, _textboxes[entity].get()->getRenderLayerComponent());
	}
	
}

// Overloaded functions

void TR::TextboxSystem::create(const Engine::SystemContext& ctx) {
	if (!ctx.entityManager || !ctx.componentManager) {
		return;
	}
	else {
		init(ctx.entityManager, ctx.componentManager);
		updateRender(ctx.entityManager, ctx.componentManager);
	}
}

void TR::TextboxSystem::update(const Engine::SystemContext& ctx) {
	
}

void TR::TextboxSystem::render(const Engine::SystemContext& ctx) {

}

void TR::TextboxSystem::quit(const Engine::SystemContext& ctx) {

}