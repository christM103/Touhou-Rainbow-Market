#pragma once

#include "Game/Objects/Systems/Market/MarketSystem.hpp"
#include <ranges>

void TR::MarketSystem::marketInit(Engine::ComponentManager* componentManager, Engine::Window* windowManager, Engine::AssetManager* assetManager) {
	assetManager->loadTexture("assets/gfx/sprites/Market_Game/Placeholder_Game_MarketFree_S.png", "MKT_NULL", windowManager->getRenderer());
	assetManager->loadTexture("assets/gfx/sprites/Market_Game/Placeholder_Game_MarketMystia_S.png", "MKT_MYST", windowManager->getRenderer());

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
	componentManager->getComponent<Engine::MultiTransformComponent>(marketEntities[4])->transforms.emplace(0, std::make_shared<Engine::TransformComponent>(Engine::Vector2i(840, 420)));
	componentManager->getComponent<Engine::MultiTransformComponent>(marketEntities[5])->transforms.emplace(0, std::make_shared<Engine::TransformComponent>(Engine::Vector2i(630, 500)));

	for (auto& entity : marketEntities) {
		Engine::Vector2i pos = componentManager->getComponent<Engine::MultiTransformComponent>(entity)->transforms.at(0).get()->position;
		componentManager->addComponent<Engine::ColliderComponent>(entity, 
			Engine::Rectf(static_cast<float>(pos.x) + 25.0f, static_cast<float>(pos.y) + 25.0f, 150.0f, 150.0f), Engine::Vector2f(), false, true);
	}

	 
}

void TR::MarketSystem::updateEntities(Engine::EntityManager* entityManager, Engine::ComponentManager* componentManager, Engine::Window* windowManager, Engine::AssetManager* assetManager) {
	// Updates current render data by erasing any entities that currently do not exist

	std::erase_if(_markets, [&](const auto& item) {
		const auto& [entity, data] = item;
		const auto& entMap = entityManager->getEntities();
		const auto it = std::find_if(entMap.begin(), entMap.end(), [&](const auto& pair) {
			return pair.second == entity;
			});
		return (it == entMap.end());
		});

	auto* markets = componentManager->allEntities<MarketComponent>();

	if (!markets) {
		return;
	}
	if (_markets.size() != 6) {
		this->marketInit(componentManager, windowManager, assetManager);
	}
}

void TR::MarketSystem::marketUpdate(Engine::EntityManager* entityManager, Engine::ComponentManager* componentManager, Engine::Window* windowManager) {
	Engine::ColliderComponent* _collision_comp;
	Engine::MouseComponent* _mouse_comp = componentManager->getComponent<Engine::MouseComponent>(entityManager->getEntities().at("MOUSE"));

	for (auto& [entity, market] : std::views::reverse(_markets)) {
		switch (market->market_ID) {
			case Market_ID::MID_Mystia:
				if (componentManager->getComponent<Engine::MultiSpriteComponent>(entity)->sprites.at(0)->getResourceID() != "MKT_MYST") {
					componentManager->getComponent<Engine::MultiSpriteComponent>(entity)->sprites.at(0)->setResourceID("MKT_MYST");
				}
				break;
			default:
				if (componentManager->getComponent<Engine::MultiSpriteComponent>(entity)->sprites.at(0)->getResourceID() != "MKT_NULL") {
					componentManager->getComponent<Engine::MultiSpriteComponent>(entity)->sprites.at(0)->setResourceID("MKT_NULL");
				}
				break;
		}
		

		/*
		switch (componentManager->getComponent<Engine::MultiSpriteComponent>(entity)->sprites.at(0)->getResourceID()) {

		}
		*/
		if (_mouse_comp->leftPressed()) {
			_collision_comp = componentManager->getComponent<Engine::ColliderComponent>(entity);
			if (_collision_comp->objPressed()) {
				std::cout << "At entity " << entity << ": ";
				std::cout << "Active" << std::endl;
				market->market_active = true;
				break;
			}
			else {
				market->market_active = false;
			}
		}
	}
}

void TR::MarketSystem::create(const Engine::SystemContext& ctx) {
	if (!ctx.componentManager || !ctx.window || !ctx.assetManager) {
		return;
	}
	else {
		marketInit(ctx.componentManager, ctx.window, ctx.assetManager);
	}
}

void TR::MarketSystem::update(const Engine::SystemContext& ctx) {
	if (!ctx.entityManager || !ctx.componentManager || !ctx.assetManager || !ctx.window) {
		return;
	}
	else {
		updateEntities(ctx.entityManager, ctx.componentManager, ctx.window, ctx.assetManager);
		marketUpdate(ctx.entityManager, ctx.componentManager, ctx.window);
	}
}

void TR::MarketSystem::render(const Engine::SystemContext& ctx) {

}

void TR::MarketSystem::quit(const Engine::SystemContext& ctx) {

}