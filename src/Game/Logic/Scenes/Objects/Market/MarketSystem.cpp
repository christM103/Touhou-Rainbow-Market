#pragma once

#include "Game/Objects/Systems/Market/MarketSystem.hpp"

void TR::MarketSystem::marketInit(Engine::EntityManager* entityManager, Engine::ComponentManager* componentManager, Engine::Window* windowManager, Engine::AssetManager* assetManager) {
	assetManager->loadTexture("assets/gfx/sprites/Market_Game/Placeholder_Game_MarketFree_S.png", "MKT_NULL", windowManager->getRenderer());

	const auto& entities = componentManager->allEntities<MarketComponent>();
	std::vector<Engine::Entity> marketEntities;
	
	// Loading all market entities

	for (auto& entity : *entities) {
		if (_markets.find(entity) == _markets.end()) {
			_markets.emplace(entity, componentManager->getComponent<MarketComponent>(entity));
			auto& _transform_comp = componentManager->addComponent<Engine::MultiTransformComponent>(entity);
			auto& _velocity_comp = componentManager->addComponent<Engine::VelocityComponent>(entity, Engine::Vector2f(0, 0));
			auto& _sprite_comp = componentManager->addComponent<Engine::MultiSpriteComponent>(entity);
			auto& _render_comp = componentManager->addComponent<Engine::RenderLayerComponent>(entity, Engine::RenderLayerComponent::FG - 1);
			auto& _mouse_comp = componentManager->addComponent<Engine::MouseComponent>(entity);
		}
	}

	for (auto& [entity, market] : _markets) {
		marketEntities.push_back(entity);
		componentManager->getComponent<Engine::MultiSpriteComponent>(entity)->sprites.emplace(0, 
			std::make_shared<Engine::SpriteComponent>(Engine::Recti(0, 0, 200, 200), Engine::Vector2i(200, 200), "MKT_NULL"));
	}

	// Updates transformation of all markets

	componentManager->getComponent<Engine::MultiTransformComponent>(marketEntities[0])->transforms.emplace(0, std::make_shared<Engine::TransformComponent>(Engine::Vector2i(540, 300)));
	componentManager->getComponent<Engine::MultiTransformComponent>(marketEntities[1])->transforms.emplace(0, std::make_shared<Engine::TransformComponent>(Engine::Vector2i(330, 380)));
	componentManager->getComponent<Engine::MultiTransformComponent>(marketEntities[2])->transforms.emplace(0, std::make_shared<Engine::TransformComponent>(Engine::Vector2i(690, 360)));
	componentManager->getComponent<Engine::MultiTransformComponent>(marketEntities[3])->transforms.emplace(0, std::make_shared<Engine::TransformComponent>(Engine::Vector2i(480, 440)));
	componentManager->getComponent<Engine::MultiTransformComponent>(marketEntities[4])->transforms.emplace(0, std::make_shared<Engine::TransformComponent>(Engine::Vector2i(840, 430)));
	componentManager->getComponent<Engine::MultiTransformComponent>(marketEntities[5])->transforms.emplace(0, std::make_shared<Engine::TransformComponent>(Engine::Vector2i(630, 510)));

	for (auto& entity : marketEntities) {
		Engine::Vector2i pos = componentManager->getComponent<Engine::MultiTransformComponent>(entity)->transforms.at(0).get()->position;
		componentManager->addComponent<Engine::ColliderComponent>(entity, Engine::Rectf(static_cast<float>(pos.x) + 50.0, static_cast<float>(pos.y) + 50.0, 100.0, 100.0));
	}

	 
}

void TR::MarketSystem::marketUpdate(Engine::EntityManager* entityManager, Engine::ComponentManager* componentManager, Engine::Window* windowManager) {
	Engine::ColliderComponent* _collision_comp;
	Engine::MouseComponent* _mouse_comp;

	for (auto& [entity, market] : _markets) {
		_collision_comp = componentManager->getComponent<Engine::ColliderComponent>(entity);
		_mouse_comp = componentManager->getComponent<Engine::MouseComponent>(entity);
		if (_mouse_comp->leftPressed()) {
			std::cout << "At entity " << entity << ": ";
			if (_collision_comp->bounds.contains(Engine::Vector2f(static_cast<float>(_mouse_comp->position->x), static_cast<float>(_mouse_comp->position->y)))) {
				std::cout << "Active" << std::endl;
			}
			else {
				std::cout << "Not Active" << std::endl;
			}
		}
		
	}
}

void TR::MarketSystem::create(const Engine::SystemContext& ctx) {
	if (!ctx.entityManager || !ctx.componentManager || !ctx.window || !ctx.assetManager) {
		return;
	}
	else {
		marketInit(ctx.entityManager, ctx.componentManager, ctx.window, ctx.assetManager);
	}
}

void TR::MarketSystem::update(const Engine::SystemContext& ctx) {
	if (!ctx.entityManager || !ctx.componentManager || !ctx.window) {
		return;
	}
	else {
		marketUpdate(ctx.entityManager, ctx.componentManager, ctx.window);
	}
}

void TR::MarketSystem::render(const Engine::SystemContext& ctx) {

}

void TR::MarketSystem::quit(const Engine::SystemContext& ctx) {

}