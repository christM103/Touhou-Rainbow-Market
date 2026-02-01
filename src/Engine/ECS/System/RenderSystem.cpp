#pragma once

#include <algorithm>
#include "Engine/ECS/System/RenderSystem.hpp"

 

Engine::RenderSystem::~RenderSystem() {
	_multi_sprite_set.clear();
	_render_targets.clear();
}

void Engine::RenderSystem::init(const EntityManager* entityManager, const ComponentManager* componentManager, 
	const AssetManager* assetManager, const Window* window) {
	const TransformComponent* position_data;
	const SpriteComponent* sprite_data;
	const TextComponent* text_data;

	const MultiTransformComponent* multi_position_data;
	const MultiSpriteComponent* multi_sprite_data;
	const MultiTextComponent* multi_text_data;

	uint16_t layer;
	Render_Flags renderflags;

	// Initializes any entities that are renderable targets
	for (Entity entity : entityManager->getEntities()) {
		if (_multi_sprite_set.find(entity) == _multi_sprite_set.end()) {

			renderflags = Render_Flags::Null;

			// Manages the drawing layer of the entity
			if (componentManager->hasComponent<RenderLayerComponent>(entity)) {
				layer = componentManager->getComponent<RenderLayerComponent>(entity)->layer;
			}
			else {
				layer = RenderLayerComponent::BG;
			}

			// Manage the render flags of the object
			if (componentManager->hasComponent<TransformComponent>(entity)) {
				renderflags |= Render_Flags::isSingle;
				if (componentManager->hasComponent<TextComponent>(entity)) {
					renderflags |= Render_Flags::isText;
				}
				else if (componentManager->hasComponent<SpriteComponent>(entity)) {
					renderflags |= Render_Flags::isSprite;
				}
			}
			else if (componentManager->hasComponent<MultiTransformComponent>(entity)) {
				renderflags |= Render_Flags::isMulti;
				if (componentManager->hasComponent<MultiTextComponent>(entity)) {
					renderflags |= Render_Flags::isText;
				}
				else if (componentManager->hasComponent<MultiSpriteComponent>(entity)) {
					renderflags |= Render_Flags::isSprite;
				}
			}

			// Allow the object to be a render object ONLY with a valid render flag
			if (((renderflags & Render_Flags::isSprite) != Render_Flags::Null) || ((renderflags & Render_Flags::isText) != Render_Flags::Null)) {
				_render_targets.push_back({ entity, renderflags, layer });
			}
		}
	}

	// Initialize the sprites for each renderable target
	for (const auto& renderTarget : _render_targets) {
		auto entity = std::get<0>(renderTarget);
		auto imageType = std::get<1>(renderTarget);

		if (_multi_sprite_set.find(entity) == _multi_sprite_set.end()) {
			if ((imageType & Render_Flags::isSingle) != Render_Flags::Null) {
				position_data = componentManager->getComponent<TransformComponent>(entity);
				if ((imageType & Render_Flags::isSprite) != Render_Flags::Null) {
					sprite_data = componentManager->getComponent<SpriteComponent>(entity);
					std::vector<std::unique_ptr<Sprite>> tempV;
					tempV.emplace_back(std::make_unique<Sprite>(sprite_data->getResourceID(), sprite_data->getSize().x, sprite_data->getSize().y));
					_multi_sprite_set.emplace( entity, std::move(tempV) );
				}
				if ((imageType & Render_Flags::isText) != Render_Flags::Null) {
					text_data = componentManager->getComponent<TextComponent>(entity);
					std::vector<std::unique_ptr<Sprite>> tempV;
					tempV.emplace_back(std::make_unique<Text>(text_data->getText(), text_data->getTextSize()));
					_multi_sprite_set.emplace( entity, std::move(tempV) );
				}
			}
			else if ((imageType & Render_Flags::isMulti) != Render_Flags::Null) {
				multi_position_data = componentManager->getComponent<MultiTransformComponent>(entity);
				_multi_sprite_set.try_emplace(entity);
				for (auto& transformComp : multi_position_data->transforms) {
					if ((imageType & Render_Flags::isSprite) != Render_Flags::Null) {
						multi_sprite_data = componentManager->getComponent<MultiSpriteComponent>(entity);
						for (auto& spriteComp : multi_sprite_data->sprites) {
							if (spriteComp.first == transformComp.first) {
								_multi_sprite_set[entity].emplace_back(
									std::make_unique<Sprite>(spriteComp.second->getResourceID(), spriteComp.second->getSize().x, spriteComp.second->getSize().y));
							}
						}
					}
					if ((imageType & Render_Flags::isText) != Render_Flags::Null) {
						multi_text_data = componentManager->getComponent<MultiTextComponent>(entity);
						for (auto& spriteComp : multi_text_data->text) {
							if (spriteComp.first == transformComp.first) {
								_multi_sprite_set[entity].emplace_back(std::make_unique<Text>(spriteComp.second->getText(), spriteComp.second->getTextSize()));
							}
						}
					}
				}
			}
		}
		
	}

	// Update all the newly created render entity assets
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


	// Draws all of the render targets onto the screen
	for (const auto& renderTarget : _render_targets) {
		auto entity = std::get<0>(renderTarget);
		auto imageType = std::get<1>(renderTarget);

		if ((imageType & Render_Flags::isMulti) != Render_Flags::Null) {
			for (auto& pos_data : componentManager->getComponent<MultiTransformComponent>(entity)->transforms) {
				position_data = pos_data.second.get();
				if (position_data->centered) {
					for (auto& sprite : _multi_sprite_set.at(entity)) {
						sprite->draw_center(window->getRenderer(), assetManager);
					}
				}
				else {
					for (auto& sprite : _multi_sprite_set.at(entity)) {
						sprite->draw(window->getRenderer(), assetManager);
					}
				}
			}
		}
		else {
			position_data = componentManager->getComponent<TransformComponent>(entity);
			if (position_data->centered) {
				for (auto& sprite : _multi_sprite_set.at(entity)) {
					sprite->draw_center(window->getRenderer(), assetManager);
				}
			}
			else {
				for (auto& sprite : _multi_sprite_set.at(entity)) {
					sprite->draw(window->getRenderer(), assetManager);
				}
			}
		}
		
	}
}

void Engine::RenderSystem::update(const EntityManager* entityManager, const ComponentManager* componentManager,
	const AssetManager* assetManager, const Window* window) {

	// Transformation Update Lambda (Updates Position, Size, Rotation, and Source
	auto updateSpriteTransformation = [](const TransformComponent * position_data, auto& prevSprite) {
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

	};

	// Sprite Update Lambda (Updates attributes when the object is a sprite)
	auto updateSpriteData = [](const SpriteComponent* sprite_data, Sprite* prevSprite) {
		SpriteComponent sprite_data_prev(Recti(prevSprite->getPositionCrop(), prevSprite->getSizeCrop()), prevSprite->getSize(), "");
		if (*sprite_data != sprite_data_prev) {
			if (sprite_data->getSize() != sprite_data_prev.getSize()) {
				prevSprite->setSize(sprite_data->getSize());
			}
			if ((sprite_data->getSourceRect().size != sprite_data_prev.getSourceRect().size)
				|| (sprite_data->getSourceRect().position != sprite_data_prev.getSourceRect().position)) {
				prevSprite->setSourceRect(sprite_data->getSourceRect());
			}
			if (prevSprite->getTexture() != sprite_data->getResourceID()) {
				prevSprite->swapTexture(sprite_data->getResourceID(),
					prevSprite->getWidth(), prevSprite->getHeight());
			}
		}

	};

	// Text Update Lambda (Updates attributes when the object is a text object)
	auto updateTextData = [](const TextComponent* text_data, Text* prevText) {
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
		}

	};

	const TransformComponent* position_data;
	const SpriteComponent* sprite_data;
	const TextComponent* text_data;

	// Updates current render data by erasing any entities/components that currently do not exist

	std::erase_if(_render_targets, [&](const auto& item) {
		const Entity& entity = std::get<0>(item);
		return entityManager->getEntities().find(entity) == entityManager->getEntities().end();
		});

	std::erase_if(_multi_sprite_set, [&](const auto& item) {
		const Entity& entity = std::get<0>(item);
		return entityManager->getEntities().find(entity) == entityManager->getEntities().end()
			&& !componentManager->hasComponent<TextComponent>(entity) && !componentManager->hasComponent<SpriteComponent>(entity)
			&& !componentManager->hasComponent<MultiTextComponent>(entity) && !componentManager->hasComponent<MultiSpriteComponent>(entity);
		});


	// Updates each individual renderable entity
	for (const auto& renderTarget : _render_targets) {
		auto entity = std::get<0>(renderTarget);
		auto imageType = std::get<1>(renderTarget);

		if (static_cast<uint8_t>(imageType & Render_Flags::isSingle)) {
			position_data = componentManager->getComponent<TransformComponent>(entity);

			updateSpriteTransformation(position_data, _multi_sprite_set[entity].at(0));
			auto prevSprite = _multi_sprite_set[entity].at(0).get();

			if (auto* sprite = dynamic_cast<Text*>(prevSprite)) {
				text_data = componentManager->getComponent<TextComponent>(entity);
				updateTextData(text_data, sprite);
				sprite->load(window->getRenderer(), "txtEnt" + std::to_string(entity), assetManager, sprite->getDestinationRect());
			}
			else {
				sprite_data = componentManager->getComponent<SpriteComponent>(entity);
				updateSpriteData(sprite_data, prevSprite);
			}

		}
		else if (static_cast<uint8_t>(imageType & Render_Flags::isMulti)) {
			for (uint8_t ind = 0; ind < _multi_sprite_set[entity].size(); ind++) {
				position_data = componentManager->getComponent<MultiTransformComponent>(entity)->transforms.at(ind).get();
				updateSpriteTransformation(position_data, _multi_sprite_set[entity].at(ind));

				auto prevSprite = _multi_sprite_set[entity].at(ind).get();
				if (auto* sprite = dynamic_cast<Text*>(prevSprite)) {
					text_data = componentManager->getComponent<MultiTextComponent>(entity)->text.at(ind).get();
					updateTextData(text_data, sprite);
					sprite->load(window->getRenderer(), "txtEnt" + std::to_string(entity), assetManager, sprite->getDestinationRect());
				}
				else {
					sprite_data = componentManager->getComponent<MultiSpriteComponent>(entity)->sprites.at(ind).get();
					updateSpriteData(sprite_data, prevSprite);
				}

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