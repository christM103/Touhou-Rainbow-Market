#pragma once
#include <algorithm>
#include "Engine/ECS/System/CollisionSystem.hpp"


void Engine::CollisionSystem::initCollision(ComponentManager* componentManager) {
	auto* entities = componentManager->allEntities<ColliderComponent>();
	ColliderComponent* colliderComp;

	if (!entities) {
		return;
	}

	for (auto& entity : *entities) {
		colliderComp = componentManager->getComponent<ColliderComponent>(entity);
		if (std::find(_collision_entities.begin(), _collision_entities.end(), std::make_pair(entity, colliderComp)) == _collision_entities.end()) {
			_collision_entities.push_back({ entity, colliderComp });
		}
	}
}

void Engine::CollisionSystem::updateEntities(EntityManager* entityManager, ComponentManager* componentManager) {
	size_t entity_size;

	if (auto set = componentManager->allEntities<ColliderComponent>()) {
		entity_size = set->size();
	}
	else {
		entity_size = 0;
	}

	std::erase_if(_collision_entities, [&](const auto& item) {
		const auto& [entity, data] = item;
		const auto& entMap = entityManager->getEntities();
		const auto it = std::find_if(entMap.begin(), entMap.end(), [&](const auto& pair) {
			return pair.second == entity;
			});
		return (it == entMap.end());
		});

	if (entity_size != _collision_entities.size()) {
		this->initCollision(componentManager);
	}
}

void Engine::CollisionSystem::updatePosition(ComponentManager* componentManager) {
	Vector2f newOffset;
	VelocityComponent* velocity_component;
	auto cameras = componentManager->allEntities<CameraComponent>();
	CameraComponent* camera_component;


	if (cameras) {
		camera_component = componentManager->getComponent<CameraComponent>(*cameras->begin());
		newOffset = Vector2f(static_cast<float>(camera_component->position.position.x), static_cast<float>(camera_component->position.position.y));
	}

	for (const auto& [entity, data] : _collision_entities) {
		velocity_component = componentManager->getComponent<VelocityComponent>(entity);
		if (velocity_component != nullptr) {
			data->bounds.position += velocity_component->linear;
		}
		if (newOffset != Vector2f()) {
			data->offset = newOffset;
		}

	}
}

void Engine::CollisionSystem::updateCollision(ComponentManager* componentManager) {
	Rectf currentRect;
	MouseComponent* mouse;
	auto mouses = componentManager->allEntities<MouseComponent>();

	if (mouses) {
		mouse = componentManager->getComponent<MouseComponent>(*mouses->begin());
	}
	else {
		mouse = nullptr;
	}

	for (auto& [entity, data] : _collision_entities) {
		currentRect = Rectf(data->bounds.position - data->offset, data->bounds.size);
		if (((data->flags & ColliderComponent::trackMouse) != ColliderComponent::Null) && (mouse != nullptr)) {
			if (currentRect.contains(Vector2f(static_cast<float>(mouse->position->x), static_cast<float>(mouse->position->y)))) {
				data->flags &= ~ColliderComponent::mousePressed;
				data->flags &= ~ColliderComponent::mouseHeld;
				data->flags &= ~ColliderComponent::mouseReleased;
				data->flags &= ~ColliderComponent::mouseHovered;

				if (mouse->leftPressed()) {
					data->flags |= ColliderComponent::mousePressed;
				}
				else if (mouse->leftHeld()) {
					data->flags |= ColliderComponent::mouseHeld;
				}
				else if (mouse->leftReleased()) {
					data->flags |= ColliderComponent::mouseReleased;
				}
				else {
					data->flags |= ColliderComponent::mouseHovered;
				}
			}
		}
	}
}

// Overloaded functions

void Engine::CollisionSystem::create(const SystemContext& ctx) {
	if (!ctx.componentManager) {
		return;
	}
	else {
		this->initCollision(ctx.componentManager);
	}
}

void Engine::CollisionSystem::update(const SystemContext& ctx) {
	if (!ctx.entityManager || !ctx.componentManager) {
		return;
	}
	else {
		this->updateEntities(ctx.entityManager, ctx.componentManager);
		this->updatePosition(ctx.componentManager);
		this->updateCollision(ctx.componentManager);
	}
}

void Engine::CollisionSystem::render(const SystemContext& ctx) {}

void Engine::CollisionSystem::quit(const SystemContext& ctx) {
	_collision_entities.clear();
}