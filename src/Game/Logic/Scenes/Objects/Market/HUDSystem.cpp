#pragma once

#include "Game/Objects/Systems/Market/HUDSystem.hpp"



void TR::HUDSystem::initHUD(Engine::ComponentManager* componentManager, Engine::Window* windowManager, Engine::AssetManager* assetManagerr) {

	//auto& _text_comp = componentManager->addComponent<Engine::MultiTextComponent>(*active_entity.first);
}

void TR::HUDSystem::updateEntites(const Engine::EntityManager* entityManager, Engine::ComponentManager* componentManager) {

}

void TR::HUDSystem::updateData(Engine::ComponentManager* componentManager, Engine::Window* windowManager) {

}

void TR::HUDSystem::create(const Engine::SystemContext& ctx) {
	if (!ctx.entityManager || !ctx.componentManager || !ctx.window || !ctx.assetManager) {
		return;
	}
	else {
		this->initHUD(ctx.componentManager, ctx.window, ctx.assetManager);
	}
}

void TR::HUDSystem::update(const Engine::SystemContext& ctx) {
	if (!ctx.entityManager || !ctx.componentManager || !ctx.window || !ctx.assetManager) {
		return;
	}
	else {
		this->updateEntites(ctx.entityManager, ctx.componentManager);
		this->updateData(ctx.componentManager, ctx.window);
	}
}

void TR::HUDSystem::render(const Engine::SystemContext& ctx) {

}

void TR::HUDSystem::quit(const Engine::SystemContext& ctx) {
	this->~HUDSystem();
}