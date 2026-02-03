#pragma once

#include "Game/Objects/Systems/Common/TextboxSystem.hpp"


TR::TextboxSystem::~TextboxSystem() {
	_textboxes.clear();
}

void TR::TextboxSystem::init(const Engine::EntityManager* entityManager, Engine::ComponentManager* componentManager) {
	const TextBoxComponent* textbox;

	const char* text;

	// Initialize the textboxes for each entity
	for (const auto& entity : entityManager->getEntities()) {
		if (componentManager->hasComponent<TextBoxComponent>(entity)) {
			textbox = componentManager->getComponent<TextBoxComponent>(entity);
			if (textbox) {
				_textboxes.emplace(entity, std::make_unique<TextBoxComponent>(*textbox));

				auto& _transform_comp = componentManager->addComponent<Engine::MultiTransformComponent>(entity);
				auto& _sprite_comp = componentManager->addComponent<Engine::MultiSpriteComponent>(entity);
				auto& _text_comp = componentManager->addComponent<Engine::MultiTextComponent>(entity);
				auto& _render_comp = componentManager->addComponent<Engine::RenderLayerComponent>(entity, Engine::RenderLayerComponent::FG);

				_transform_comp.transforms.emplace(0, std::make_shared<Engine::TransformComponent>(Engine::Vector2i{ textbox->_textbox_position }));
				_transform_comp.transforms.emplace(1, std::make_shared<Engine::TransformComponent>(Engine::Vector2i{ textbox->_textbox_position }));
				_transform_comp.transforms.emplace(2, std::make_shared<Engine::TransformComponent>(Engine::Vector2i{ textbox->_textbox_position + Engine::Vector2i(40,40) }));

				_sprite_comp.sprites.emplace(0, std::make_shared<Engine::SpriteComponent>(Engine::Recti(0, 0, 800, 400), Engine::Vector2i(800, 400), "TXT_BOX_BG"));
				_sprite_comp.sprites.emplace(1, std::make_shared<Engine::SpriteComponent>(Engine::Recti(0, 0, 800, 400), Engine::Vector2i(800, 400), "TXT_BOX_F"));

				((textbox->_textbox_flags & TextBoxComponent::TXT_COMPLETE) != TextBoxComponent::TXTBOX_NULL) ? text = textbox->_textbox_text.c_str() : text = "";

				_text_comp.text.emplace(2, std::make_shared<Engine::TextComponent>(text, 40, Engine::Vector4i(255, 255, 255, 255), Engine::Vector2i(740, 400)));

				_render_comp.layer = Engine::RenderLayerComponent::FG;
			}
		}
	}
}
void TR::TextboxSystem::updateRender(const Engine::EntityManager* entityManager, Engine::ComponentManager* componentManager) {

	Engine::TextComponent* _text_comp;

	for (const auto& [entity, textbox] : _textboxes) {
		_text_comp = componentManager->getComponent<Engine::MultiTextComponent>(entity)->text.at(2).get();
		if (textbox->dT % 20 == 0) {
			if ((textbox->_textbox_flags & TextBoxComponent::TXT_COMPLETE) == TextBoxComponent::TXTBOX_NULL) {
				std::string currentText = _text_comp->getText();
				if (currentText.size() < textbox->_textbox_text.size()) {
					currentText.append(textbox->_textbox_text, currentText.size(), 1);
					_text_comp->setText(currentText.c_str());
				}
				else {
					textbox->_textbox_flags |= TextBoxComponent::TXT_COMPLETE;
				}
			}
		}

		(textbox->dT >= 360) ? textbox->dT+= textbox->_textbox_speed : textbox->dT = 0;
	}
}

// Overloaded functions

void TR::TextboxSystem::create(const Engine::SystemContext& ctx) {
	if (!ctx.entityManager || !ctx.componentManager) {
		return;
	}
	else {
		init(ctx.entityManager, ctx.componentManager);
	}
}

void TR::TextboxSystem::update(const Engine::SystemContext& ctx) {
	if (!ctx.entityManager || !ctx.componentManager) {
		return;
	}
	else {
		updateRender(ctx.entityManager, ctx.componentManager);
	}
}

void TR::TextboxSystem::render(const Engine::SystemContext& ctx) {

}

void TR::TextboxSystem::quit(const Engine::SystemContext& ctx) {
	this->~TextboxSystem();
}