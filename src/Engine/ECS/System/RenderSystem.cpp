#pragma once

#include <algorithm>
#include "Engine/ECS/System/RenderSystem.hpp"

 

Engine::RenderSystem::~RenderSystem() {
	_sprite_set.clear();
}

void Engine::RenderSystem::initRender(ComponentManager* componentManager) {

	RenderComponent* render_data;
	
	const TransformComponent* position_data;
	const SpriteComponent* sprite_data;
	const TextComponent* text_data;

	const MultiTransformComponent* multi_position_data;
	const MultiSpriteComponent* multi_sprite_data;
	const MultiTextComponent* multi_text_data;

	RenderLayerComponent* layer_data;

	// Initializes any entities that are renderable targets
	

	// For single sprite objects
	if (const std::unordered_set<Entity>* transformComp = componentManager->allEntities<TransformComponent>()) {
		for (Entity entity : *transformComp) {
			if (componentManager->hasComponent<RenderComponent>(entity)) {
				continue;
			}
			position_data = componentManager->getComponent<TransformComponent>(entity);
			sprite_data = nullptr;
			text_data = nullptr;

			if (componentManager->hasComponent<TextComponent>(entity)) {
				text_data = componentManager->getComponent<TextComponent>(entity);
			}
			else if (componentManager->hasComponent<SpriteComponent>(entity)) {
				sprite_data = componentManager->getComponent<SpriteComponent>(entity);
			}
			else {
				componentManager->removeComponent<TransformComponent>(entity);
				continue;
			}

			if (componentManager->hasComponent<RenderLayerComponent>(entity)) {
				layer_data = componentManager->getComponent<RenderLayerComponent>(entity);
			}
			else {
				layer_data = &componentManager->addComponent<RenderLayerComponent>(entity, RenderLayerComponent::BG);
			}

			componentManager->addComponent<RenderComponent>(entity, layer_data, position_data, sprite_data, text_data);
		}
	}
	
	// For multi-sprite objects
	if (const std::unordered_set<Entity>* multitransComp = componentManager->allEntities<MultiTransformComponent>()) {
		for (Entity entity : *multitransComp) {
			if (componentManager->hasComponent<RenderComponent>(entity)) {
				continue;
			}
			multi_position_data = componentManager->getComponent<MultiTransformComponent>(entity);
			multi_sprite_data = nullptr;
			multi_text_data = nullptr;

			if (componentManager->hasComponent<MultiTextComponent>(entity)) {
				multi_text_data = componentManager->getComponent<MultiTextComponent>(entity);
			}
			if (componentManager->hasComponent<MultiSpriteComponent>(entity)) {
				multi_sprite_data = componentManager->getComponent<MultiSpriteComponent>(entity);
			}
			if (!multi_text_data && !multi_sprite_data) {
				componentManager->removeComponent<MultiTransformComponent>(entity);
				continue;
			}

			if (componentManager->hasComponent<RenderLayerComponent>(entity)) {
				layer_data = componentManager->getComponent<RenderLayerComponent>(entity);
			}
			else {
				layer_data = &componentManager->addComponent<RenderLayerComponent>(entity, RenderLayerComponent::BG);
			}

			componentManager->addComponent<RenderComponent>(entity, layer_data, multi_position_data, multi_sprite_data, multi_text_data);
		}
	}

	// Initialize the sprites for each renderable target
	if (auto* renderable_targets = componentManager->allEntities<RenderComponent>()) {
		for (const auto entity : *renderable_targets) {
			auto it = std::find_if(_sprite_set.begin(), _sprite_set.end(), [&](const auto& render) {
				return entity == render._ent;
				});
			if (it == _sprite_set.end()) {
				render_data = componentManager->getComponent<RenderComponent>(entity);
				std::vector<std::unique_ptr<Sprite>> sprites;
				sprite_data = render_data->_sprite_data;
				text_data = render_data->_text_data;
				multi_position_data = render_data->_multi_position_data;
				multi_sprite_data = render_data->_multi_sprite_data;
				multi_text_data = render_data->_multi_text_data;

				// Initialize single sprite entities
				if ((render_data->_flags & Render_Flags::isSingle) != Render_Flags::Null) {
					if ((render_data->_flags & Render_Flags::isSprite) != Render_Flags::Null) {
						sprites.emplace_back(std::make_unique<Sprite>(sprite_data->getResourceID(), sprite_data->getSize().x, sprite_data->getSize().y));
					}
					if ((render_data->_flags & Render_Flags::isText) != Render_Flags::Null) {
						sprites.emplace_back(std::make_unique<Text>(text_data->getText(), text_data->getTextSize()));
					}
				}
				// Initialize multi sprite entities
				else if ((render_data->_flags & Render_Flags::isMulti) != Render_Flags::Null) {
					for (auto& [_trID, _trData] : multi_position_data->transforms) {
						if ((render_data->_flags & Render_Flags::isSprite) != Render_Flags::Null) {
							for (auto& [_spID, _spData] : multi_sprite_data->sprites) {
								if (_spID == _trID) {
									sprites.emplace_back(std::make_unique<Sprite>(_spData->getResourceID(), _spData->getSize().x, _spData->getSize().y));
								}
							}
						}
						if ((render_data->_flags & Render_Flags::isText) != Render_Flags::Null) {
							for (auto& [_txID, _spData] : multi_text_data->text) {
								if (_txID == _trID) {
									sprites.emplace_back(std::make_unique<Text>(_spData->getText(), _spData->getTextSize()));
								}
							}
						}
					}
				}

				_sprite_set.emplace_back(RenderBody(entity, render_data, std::move(sprites)));
			}
		}
	}	

	if (!_camera) {
		if (auto* cameras = componentManager->allEntities<CameraComponent>()) {
			_camera = componentManager->getComponent<CameraComponent>(*cameras->begin());
		}
	}

}

void Engine::RenderSystem::updateEntities(EntityManager* entityManager, ComponentManager* componentManager) {
	// Updates current render data by erasing any entities that currently do not exist

	std::erase_if(_sprite_set, [&](const auto& item) {
		const auto& entity = item._ent;
		const auto& entMap = entityManager->getEntities();
		const auto it = std::find_if(entMap.begin(), entMap.end(), [&](const auto& pair) {
			return pair.second == entity;
			});
		return (it == entMap.end());
		});

	auto* trans = componentManager->allEntities<TransformComponent>();
	auto* multi = componentManager->allEntities<MultiTransformComponent>();

	if (!trans || !multi) {
		this->initRender(componentManager);
	}
	else if (_sprite_set.size() != (trans->size() + multi->size())) {
		this->initRender(componentManager);
	}
}

void Engine::RenderSystem::updateRender(const ComponentManager* componentManager,
	const AssetManager* assetManager, const Window* window) {

	// Transformation Update Lambda (Updates Position, Size, Rotation, and Source
	auto updateSpriteTransformation = [&](const TransformComponent* position_data, uint16_t layer,  auto& prevSprite) {
		TransformComponent position_data_prev;
		if (_camera) {
			position_data_prev = TransformComponent(prevSprite->getPosition() - _camera->position.position, prevSprite->getAngle(), prevSprite->getScale());
		}
		else {
			position_data_prev = TransformComponent(prevSprite->getPosition(), prevSprite->getAngle(), prevSprite->getScale());
		}
		Vector2i camera_pos = position_data_prev.position - prevSprite->getPosition();
		
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
		
		
		if (layer < RenderLayerComponent::HUD) {
			if (_camera) {
				if (camera_pos != _camera->position.position) {
					prevSprite->setPos(position_data->position + camera_pos);
				}
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
			if (prevSprite->getColor() != sprite_data->getColor()->rgb) {
				prevSprite->setColor(sprite_data->getColor()->rgb);
			}
			if (prevSprite->getAlpha() != sprite_data->getColor()->alpha) {
				prevSprite->setAlpha(sprite_data->getColor()->alpha);
			}
		}

		};

	// Text Update Lambda (Updates attributes when the object is a text object)
	auto updateTextData = [](const TextComponent* text_data, Text* prevText) {
		TextComponent text_data_prev(prevText->getText(), prevText->getTextSize(), prevText->getTextColor());

		if (text_data->getTextBounds() != Vector2i(0, 0)) {
			text_data_prev.setTextBounds(prevText->getSize());
		}

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
			if ((text_data->getTextBounds() != Vector2i(0, 0)) && (text_data->getTextBounds().x != prevText->getSize().x)) {
				prevText->setTextBounds(text_data->getTextBounds());
			}
			return true;
		}
		return false;

		};

	const TransformComponent* position_data;
	const SpriteComponent* sprite_data;
	const TextComponent* text_data;


	// Updates each individual renderable entity
	for (auto& renderTarget : _sprite_set) {
		auto entity = renderTarget._ent;
		auto imageType = renderTarget._render->_flags;

		if (renderTarget._layer != renderTarget._render->_layer_data->layer) {
			renderTarget._layer = renderTarget._render->_layer_data->layer;
		}

		if ((imageType & Render_Flags::isSingle) != Render_Flags::Null) {
			position_data = renderTarget._render->_position_data;

			updateSpriteTransformation(position_data, renderTarget._layer, renderTarget._sprite_set.at(0));
			auto prevSprite = renderTarget._sprite_set.at(0).get();

			if (auto* sprite = dynamic_cast<Text*>(prevSprite)) {
				text_data = renderTarget._render->_text_data;
				if (updateTextData(text_data, sprite)) {
					sprite->load(window->getRenderer(), "txtEnt" + std::to_string(entity), assetManager, sprite->getDestinationRect());
				}
			}
			else {
				sprite_data = renderTarget._render->_sprite_data;
				updateSpriteData(sprite_data, prevSprite);
			}

		}
		else if ((imageType & Render_Flags::isMulti) != Render_Flags::Null) {
			for (auto& [ind, data] : renderTarget._render->_multi_position_data->transforms) {

				updateSpriteTransformation(data.get(), renderTarget._layer, renderTarget._sprite_set.at(ind));

				auto prevSprite = renderTarget._sprite_set.at(ind).get();
				if (auto* sprite = dynamic_cast<Text*>(prevSprite)) {
					text_data = renderTarget._render->_multi_text_data->text.at(ind).get();
					if (updateTextData(text_data, sprite)) {
						sprite->load(window->getRenderer(), "txtEnt" + std::to_string(entity), assetManager, sprite->getDestinationRect());
					}
				}
				else {
					sprite_data = renderTarget._render->_multi_sprite_data->sprites.at(ind).get();
					updateSpriteData(sprite_data, prevSprite);
				}

			}
		}

	}

}

void Engine::RenderSystem::drawRender(const AssetManager* assetManager, const Window* window) {

	// Lambda for drawing sprites
	auto spriteRenderer = [&](const TransformComponent* position_data, const auto& _sprite_set) {
		if (position_data->centered) {
			for (auto& sprite : _sprite_set) {
				sprite->draw_center(window->getRenderer(), assetManager);
			}
		}
		else {
			for (auto& sprite : _sprite_set) {
				sprite->draw(window->getRenderer(), assetManager);
			}
		}
		return;
		};

	// Updates the current render targets
	const TransformComponent* position_data;

	// Sorts the render targets by layer order
	std::sort(_sprite_set.begin(), _sprite_set.end(),
		[](const RenderBody& a, const RenderBody& b) {
			int layerA = a._layer;
			int layerB = b._layer;
			if (layerA != layerB) {
				return layerA < layerB;
			}
			return a._ent < b._ent;
		});


	// Draws all of the render targets onto the screen
	for (const auto& renderTarget : _sprite_set) {
		auto entity = renderTarget._ent;
		auto imageType = renderTarget._render->_flags;

		if ((imageType & Render_Flags::isMulti) != Render_Flags::Null) {
			for (auto& pos_data : renderTarget._render->_multi_position_data->transforms) {
				position_data = pos_data.second.get();
				spriteRenderer(position_data, renderTarget._sprite_set);
			}
		}
		else {
			spriteRenderer(renderTarget._render->_position_data, renderTarget._sprite_set);
		}
	}
}



/// * System Overloaded Functions

void Engine::RenderSystem::create(const SystemContext& ctx) {
	if (!ctx.componentManager) {
		return;
	}
	else {
		this->initRender(ctx.componentManager);
	}
}

void Engine::RenderSystem::update(const SystemContext& ctx) {
	if (!ctx.entityManager || !ctx.componentManager) {
		return;
	}
	else {
		this->updateEntities(ctx.entityManager, ctx.componentManager);
	}
}

void Engine::RenderSystem::render(const SystemContext& ctx) {
	if (!ctx.assetManager || !ctx.componentManager || !ctx.window) {
		return;
	}
	else {
		this->updateRender(ctx.componentManager, ctx.assetManager, ctx.window);
		this->drawRender(ctx.assetManager, ctx.window);
	}
}

void Engine::RenderSystem::quit(const SystemContext& ctx) {
	_sprite_set.clear();
}