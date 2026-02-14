#pragma once

#include <SDL2/SDL_ttf.h>

#include "Game/Objects/Systems/Common/TextboxSystem.hpp"


TR::TextboxSystem::~TextboxSystem() {
	_textboxes.clear();
}

void TR::TextboxSystem::init(const Engine::EntityManager* entityManager, Engine::ComponentManager* componentManager, Engine::Window* windowManager) {
	const auto* entities = componentManager->allEntities<TextBoxComponent>();
	TextBoxComponent* textbox;

	const char* text;
	Engine::Vector2i position;

	// Initialize the textboxes for each entity
	for (const auto& entity : *entities) {
		if (_textboxes.find(entity) == _textboxes.end()) {
			textbox = componentManager->getComponent<TextBoxComponent>(entity);
			if (textbox && _textboxes.try_emplace(entity, std::make_unique<TextBoxComponent>(*textbox)).second) {

				auto& _transform_comp = componentManager->addComponent<Engine::MultiTransformComponent>(entity);
				auto& _velocity_comp = componentManager->addComponent<Engine::VelocityComponent>(entity, Engine::Vector2f(0,0));
				auto& _sprite_comp = componentManager->addComponent<Engine::MultiSpriteComponent>(entity);
				auto& _text_comp = componentManager->addComponent<Engine::MultiTextComponent>(entity);
				auto& _render_comp = componentManager->addComponent<Engine::RenderLayerComponent>(entity, Engine::RenderLayerComponent::FG);
				auto& _input_comp = componentManager->addComponent<Engine::InputComponent>(entity);
				auto& _mouse_comp = componentManager->addComponent<Engine::MouseComponent>(entity);

				position = textbox->_textbox_position;
				if ((textbox->_textbox_flags & TextBoxComponent::ENTER) != TextBoxComponent::TXTBOX_NULL) {
					if ((textbox->_textbox_flags & TextBoxComponent::TRANSITION_LEFT) != TextBoxComponent::TXTBOX_NULL) {
						position.x = windowManager->getWidth();
					}
					else if ((textbox->_textbox_flags & TextBoxComponent::TRANSITION_RIGHT) != TextBoxComponent::TXTBOX_NULL) {
						position.x = -800;
					}

					if ((textbox->_textbox_flags & TextBoxComponent::TRANSITION_UP) != TextBoxComponent::TXTBOX_NULL) {
						position.y = windowManager->getHeight();
					}
					else if ((textbox->_textbox_flags & TextBoxComponent::TRANSITION_DOWN) != TextBoxComponent::TXTBOX_NULL) {
						position.y = -400;
					}
				}

				_transform_comp.transforms.emplace(0, std::make_shared<Engine::TransformComponent>(position));
				_transform_comp.transforms.emplace(1, std::make_shared<Engine::TransformComponent>(position));
				_transform_comp.transforms.emplace(2, std::make_shared<Engine::TransformComponent>((position + Engine::Vector2i(40, 40))));

				_sprite_comp.sprites.emplace(0, std::make_shared<Engine::SpriteComponent>(Engine::Recti(0, 0, 800, 400), Engine::Vector2i(800, 400), "TXT_BOX_BG"));
				_sprite_comp.sprites.emplace(1, std::make_shared<Engine::SpriteComponent>(Engine::Recti(0, 0, 800, 400), Engine::Vector2i(800, 400), "TXT_BOX_F"));

				((textbox->_textbox_flags & TextBoxComponent::TXT_COMPLETE) != TextBoxComponent::TXTBOX_NULL) ? text = textbox->_textbox_text.c_str() : text = "";

				_textboxes.at(entity)->_textbox_text = textFormatting("assets/fonts/ArialMdm.ttf", 40, textbox->_textbox_text);

				_text_comp.text.emplace(2, std::make_shared<Engine::TextComponent>(text, 40, Engine::Vector4i(255, 255, 255, 255), Engine::Vector2i(730, 400)));

				_render_comp.layer = Engine::RenderLayerComponent::FG;

				_input_comp.newKey(SDL_SCANCODE_SPACE);
			}
		}
	}
}
void TR::TextboxSystem::updateRender(const Engine::EntityManager* entityManager, Engine::ComponentManager* componentManager, Engine::Window* windowManager) {
	Engine::TextComponent* _text_comp;

	std::erase_if(_textboxes, [&](const auto& item) {
		const auto& [entity, component] = item;
		const auto& entMap = entityManager->getEntities();
		const auto it = std::find_if(entMap.begin(), entMap.end(), [&](const auto& pair) {
			return pair.second == entity;
			});
		return (it == entMap.end());
		});


	this->init(entityManager, componentManager, windowManager);
	for (const auto& [entity, textbox] : _textboxes) {
		_text_comp = componentManager->getComponent<Engine::MultiTextComponent>(entity)->text.at(2).get();
		if ((textbox->_textbox_flags & TextBoxComponent::ENTER) != TextBoxComponent::TXTBOX_NULL) {
			float hor = 0.0, vert = 0.0;
			auto& _transform_comp = componentManager->getComponent<Engine::MultiTransformComponent>(entity)->transforms.at(0);

			if ((textbox->_textbox_flags & TextBoxComponent::TRANSITION_LEFT) != TextBoxComponent::TXTBOX_NULL) {
				hor = -4.0;
				if (_transform_comp->position.x + hor < textbox->_textbox_position.x) {
					hor = 0.0;
				}
			}
			else if ((textbox->_textbox_flags & TextBoxComponent::TRANSITION_RIGHT) != TextBoxComponent::TXTBOX_NULL) {
				hor = 4.0;
				if (_transform_comp->position.x + hor > textbox->_textbox_position.x) {
					hor = 0.0;
				}
			}
			else {
				hor = 0.0;
			}

			if ((textbox->_textbox_flags & TextBoxComponent::TRANSITION_UP) != TextBoxComponent::TXTBOX_NULL) {
				vert = -4.0;
				if (_transform_comp->position.y + vert < textbox->_textbox_position.y) {
					vert = 0.0;
				}
			}
			else if ((textbox->_textbox_flags & TextBoxComponent::TRANSITION_DOWN) != TextBoxComponent::TXTBOX_NULL) {
				vert = 4.0;
				if (_transform_comp->position.y + vert > textbox->_textbox_position.y) {
					vert = 0.0;
				}
			}
			else {
				vert = 0.0;
			}

			if ((hor == 0.0) && (vert == 0.0)) {
				textbox->_textbox_flags ^= TextBoxComponent::ENTER;
			}

			componentManager->addComponent<Engine::VelocityComponent>(entity, Engine::Vector2f(hor, vert));
		} 
		else if ((textbox->_textbox_flags & TextBoxComponent::EXIT) != TextBoxComponent::TXTBOX_NULL) {
			float hor = 0.0, vert = 0.0;
			auto& _transform_comp = componentManager->getComponent<Engine::MultiTransformComponent>(entity)->transforms.at(0);

			if ((textbox->_textbox_flags & TextBoxComponent::TRANSITION_LEFT) != TextBoxComponent::TXTBOX_NULL) {
				hor = -4.0;
				if (_transform_comp->position.x + hor < -800) {
					hor = 0.0;
				}
			}
			else if ((textbox->_textbox_flags & TextBoxComponent::TRANSITION_RIGHT) != TextBoxComponent::TXTBOX_NULL) {
				hor = 4.0;
				if (_transform_comp->position.x + hor > windowManager->getWidth()) {
					hor = 0.0;
				}
			}
			else {
				hor = 0.0;
			}

			if ((textbox->_textbox_flags & TextBoxComponent::TRANSITION_UP) != TextBoxComponent::TXTBOX_NULL) {
				vert = -4.0;
				if (_transform_comp->position.y + vert < -400) {
					vert = 0.0;
				}
			}
			else if ((textbox->_textbox_flags & TextBoxComponent::TRANSITION_DOWN) != TextBoxComponent::TXTBOX_NULL) {
				vert = 4.0;
				if (_transform_comp->position.y + vert > windowManager->getHeight()) {
					vert = 0.0;
				}
			}
			else {
				vert = 0.0;
			}

			if ((hor == 0.0) && (vert == 0.0)) {
				textbox->_textbox_flags ^= TextBoxComponent::EXIT;
				textbox->_textbox_flags ^= TextBoxComponent::END;
			}

			componentManager->addComponent<Engine::VelocityComponent>(entity, Engine::Vector2f(hor, vert));
		}
		else if ((textbox->_textbox_flags & TextBoxComponent::END) == TextBoxComponent::TXTBOX_NULL) {
			std::string currentText = _text_comp->getText();
			if (textbox->dT % 30 == 0) {
				if ((textbox->_textbox_flags & TextBoxComponent::TXT_CONTINUE) == TextBoxComponent::TXTBOX_NULL) {
					if ((textbox->_textbox_flags & TextBoxComponent::TXT_COMPLETE) == TextBoxComponent::TXTBOX_NULL) {
						if (currentText.size() < textbox->_textbox_text.size()) {
							currentText.append(textbox->_textbox_text, currentText.size(), 1);
							if (currentText.back() == '\n') {
								textbox->textLine++;
							}
							if (textbox->textLine > 6) {
								textbox->_textbox_flags ^= TextBoxComponent::TXT_CONTINUE;
							}
							_text_comp->setText(currentText.c_str());
						}
						else {
							textbox->_textbox_flags |= TextBoxComponent::TXT_COMPLETE;
						}
					}
				}
			}
			if (componentManager->getComponent<Engine::InputComponent>(entity)->keyPressed(SDL_SCANCODE_SPACE)) {

				if ((textbox->_textbox_flags & TextBoxComponent::TXT_COMPLETE) != TextBoxComponent::TXTBOX_NULL) {
					textbox->_textbox_flags ^= TextBoxComponent::EXIT;

					if (((textbox->_textbox_flags & TextBoxComponent::TRANSITION_LEFT) != TextBoxComponent::TXTBOX_NULL) ||
						((textbox->_textbox_flags & TextBoxComponent::TRANSITION_RIGHT) != TextBoxComponent::TXTBOX_NULL)) {
						textbox->_textbox_flags ^= TextBoxComponent::TRANSITION_LEFT;
						textbox->_textbox_flags ^= TextBoxComponent::TRANSITION_RIGHT;
					}

					if (((textbox->_textbox_flags & TextBoxComponent::TRANSITION_UP) != TextBoxComponent::TXTBOX_NULL) ||
						((textbox->_textbox_flags & TextBoxComponent::TRANSITION_DOWN) != TextBoxComponent::TXTBOX_NULL)) {
						textbox->_textbox_flags ^= TextBoxComponent::TRANSITION_UP;
						textbox->_textbox_flags ^= TextBoxComponent::TRANSITION_DOWN;
					}
				}

				if ((textbox->_textbox_flags & TextBoxComponent::TXT_CONTINUE) != TextBoxComponent::TXTBOX_NULL) {
					_text_comp->setText("");
					textbox->textLine = 0;
					auto pos = textbox->_textbox_text.find(currentText);
					if (pos != std::string::npos) {
						textbox->_textbox_text.erase(pos, currentText.length());
					}
					textbox->_textbox_flags ^= TextBoxComponent::TXT_CONTINUE;
				}
				else {
					for (auto ch : textbox->_textbox_text.substr(currentText.size())) {
						currentText.append(1, ch);
						if (ch == '\n') {
							textbox->textLine++;
						}
						if (textbox->textLine > 6) {
							textbox->_textbox_flags ^= TextBoxComponent::TXT_CONTINUE;
							break;
						}
					}
					_text_comp->setText(currentText.c_str());
					if (currentText.size() == textbox->_textbox_text.size()) {
						textbox->_textbox_flags ^= TextBoxComponent::TXT_COMPLETE;
					}
				}
			}

			(textbox->dT < 360) ? textbox->dT += textbox->_textbox_speed : textbox->dT = 0;
		}
	}
}

std::string TR::TextboxSystem::textFormatting(std::string font, int size,  std::string text) {
	int count;
	std::string newString = "", newLine;
	TTF_Font* tempFont = TTF_OpenFont(font.c_str(), size);

	for (char const &ch : text) {
		newLine += ch;
		TTF_MeasureText(tempFont, newLine.c_str(), 730, NULL, &count);
		if (count != newLine.size()) {
			if (newLine.find_last_of(' ') != std::string::npos) {
				newString += newLine.substr(0, newLine.find_last_of(' ')) + "\n";
				newLine = newLine.substr(newLine.find_last_of(' ') + 1);
			}
			else {
				newLine.pop_back();
				newString += newLine + "\n";
				newLine = ch;
			}
		}
	}
	newString += newLine;

	TTF_CloseFont(tempFont);
	return newString;
}

// Overloaded functions

void TR::TextboxSystem::create(const Engine::SystemContext& ctx) {
	if (!ctx.entityManager || !ctx.componentManager || !ctx.window) {
		return;
	}
	else {
		init(ctx.entityManager, ctx.componentManager, ctx.window);
	}
}

void TR::TextboxSystem::update(const Engine::SystemContext& ctx) {
	if (!ctx.entityManager || !ctx.componentManager || !ctx.window) {
		return;
	}
	else {
		updateRender(ctx.entityManager, ctx.componentManager, ctx.window);
	}
}

void TR::TextboxSystem::render(const Engine::SystemContext& ctx) {

}

void TR::TextboxSystem::quit(const Engine::SystemContext& ctx) {
	this->~TextboxSystem();
}