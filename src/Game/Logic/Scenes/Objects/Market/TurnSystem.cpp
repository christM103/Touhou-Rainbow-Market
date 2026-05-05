#pragma once

#include "Game/Objects/Systems/Market/TurnSystem.hpp"
TR::TurnSystem::~TurnSystem() {

}

void TR::TurnSystem::initTurns(Engine::ComponentManager* componentManager, Engine::Window* windowManager, Engine::AssetManager* assetManager) {
	if (auto turnEntities = componentManager->allEntities<TurnsComponent>()) {
		active_entity = std::make_pair(&(*turnEntities->begin()), componentManager->getComponent<TurnsComponent>(*turnEntities->begin())) ;
		auto* _turns_comp = componentManager->getComponent<TurnsComponent>(*active_entity.first);

		for (auto i : _turns_comp->turns) {
			if (!assetManager->getTexture("TURN_" + i.first)) {
				std::string turnStr = "TURN_" + std::to_string(i.first);
				std::string turnStrPath = "assets/gfx/sprites/Market_Game/Placeholder_Game_Turn" + std::to_string(i.first) + ".png";
				assetManager->loadTexture(turnStrPath, turnStr.c_str(), windowManager->getRenderer());
			}
		}

		auto& _transform_comp = componentManager->addComponent<Engine::MultiTransformComponent>(*active_entity.first);
		auto& _sprite_comp = componentManager->addComponent<Engine::MultiSpriteComponent>(*active_entity.first);
		auto turn_str = "TURN_" + std::to_string(active_entity.second->current_turn);

		auto current_sprite = Engine::SpriteComponent(Engine::Recti{ 0,0,400,200 }, Engine::Vector2i(400, 200), turn_str.c_str());
		auto initial_trans = Engine::TransformComponent(Engine::Vector2i(windowManager->getWidth()/2, -100), 0.0f, Engine::Vector2f(1.0f, 1.0f), true);

		_sprite_comp.sprites.emplace(0, std::make_shared<Engine::SpriteComponent>(current_sprite));
		_transform_comp.transforms.emplace(0, std::make_shared<Engine::TransformComponent>(initial_trans));


		componentManager->addComponent<Engine::VelocityComponent>(*active_entity.first);
		componentManager->addComponent<TimerComponent>(*active_entity.first);
		timer = std::make_unique<Engine::Timer>(Engine::Timer(false));
	}
	else {
		return;
	}
}

void TR::TurnSystem::updateEntites(Engine::ComponentManager* componentManager, Engine::Window* windowManager, Engine::AssetManager* assetManager) {
	if (auto* entities = componentManager->allEntities<TurnsComponent>()) {
		if (active_entity.first == nullptr || entities->find(*(active_entity.first)) == entities->end()) {
			active_entity.first = nullptr;
			timer.release();
		}
	}
	else {
		active_entity.first = nullptr;
		timer.release();
	}

	if (active_entity.first == nullptr) {
		if (auto* entities = componentManager->allEntities<TurnsComponent>()) {
			this->initTurns(componentManager, windowManager, assetManager);
		}
	}
}

void TR::TurnSystem::updateTurns(Engine::ComponentManager* componentManager, Engine::Window* windowManager) {

	if (active_entity.first != nullptr) {
		auto active_turn = active_entity.second->turns.at(active_entity.second->current_turn);

		auto* _transform_comp = componentManager->getComponent<Engine::MultiTransformComponent>(*active_entity.first);
		auto* _sprite_comp = componentManager->getComponent<Engine::MultiSpriteComponent>(*active_entity.first);
		auto* _velocity_comp = componentManager->getComponent<Engine::VelocityComponent>(*active_entity.first);
		auto* _timer_comp = componentManager->getComponent<TimerComponent>(*active_entity.first);

		auto turn_str = "TURN_" + std::to_string(active_entity.second->current_turn);
		
		if (_sprite_comp->sprites.at(0)->getResourceID() != turn_str) {
			_sprite_comp->sprites.at(0)->setResourceID(turn_str.c_str());
		}

		if (active_turn.turn_started) {
			if (_transform_comp->transforms.at(0)->position.y < 200) {
				_velocity_comp->linear = Engine::Vector2f(0, 5);
			}
			else {
				_velocity_comp->linear = Engine::Vector2f(0, 0);
			}
		}
	}
}

// Overloaded functions

void TR::TurnSystem::create(const Engine::SystemContext& ctx) {
	if (!ctx.entityManager || !ctx.componentManager || !ctx.window || !ctx.assetManager) {
		return;
	}
	else {
		this->initTurns(ctx.componentManager, ctx.window, ctx.assetManager);
	}
}

void TR::TurnSystem::update(const Engine::SystemContext& ctx) {
	if (!ctx.entityManager || !ctx.componentManager || !ctx.window || !ctx.assetManager) {
		return;
	}
	else {
		this->updateEntites(ctx.componentManager, ctx.window, ctx.assetManager);
		this->updateTurns(ctx.componentManager, ctx.window);
	}
}

void TR::TurnSystem::render(const Engine::SystemContext& ctx) {

}

void TR::TurnSystem::quit(const Engine::SystemContext& ctx) {

}