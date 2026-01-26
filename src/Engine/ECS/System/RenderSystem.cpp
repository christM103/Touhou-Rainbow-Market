#pragma once

#include <algorithm>
#include "Engine/ECS/System/RenderSystem.hpp"



Engine::RenderSystem::~RenderSystem() {
	_sprite_set.clear();
	_text_set.clear();
	_render_targets.clear();
}

void Engine::RenderSystem::init(const EntityManager* entityManager, const ComponentManager* componentManager, 
	const AssetManager* assetManager, const Window* window) {
	const TransformComponent* position_data;
	const SpriteComponent* sprite_data;
	const TextComponent* text_data;

	uint16_t layer;

	// Initializes any entities that are renderable targets
	for (Entity entity : entityManager->getEntities()) {
		if ((_sprite_set.find(entity) == _sprite_set.end()) && (_text_set.find(entity) == _text_set.end())) {
			if (componentManager->hasComponent<TransformComponent>(entity)) {
				if (componentManager->hasComponent<RenderLayerComponent>(entity)) {
					layer = componentManager->getComponent<RenderLayerComponent>(entity)->layer;
				}
				else {
					layer = RenderLayerComponent::BG;
				}

				if (componentManager->hasComponent<TextComponent>(entity)) {
					_render_targets.push_back({ entity, isText::value, layer });
				}
				else if (componentManager->hasComponent<SpriteComponent>(entity)) {
					_render_targets.push_back({ entity, isSprite::value, layer });
				}

			}
		}
	}

	// Initialize the sprites for each renderable target
	for (const auto& renderTarget : _render_targets) {
		auto entity = std::get<0>(renderTarget);
		auto imageType = std::get<1>(renderTarget);
		position_data = componentManager->getComponent<TransformComponent>(entity);

		if ((_sprite_set.find(entity) == _sprite_set.end()) && (_text_set.find(entity) == _text_set.end())) {
			if (imageType == isSprite::value) {
				sprite_data = componentManager->getComponent<SpriteComponent>(entity);
				_sprite_set.insert({ entity,
					std::make_unique<Sprite>(assetManager->getTexture(sprite_data->getResourceID()),
						sprite_data->getSize().x, sprite_data->getSize().y) });
			}
			else if (imageType == isText::value) {
				text_data = componentManager->getComponent<TextComponent>(entity);
				_text_set.insert({ entity,
					std::make_unique<Text>(text_data->getText(), text_data->getTextSize()) });
			}
		}
	}

	this->update(entityManager, componentManager, assetManager, window);

}


void Engine::RenderSystem::draw(const EntityManager* entityManager, const ComponentManager* componentManager,
	const AssetManager* assetManager, const Window* window) {

	// Updates the current render targets
	this->update(entityManager, componentManager, assetManager, window);
	const TransformComponent* position_data;

	// Sorts the render targets by layer order
	std::sort(_render_targets.begin(), _render_targets.end(),
		[](const RenderTarget& a, const RenderTarget& b) {
			int layerA = std::get<2>(a);
			int layerB = std::get<2>(b);
			if (layerA != layerB) {
				return layerA < layerB;
			}
			return std::get<0>(a) < std::get<0>(b);
		});

	for (const auto& renderTarget : _render_targets) {
		auto entity = std::get<0>(renderTarget);
		auto imageType = std::get<1>(renderTarget);

		position_data = componentManager->getComponent<TransformComponent>(entity);

		if (position_data->centered) {
			if (imageType == isSprite::value) {
				_sprite_set.at(entity)->draw_center(window->getRenderer());
			}
			else if (imageType == isText::value) {
				_text_set.at(entity)->draw_center(window->getRenderer());
			}
		}
		else {
			if (imageType == isSprite::value) {
				_sprite_set.at(entity)->draw(window->getRenderer());
			}
			else if (imageType == isText::value) {
				_text_set.at(entity)->draw(window->getRenderer());
			}
		}
		
	}

}

void Engine::RenderSystem::update(const EntityManager* entityManager, const ComponentManager* componentManager,
	const AssetManager* assetManager, const Window* window) {

	// Transformation Update Lambda (Updates Position, Size, Rotation, and Source
	auto updateSpriteTransformation = [](Entity entity, auto& sprite_map, const ComponentManager * componentManager,
		const TransformComponent * position_data) {

		auto prevSprite = sprite_map.find(entity)->second.get();

		TransformComponent position_data_prev(prevSprite->getPosition(), prevSprite->getAngle(), prevSprite->getScale());

		if (*position_data != position_data_prev) {
			if (position_data->position != position_data_prev.position) {
				prevSprite->setPos(position_data->position);
			}
			if (position_data->rotation != position_data_prev.rotation) {
				prevSprite->setAngle(position_data->rotation);
			}
			if (position_data->scale != position_data_prev.scale) {
				prevSprite->setScale(position_data->scale);
			}	
		}

		return prevSprite;
	};

	const TransformComponent* position_data;
	const SpriteComponent* sprite_data;
	const TextComponent* text_data;

	// Updates current render data by erasing any entities/components that currently do not exist
	std::erase_if(_sprite_set, [&](const auto& item) {
		const Entity& entity = std::get<0>(item);
		return entityManager->getEntities().find(entity) == entityManager->getEntities().end() && !componentManager->hasComponent<SpriteComponent>(entity);
		});

	std::erase_if(_text_set, [&](const auto& item) {
		const Entity& entity = std::get<0>(item);
		return entityManager->getEntities().find(entity) == entityManager->getEntities().end() && !componentManager->hasComponent<TextComponent>(entity);
		});

	std::erase_if(_render_targets, [&](const auto& item) {
		const Entity& entity = std::get<0>(item);
		return entityManager->getEntities().find(entity) == entityManager->getEntities().end();
		});

	// Updates each individual renderable entity
	for (const auto& renderTarget : _render_targets) {
		auto entity = std::get<0>(renderTarget);
		auto imageType = std::get<1>(renderTarget);

		position_data = componentManager->getComponent<TransformComponent>(entity);

		if (imageType == isSprite::value) {
			// Updates attributes when the object is a sprite
			auto prevSprite = updateSpriteTransformation(entity, _sprite_set, componentManager, position_data);
			sprite_data = componentManager->getComponent<SpriteComponent>(entity);

			SpriteComponent sprite_data_prev(Recti(prevSprite->getPositionCrop(), prevSprite->getSizeCrop()), prevSprite->getSize(), "");

			if (*sprite_data != sprite_data_prev) {
				if (sprite_data->getSize() != sprite_data_prev.getSize()) {
					prevSprite->setSize(sprite_data->getSize());
				}
				if ((sprite_data->getSourceRect().size != sprite_data_prev.getSourceRect().size)
					|| (sprite_data->getSourceRect().position != sprite_data_prev.getSourceRect().position)) {
					prevSprite->setSourceRect(sprite_data->getSourceRect());
				}
				if (prevSprite->getTexture() != assetManager->getTexture(sprite_data->getResourceID())) {
					prevSprite->swapTexture(assetManager->getTexture(sprite_data->getResourceID()),
						prevSprite->getWidth(), prevSprite->getHeight());
				}
			}
			

		}
		else if (imageType == isText::value) {
			// Updates attributes when the object is a text object
			auto prevText = updateSpriteTransformation(entity, _text_set, componentManager, position_data);
			text_data = componentManager->getComponent<TextComponent>(entity);

			TextComponent text_data_prev(prevText->getText(), prevText->getTextSize(), prevText->getTextColor());

			if (*text_data != text_data_prev) {
				if (text_data->getText() != text_data_prev.getText()) {
					prevText->setText(text_data->getText());
				}
				if (text_data->getTextSize() != text_data_prev.getTextSize()) {
					prevText->setTextSize(text_data->getTextSize());
				}
				if (text_data->getTextColor() != text_data_prev.getTextColor()) {
					prevText->setColor(text_data->getTextColor());
				}
				prevText->load(window->getRenderer(), prevText->getDestinationRect());
			}

		}
	}

}

/// * System Overloaded Functions

void Engine::RenderSystem::create(const SystemContext& ctx) {
	if (!ctx.entityManager || !ctx.assetManager || !ctx.componentManager || !ctx.window) {
		return;
	}
	else {
		this->init(ctx.entityManager, ctx.componentManager, ctx.assetManager, ctx.window);
	}
}

void Engine::RenderSystem::update(const SystemContext& ctx) {
	if (!ctx.entityManager || !ctx.assetManager || !ctx.componentManager || !ctx.window) {
		return;
	}
	else {
		this->init(ctx.entityManager, ctx.componentManager, ctx.assetManager, ctx.window);
	}
}

void Engine::RenderSystem::render(const SystemContext& ctx) {
	if (!ctx.entityManager || !ctx.assetManager || !ctx.componentManager || !ctx.window) {
		return;
	}
	else {
		this->draw(ctx.entityManager, ctx.componentManager, ctx.assetManager, ctx.window);
	}
}

void Engine::RenderSystem::quit(const SystemContext& ctx) {
	this->~RenderSystem();
}