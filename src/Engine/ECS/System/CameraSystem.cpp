#pragma once
#include "Engine/ECS/System/CameraSystem.hpp"

void Engine::CameraSystem::initCamera(ComponentManager* componentManager) {
	auto* cameras = componentManager->allEntities<CameraComponent>();

	if (!cameras) {
		return;
	}

	if (_camera_entity == 0 || _camera_entity != *cameras->begin()) {
		_camera_entity = *cameras->begin();
		_current_camera = componentManager->getComponent<CameraComponent>(_camera_entity);

		InputComponent& input_comp = componentManager->addComponent<InputComponent>(_camera_entity);

		input_comp.newKey(SDL_SCANCODE_W);
		input_comp.newKey(SDL_SCANCODE_S);
		input_comp.newKey(SDL_SCANCODE_A);
		input_comp.newKey(SDL_SCANCODE_D);
	}

}

void Engine::CameraSystem::updateEntities(EntityManager* entityManager, ComponentManager* componentManager) {
	auto* cameras = componentManager->allEntities<CameraComponent>();

	if (!cameras) {
		_camera_entity = 0;
		_current_camera = nullptr;
		return;
	}

	if (_camera_entity != *cameras->begin()) {
		this->initCamera(componentManager);
	}

}

void Engine::CameraSystem::updateCamera(ComponentManager* componentManager) {
	if (!_camera_entity) {
		return;
	}

	if (componentManager->getComponent<InputComponent>(_camera_entity)->keyHeld(SDL_SCANCODE_W)) {
		_current_camera->position.position.y--;
	}
	else if (componentManager->getComponent<InputComponent>(_camera_entity)->keyHeld(SDL_SCANCODE_S)) {
		_current_camera->position.position.y++;
	}
	if (componentManager->getComponent<InputComponent>(_camera_entity)->keyHeld(SDL_SCANCODE_A)) {
		_current_camera->position.position.x--;
	}
	else if (componentManager->getComponent<InputComponent>(_camera_entity)->keyHeld(SDL_SCANCODE_D)) {
		_current_camera->position.position.x++;
	}
}

void Engine::CameraSystem::create(const SystemContext& ctx) {
	if (!ctx.componentManager) {
		return;
	}
	else {
		this->initCamera(ctx.componentManager);
	}
}

void Engine::CameraSystem::update(const SystemContext& ctx) {
	if (!ctx.entityManager || !ctx.componentManager) {
		return;
	}
	else {
		this->updateEntities(ctx.entityManager, ctx.componentManager);
		this->updateCamera(ctx.componentManager);
	}
}

void Engine::CameraSystem::render(const SystemContext& ctx) {}

void Engine::CameraSystem::quit(const SystemContext& ctx) {}