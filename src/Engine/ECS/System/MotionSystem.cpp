#pragma once

#include "Engine/ECS/System/MotionSystem.hpp"


void Engine::MotionSystem::init(const EntityManager* entityManager, ComponentManager* componentManager) {
	TransType trans;
	VelType vel;

	for (const auto& entity : entityManager->getEntities()) {
		if (_entities.find(entity) == _entities.end()) {
			if (componentManager->hasComponent<TransformComponent>(entity)) {
				trans = isSingleTrans;
			}
			else if (componentManager->hasComponent<MultiTransformComponent>(entity)) {
				trans = isMultiTrans;
			}
			else {
				continue;
			}

			if (componentManager->hasComponent<VelocityComponent>(entity)) {
				vel = isSingleVel;
			}
			else if (componentManager->hasComponent<MultiVelocityComponent>(entity)) {
				vel = isMultiVel;
			}
			else {
				continue;
			}
			
			_entities.emplace(entity, std::make_tuple(trans, vel));
		}
	}
}

void Engine::MotionSystem::movementUpdate(const EntityManager* entityManager, ComponentManager* componentManager) {
	TransformComponent* transformComp;
	VelocityComponent* velocityComp;

	MultiTransformComponent* multiTransComp;
	MultiVelocityComponent* multiVelComp;

	auto transformationMutator = [](TransformComponent* transformComp, VelocityComponent* velocityComp) {
		transformComp->position = Vector2i(transformComp->position.x + velocityComp->linear.x, transformComp->position.y + velocityComp->linear.y);
		transformComp->rotation += velocityComp->angular;
		transformComp->scale += velocityComp->scalar;
	};

	std::erase_if(_entities, [&](const auto& item) {
		const Entity& entity = std::get<0>(item);
		return entityManager->getEntities().find(entity) == entityManager->getEntities().end();
		});
	this->init(entityManager, componentManager);

	for (const auto& pair: _entities) {
		auto& entity = std::get<0>(pair);
		auto& entity_type = std::get<1>(pair);
		if (std::get<0>(entity_type) == isSingleTrans) {
			transformComp = componentManager->getComponent<TransformComponent>(entity);
			if (std::get<1>(entity_type) == isSingleVel) {
				velocityComp = componentManager->getComponent<VelocityComponent>(entity);
				transformationMutator(transformComp, velocityComp);
			}
		}
		else {
			multiTransComp = componentManager->getComponent<MultiTransformComponent>(entity);
			if (std::get<1>(entity_type) == isSingleVel) {
				velocityComp = componentManager->getComponent<VelocityComponent>(entity);
				for (const auto& pair : multiTransComp->transforms) {
					transformationMutator(std::get<1>(pair).get(), velocityComp);
				}
			}
			else {
				multiVelComp = componentManager->getComponent<MultiVelocityComponent>(entity);
				for (const auto& pair : multiTransComp->transforms) {
					auto index = std::get<0>(pair);
					auto transform = std::get<1>(pair).get();
					transformationMutator(transform, multiVelComp->velocities.find(index)->second.get());
				}
			}
		}
	}

}

// Overloaded functions

void Engine::MotionSystem::create(const SystemContext& ctx) {
	if (!ctx.entityManager || !ctx.componentManager) {
		return;
	}
	else {
		init(ctx.entityManager, ctx.componentManager);
	}
}

void Engine::MotionSystem::update(const SystemContext& ctx) {
	if (!ctx.entityManager || !ctx.componentManager) {
		return;
	}
	else {
		movementUpdate(ctx.entityManager, ctx.componentManager);
	}
}

void Engine::MotionSystem::render(const SystemContext& ctx) {

}

void Engine::MotionSystem::quit(const SystemContext& ctx) {
	this->~MotionSystem();
}