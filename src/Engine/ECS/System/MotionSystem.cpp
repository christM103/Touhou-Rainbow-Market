#pragma once

#include "Engine/ECS/System/MotionSystem.hpp"



void Engine::MotionSystem::init(const EntityManager* entityManager, ComponentManager* componentManager) {
	TransType trans;
	VelType vel;
	ColType col;

	for (const auto& [key, entity] : entityManager->getEntities()) {
		if (_entities.find(entity) == _entities.end()) {

			if (componentManager->hasComponent<ColliderComponent>(entity)) {
				col = hasCollider;
			}
			else {
				col = noCollider;
			}

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

			_entities.emplace(entity, std::make_tuple(trans, vel, col));
		}
	}
}

void Engine::MotionSystem::movementUpdate(const EntityManager* entityManager, ComponentManager* componentManager) {
	TransformComponent* transformComp;
	VelocityComponent* velocityComp;

	MultiTransformComponent* multiTransComp;
	MultiVelocityComponent* multiVelComp;

	ColliderComponent* colliderComp;

	auto transformationMutator = [](TransformComponent* transformComp, VelocityComponent* velocityComp) {
		transformComp->position = Vector2i(static_cast<int>(static_cast<float>(transformComp->position.x) + velocityComp->linear.x), 
			static_cast<int>(static_cast<float>(transformComp->position.y) + velocityComp->linear.y));
		transformComp->rotation += velocityComp->angular;
		transformComp->scale += velocityComp->scalar;
	};

	auto colliderMutator = [](ColliderComponent* colliderComp, VelocityComponent* velocityComp) {
		colliderComp->bounds.position += velocityComp->linear;
		colliderComp->bounds.size += velocityComp->scalar;
		};

	std::erase_if(_entities, [&](const auto& item) {
		const auto& [entity, data] = item;
		const auto& entMap = entityManager->getEntities();
		const auto it = std::find_if(entMap.begin(), entMap.end(), [&](const auto& pair) {
			return pair.second == entity;
			});
		return (it == entMap.end());
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
				if (std::get<2>(entity_type) == hasCollider) {
					colliderComp = componentManager->getComponent<ColliderComponent>(entity);
					colliderMutator(colliderComp, velocityComp);
				}
			}
		}
		else {
			multiTransComp = componentManager->getComponent<MultiTransformComponent>(entity);
			if (std::get<1>(entity_type) == isSingleVel) {
				velocityComp = componentManager->getComponent<VelocityComponent>(entity);
				for (const auto& pair : multiTransComp->transforms) {
					transformationMutator(std::get<1>(pair).get(), velocityComp);
				}
				if (std::get<2>(entity_type) == hasCollider) {
					colliderComp = componentManager->getComponent<ColliderComponent>(entity);
					colliderMutator(colliderComp, velocityComp);
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
	_entities.clear();
}