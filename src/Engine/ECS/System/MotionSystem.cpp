#pragma once

#include "Engine/ECS/System/MotionSystem.hpp"



void Engine::MotionSystem::initMotion(const EntityManager* entityManager, ComponentManager* componentManager) {
	TransType trans;
	VelType vel;
	ColType col;
	AccelType accel;
	std::unordered_set<Entity> totalEntites;

	if (auto* velocities = componentManager->allEntities<VelocityComponent>()) {
		totalEntites.insert(velocities->begin(), velocities->end());
	}
	if (auto* multivelocities = componentManager->allEntities<MultiVelocityComponent>()) {
		totalEntites.insert(multivelocities->begin(), multivelocities->end());
	}
	if (auto* accelerations = componentManager->allEntities<AccelerationComponent>()) {
		totalEntites.insert(accelerations->begin(), accelerations->end());
	}
	if (auto* multiaccelerations = componentManager->allEntities<MultiAccelerationComponent>()) {
		totalEntites.insert(multiaccelerations->begin(), multiaccelerations->end());
	}

	for (const auto& entity : totalEntites) {
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
				if (componentManager->hasComponent<AccelerationComponent>(entity)) {
					accel = isSingleAccel;
				}
				else {
					accel = noAccel;
				}
				vel = isSingleVel;
			}
			else if (componentManager->hasComponent<MultiVelocityComponent>(entity)) {
				if (componentManager->hasComponent<AccelerationComponent>(entity)) {
					accel = isMultiAccel;
				}
				else {
					accel = noAccel;
				}
				vel = isMultiVel;
			}
			else {
				continue;
			}

			_entities.emplace(entity, MotionObject(trans, vel, accel, col));
		}
	}

}

void Engine::MotionSystem::updateEntities(EntityManager* entityManager, ComponentManager* componentManager) {
	std::erase_if(_entities, [&](const auto& item) {
		const auto& [entity, data] = item;
		const auto& entMap = entityManager->getEntities();
		const auto it = std::find_if(entMap.begin(), entMap.end(), [&](const auto& pair) {
			return pair.second == entity;
			});
		return (it == entMap.end());
		});

	auto* velEntities = componentManager->allEntities<VelocityComponent>();
	auto* multiVelEntities = componentManager->allEntities<MultiVelocityComponent>();

	size_t totalEntities = 0;

	if (velEntities) {
		totalEntities += velEntities->size();
	}

	if (multiVelEntities) {
		totalEntities += multiVelEntities->size();
	}

	if (_entities.size() != totalEntities) {
		this->initMotion(entityManager, componentManager);
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

	for (const auto& [entity, entity_type] : _entities) {
		if (entity_type.transformationType == isSingleTrans) {
			transformComp = componentManager->getComponent<TransformComponent>(entity);
			if (entity_type.velocityType == isSingleVel) {
				velocityComp = componentManager->getComponent<VelocityComponent>(entity);
				transformationMutator(transformComp, velocityComp);
				if (entity_type.colliderType == hasCollider) {
					colliderComp = componentManager->getComponent<ColliderComponent>(entity);
					colliderMutator(colliderComp, velocityComp);
				}
			}
		}
		else {
			multiTransComp = componentManager->getComponent<MultiTransformComponent>(entity);
			if (entity_type.velocityType == isSingleVel) {
				velocityComp = componentManager->getComponent<VelocityComponent>(entity);
				for (const auto& pair : multiTransComp->transforms) {
					transformationMutator(std::get<1>(pair).get(), velocityComp);
				}
				if (entity_type.colliderType == hasCollider) {
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
		this->initMotion(ctx.entityManager, ctx.componentManager);
	}
}

void Engine::MotionSystem::update(const SystemContext& ctx) {
	if (!ctx.entityManager || !ctx.componentManager) {
		return;
	}
	else {
		this->updateEntities(ctx.entityManager, ctx.componentManager);
		this->movementUpdate(ctx.entityManager, ctx.componentManager);
	}
}

void Engine::MotionSystem::render(const SystemContext& ctx) {

}

void Engine::MotionSystem::quit(const SystemContext& ctx) {
	_entities.clear();
}