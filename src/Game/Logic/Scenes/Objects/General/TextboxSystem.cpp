#pragma once

#include <array>
#include <SDL2/SDL_ttf.h>
#include "Game/Objects/Systems/Common/TextboxSystem.hpp"


TR::TextboxSystem::~TextboxSystem() {
	_textboxes.clear();
}

void TR::TextboxSystem::initTextbox(Engine::ComponentManager* componentManager, Engine::Window* windowManager, Engine::AssetManager* assetManager) {
	
	// Texture Initilization
	if (!assetManager->getTexture("TXTBOX_TILESET")) {
		assetManager->loadTexture("assets/gfx/sprites/Common/Placeholder_Box_Tileset.png", "TXTBOX_TILESET", windowManager->getRenderer());
	}
	
	const auto* entities = componentManager->allEntities<TextBoxComponent>();
	TextBoxComponent* textbox;
	const char* text;
	Engine::Vector2i position;

	uint8_t width_flags = TextBoxComponent::WIDTH_TINY | TextBoxComponent::WIDTH_SMALL | TextBoxComponent::WIDTH_MEDIUM | TextBoxComponent::WIDTH_LARGE;
	uint8_t height_flags = TextBoxComponent::HEIGHT_TINY | TextBoxComponent::HEIGHT_SMALL | TextBoxComponent::HEIGHT_MEDIUM | TextBoxComponent::HEIGHT_LARGE;

	if (!entities) {
		return;
	}

	// Initialize the textboxes for each entity
	for (const auto& entity : *entities) {
		if (_textboxes.find(entity) == _textboxes.end()) {
			textbox = componentManager->getComponent<TextBoxComponent>(entity);
			if (textbox && _textboxes.try_emplace(entity, textbox).second) {

				auto& _transform_comp = componentManager->addComponent<Engine::MultiTransformComponent>(entity);
				auto& _velocity_comp = componentManager->addComponent<Engine::VelocityComponent>(entity, Engine::Vector2f(0,0));
				auto& _sprite_comp = componentManager->addComponent<Engine::MultiSpriteComponent>(entity);
				auto& _text_comp = componentManager->addComponent<Engine::MultiTextComponent>(entity);
				auto& _render_comp = componentManager->addComponent<Engine::RenderLayerComponent>(entity, Engine::RenderLayerComponent::FG);
				auto& _input_comp = componentManager->addComponent<Engine::InputComponent>(entity);

				// Position Calculations
				calculateSize(textbox);
				position = textbox->_textbox_position;
				if ((textbox->_textbox_flags & TextBoxComponent::ENTER) != TextBoxComponent::TXTBOX_NULL) {
					if ((textbox->_textbox_flags & TextBoxComponent::TRANSITION_LEFT) != TextBoxComponent::TXTBOX_NULL) {
						position.x = windowManager->getWidth();
					}
					else if ((textbox->_textbox_flags & TextBoxComponent::TRANSITION_RIGHT) != TextBoxComponent::TXTBOX_NULL) {
						position.x = -textbox->_textbox_size.x;
					}

					if ((textbox->_textbox_flags & TextBoxComponent::TRANSITION_UP) != TextBoxComponent::TXTBOX_NULL) {
						position.y = windowManager->getHeight();
					}
					else if ((textbox->_textbox_flags & TextBoxComponent::TRANSITION_DOWN) != TextBoxComponent::TXTBOX_NULL) {
						position.y = -textbox->_textbox_size.y;
					}
				}

				// Tileset Layout
				const uint16_t width = textbox->_textbox_size.x;
				const uint16_t height = textbox->_textbox_size.y;

				setStructure(textbox, &_sprite_comp, &_transform_comp, position);

				// Text Layout
				_transform_comp.transforms.emplace(9, std::make_shared<Engine::TransformComponent>((position + Engine::Vector2i(40, 40))));
				((textbox->_textbox_flags & TextBoxComponent::TXT_COMPLETE) != TextBoxComponent::TXTBOX_NULL) ? text = textbox->_textbox_text.c_str() : text = "";
				_textboxes.at(entity)->_textbox_text = textFormatting("assets/fonts/ArialMdm.ttf", textbox->_textSize, width - 70, textbox->_textbox_text);
				_text_comp.text.emplace(9, std::make_shared<Engine::TextComponent>(text, textbox->_textSize, Engine::Vector4i(255, 255, 255, 255), Engine::Vector2i(width - 70, height)));

				// Other Components
				_render_comp.layer = Engine::RenderLayerComponent::FG;
				_input_comp.newKey(SDL_SCANCODE_SPACE);
			}
		}
	}
}

void TR::TextboxSystem::updateEntity(const Engine::EntityManager* entityManager, Engine::ComponentManager* componentManager, Engine::Window* windowManager, Engine::AssetManager* assetManager) {
	std::erase_if(_textboxes, [&](const auto& item) {
		const auto& [entity, component] = item;
		const auto& entMap = entityManager->getEntities();
		const auto it = std::find_if(entMap.begin(), entMap.end(), [&](const auto& pair) {
			return pair.second == entity;
			});
		return (it == entMap.end());
		});

	if (auto* entities = componentManager->allEntities<TextBoxComponent>()) {
		if (entities->size() > _textboxes.size()) {
			this->initTextbox(componentManager, windowManager, assetManager);
		}
	}
}

void TR::TextboxSystem::updateRender(const Engine::EntityManager* entityManager, Engine::ComponentManager* componentManager, Engine::Window* windowManager) {
	Engine::TextComponent* _text_comp;
	Engine::TransformComponent* _top_left, *_bottom_right;
	Engine::MultiTransformComponent* _positions;
	Engine::MultiSpriteComponent* _sprites;
	Engine::InputComponent* _input_comp;

	Engine::Vector2f velocity;
	uint16_t textbox_states = TextBoxComponent::TXT_CONTINUE | TextBoxComponent::TXT_COMPLETE;
	
	for (const auto& [entity, textbox] : _textboxes) {
		_text_comp = componentManager->getComponent<Engine::MultiTextComponent>(entity)->text.at(9).get();
		_positions = componentManager->getComponent<Engine::MultiTransformComponent>(entity);
		_sprites = componentManager->getComponent<Engine::MultiSpriteComponent>(entity);
		_top_left = _positions->transforms.at(1).get();
		_bottom_right = _positions->transforms.at(4).get();
		_input_comp = componentManager->getComponent<Engine::InputComponent>(entity);
		// _input_comp->keyPressed(SDL_SCANCODE_SPACE)

		this->calculateSize(textbox, true);
		Engine::Vector2i current_size = _bottom_right->position - _top_left->position + Engine::Vector2i{32, 32};
		if (current_size != textbox->_textbox_size) {
			textbox->_textbox_flags |= TextBoxComponent::RESIZE;
		}
		else {
			textbox->_textbox_flags &= ~TextBoxComponent::RESIZE;
		}

		// The enter transition is active
		if ((textbox->_textbox_flags & TextBoxComponent::ENTER) != TextBoxComponent::TXTBOX_NULL) {
			velocity = textboxTransition(textbox, _top_left, TextBoxComponent::ENTER, Engine::Vector2i(windowManager->getWidth(), windowManager->getHeight()));
			componentManager->addComponent<Engine::VelocityComponent>(entity, velocity);
		}
		// The exit transition is active
		else if ((textbox->_textbox_flags & TextBoxComponent::EXIT) != TextBoxComponent::TXTBOX_NULL) {
			velocity = textboxTransition(textbox, _top_left, TextBoxComponent::EXIT, Engine::Vector2i(windowManager->getWidth(), windowManager->getHeight()));
			componentManager->addComponent<Engine::VelocityComponent>(entity, velocity);
		}
		// The textbox is resizing
		else if ((textbox->_textbox_flags & TextBoxComponent::RESIZE) != TextBoxComponent::TXTBOX_NULL) {
			this->setStructure(textbox, _sprites, _positions, _top_left->position);
		}
		// The textbox is static
		else if ((textbox->_textbox_flags & TextBoxComponent::RESIZE) == TextBoxComponent::TXTBOX_NULL) {
			std::string currentText = _text_comp->getText();
			_input_comp->keyPressed(SDL_SCANCODE_SPACE) ? textbox->_textbox_flags |= TextBoxComponent::INPUT_PRESSED : textbox->_textbox_flags &= ~TextBoxComponent::INPUT_PRESSED;
			switch (uint16_t state = (textbox->_textbox_flags & textbox_states)) {
				case TextBoxComponent::TXT_CONTINUE:
					if ((textbox->_textbox_flags & TextBoxComponent::INPUT_PRESSED) != TextBoxComponent::TXTBOX_NULL) {
						_text_comp->setText("");
						textbox->_textLine = 0;
						auto pos = textbox->_textbox_text.find(currentText);
						if (pos != std::string::npos) {
							textbox->_textbox_text.erase(pos, currentText.length());
						}
						textbox->_textbox_flags ^= TextBoxComponent::TXT_CONTINUE;
					}
					break;
				case TextBoxComponent::TXT_COMPLETE:
					if ((textbox->_textbox_flags & TextBoxComponent::INPUT_PRESSED) != TextBoxComponent::TXTBOX_NULL) {

						if (!textbox->_textbox_next.empty()) {
							textbox->_textbox_text = textFormatting("assets/fonts/ArialMdm.ttf", textbox->_textSize, textbox->_textbox_size.x - 70, textbox->_textbox_next);
							textbox->_textbox_next.clear();
							_text_comp->setText("");
							textbox->_textbox_flags ^= textbox->TXT_COMPLETE;
						}
						else {
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

							_text_comp->setText("");
						}
					}
					break;
				default:
					if (textbox->dT % 30 == 0) {
						if (currentText.size() < textbox->_textbox_text.size()) {
							currentText.append(textbox->_textbox_text, currentText.size(), 1);
							if (currentText.back() == '\n') {
								textbox->_textLine++;
							}
							if (textbox->_textLine > textbox->_textMax) {
								textbox->_textbox_flags ^= TextBoxComponent::TXT_CONTINUE;
							}
							_text_comp->setText(currentText.c_str());
						}
						else {
							textbox->_textbox_flags |= TextBoxComponent::TXT_COMPLETE;
						}
					}
					if ((textbox->_textbox_flags & TextBoxComponent::INPUT_PRESSED) != TextBoxComponent::TXTBOX_NULL) {
						for (auto ch : textbox->_textbox_text.substr(currentText.size())) {
							currentText.append(1, ch);
							if (ch == '\n') {
								textbox->_textLine++;
							}
							if (textbox->_textLine > textbox->_textMax) {
								textbox->_textbox_flags ^= TextBoxComponent::TXT_CONTINUE;
								break;
							}
						}
						_text_comp->setText(currentText.c_str());
						if (currentText.size() == textbox->_textbox_text.size()) {
							textbox->_textbox_flags ^= TextBoxComponent::TXT_COMPLETE;
						}
						//textbox->_textbox_flags ^= TextBoxComponent::INPUT_PRESSED;
					}
					break;
			}

			(textbox->dT < 360) ? textbox->dT += textbox->_textbox_speed : textbox->dT = 0;
		}
	}

	
}

void TR::TextboxSystem::calculateSize(TextBoxComponent* textbox, bool isDynamic, Engine::MultiTransformComponent* transform_comp) {
	uint8_t width_flags = TextBoxComponent::WIDTH_TINY | TextBoxComponent::WIDTH_SMALL | TextBoxComponent::WIDTH_MEDIUM | TextBoxComponent::WIDTH_LARGE;
	uint8_t height_flags = TextBoxComponent::HEIGHT_TINY | TextBoxComponent::HEIGHT_SMALL | TextBoxComponent::HEIGHT_MEDIUM | TextBoxComponent::HEIGHT_LARGE;

	auto setSize = [&](bool isHor, uint16_t desired) {
		int* var = isHor ? &textbox->_textbox_size.x : &textbox->_textbox_size.y;
		if (isDynamic) {
			if (*var + 4 < desired) {
				*var += 4;
			}
			else if (*var - 4 > desired) {
				*var -= 4;
			}
			else {
				*var = desired;
			}
		}
		else {
			*var = desired;
		}
	};

	switch (uint8_t wF = (textbox->_textbox_style & width_flags)) {
	case TextBoxComponent::WIDTH_TINY:
		setSize(true, 300);
		break;
	case TextBoxComponent::WIDTH_SMALL:
		setSize(true, 600);
		break;
	case TextBoxComponent::WIDTH_MEDIUM:
		setSize(true, 800);
		break;
	case TextBoxComponent::WIDTH_LARGE:
		setSize(true, 1000);
		break;
	default:
		textbox->_textbox_size.x = 0;
		break;
	}
	switch (uint8_t hF = (textbox->_textbox_style & height_flags)) {
	case TextBoxComponent::HEIGHT_TINY:
		setSize(false, 100);
		textbox->_textMax = 2;
		break;
	case TextBoxComponent::HEIGHT_SMALL:
		setSize(false, 200);
		textbox->_textMax = 4;
		break;
	case TextBoxComponent::HEIGHT_MEDIUM:
		setSize(false, 400);
		textbox->_textMax = 6;
		break;
	case TextBoxComponent::HEIGHT_LARGE:
		setSize(false, 600);
		textbox->_textMax = 8;
		break;
	default:
		textbox->_textbox_size.y = 0;
		textbox->_textMax = 0;
		break;
	}
	textbox->_textMax += 40 / textbox->_textSize;
}

void TR::TextboxSystem::setStructure(TextBoxComponent* textbox, Engine::MultiSpriteComponent* sprites, Engine::MultiTransformComponent* transform, Engine::Vector2i position) {
	const uint16_t width = textbox->_textbox_size.x;
	const uint16_t height = textbox->_textbox_size.y;
	uint8_t index = 1;

	transform->transforms.insert_or_assign(0, std::make_shared<Engine::TransformComponent>(position + Engine::Vector2i(8, 10)));
	sprites->sprites.insert_or_assign(0, std::make_shared<Engine::SpriteComponent>(
		Engine::Recti((1000 - width + 20) / 2, (600 - height + 20) / 2, 1000, 600), Engine::Vector2i(width - 20, height - 20), "TXT_BOX_BG"));

	Engine::SpriteComponent spriteCornerTL{ Engine::Recti(0, 0, 16, 16), Engine::Vector2i(32, 32), "TXTBOX_TILESET" };
	Engine::SpriteComponent spriteCornerTR{ Engine::Recti(32, 0, 16, 16), Engine::Vector2i(32, 32), "TXTBOX_TILESET" };
	Engine::SpriteComponent spriteCornerBL{ Engine::Recti(0, 32, 16, 16), Engine::Vector2i(32, 32), "TXTBOX_TILESET" };
	Engine::SpriteComponent spriteCornerBR{ Engine::Recti(32, 32, 16, 16), Engine::Vector2i(32, 32), "TXTBOX_TILESET" };
	Engine::SpriteComponent spriteLeft{ Engine::Recti(0, 16, 16, 16), Engine::Vector2i(32, 32), "TXTBOX_TILESET" };
	Engine::SpriteComponent spriteRight{ Engine::Recti(32, 16, 16, 16), Engine::Vector2i(32, 32), "TXTBOX_TILESET" };
	Engine::SpriteComponent spriteUp{ Engine::Recti(16, 0, 16, 16), Engine::Vector2i(32, 32), "TXTBOX_TILESET" };
	Engine::SpriteComponent spriteDown{ Engine::Recti(16, 32, 16, 16), Engine::Vector2i(32, 32), "TXTBOX_TILESET" };

	spriteUp.setSize(spriteUp.getSize() + Engine::Vector2i(width - 96, 0));
	spriteDown.setSize(spriteDown.getSize() + Engine::Vector2i(width - 96, 0));
	spriteLeft.setSize(spriteLeft.getSize() + Engine::Vector2i(0, height - 96));
	spriteRight.setSize(spriteRight.getSize() + Engine::Vector2i(0, height - 96));

	Engine::TransformComponent transTL(position);
	Engine::TransformComponent transTR(position + Engine::Vector2i(width - 32, 0));
	Engine::TransformComponent transBL(position + Engine::Vector2i(0, height - 32));
	Engine::TransformComponent transBR(position + Engine::Vector2i(width - 32, height - 32));
	Engine::TransformComponent transL(position + Engine::Vector2i(0, 32));
	Engine::TransformComponent transR(position + Engine::Vector2i(width - 32, 32));
	Engine::TransformComponent transU(position + Engine::Vector2i(32, 0));
	Engine::TransformComponent transD(position + Engine::Vector2i(32, height - 32));

	using Sprite = std::pair<Engine::TransformComponent, Engine::SpriteComponent>;
	std::array<Sprite, 8>  transformTiles{ 
		Sprite{transTL, spriteCornerTL}, Sprite{transTR, spriteCornerTR}, Sprite{transBL, spriteCornerBL}, Sprite{transBR,spriteCornerBR}, 
		Sprite{transL, spriteLeft}, Sprite{transR, spriteRight}, Sprite{transU, spriteUp}, Sprite{transD, spriteDown} };

	for (auto& [trans, sprite] : transformTiles) {
		transform->transforms.insert_or_assign(index, std::make_shared<Engine::TransformComponent>(trans));
		sprites->sprites.insert_or_assign(index, std::make_shared<Engine::SpriteComponent>(sprite));
		index++;
	}
}

Engine::Vector2f TR::TextboxSystem::textboxTransition(TextBoxComponent* textbox, Engine::TransformComponent* transform, TextBoxComponent::TextBoxFlags direction, Engine::Vector2i window) {
	uint16_t movement_flags = TextBoxComponent::TRANSITION_LEFT | TextBoxComponent::TRANSITION_RIGHT | TextBoxComponent::TRANSITION_UP | TextBoxComponent::TRANSITION_DOWN;
	float hor = 0.0, vert = 0.0;
	int limitLeft = ((textbox->_textbox_flags & TextBoxComponent::ENTER) != TextBoxComponent::TXTBOX_NULL) ? textbox->_textbox_position.x : -textbox->_textbox_size.x;
	int limitRight = ((textbox->_textbox_flags & TextBoxComponent::ENTER) != TextBoxComponent::TXTBOX_NULL) ? textbox->_textbox_position.x : window.x;
	int limitUp = ((textbox->_textbox_flags & TextBoxComponent::ENTER) != TextBoxComponent::TXTBOX_NULL) ? textbox->_textbox_position.y : -textbox->_textbox_size.y;
	int limitDown = ((textbox->_textbox_flags & TextBoxComponent::ENTER) != TextBoxComponent::TXTBOX_NULL) ? textbox->_textbox_position.y : window.y;

	switch (uint16_t movement = (textbox->_textbox_flags & movement_flags)) {
		case TextBoxComponent::TRANSITION_LEFT:
			hor = -4.0;
			if (transform->position.x + hor < limitLeft) {
				hor = 0.0;
			}
			break;
		case TextBoxComponent::TRANSITION_RIGHT:
			hor = 4.0;
			if (transform->position.x + hor > limitRight) {
				hor = 0.0;
			}
			break;
		case TextBoxComponent::TRANSITION_UP:
			vert = -4.0;
			if (transform->position.y + vert < limitUp) {
				vert = 0.0;
			}
			break;
		case TextBoxComponent::TRANSITION_DOWN:
			vert = 4.0;
			if (transform->position.y + vert > limitDown) {
				vert = 0.0;
			}
			break;
		default:
			hor = 0.0f;
			vert = 0.0f;
			break;
	}
	if ((hor == 0.0) && (vert == 0.0)) {
		textbox->_textbox_flags ^= TextBoxComponent::ENTER;
	}

	return Engine::Vector2f(hor, vert);
}

std::string TR::TextboxSystem::textFormatting(std::string font, int size, uint16_t width, std::string text) {
	int count;
	std::string newString = "", newLine;
	TTF_Font* tempFont = TTF_OpenFont(font.c_str(), size);

	for (char const &ch : text) {
		newLine += ch;
		TTF_MeasureText(tempFont, newLine.c_str(), width, NULL, &count);
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
	if (!ctx.entityManager || !ctx.componentManager || !ctx.window || !ctx.assetManager) {
		return;
	}
	else {
		this->initTextbox(ctx.componentManager, ctx.window, ctx.assetManager);
	}
}

void TR::TextboxSystem::update(const Engine::SystemContext& ctx) {
	if (!ctx.entityManager || !ctx.componentManager || !ctx.window || !ctx.assetManager) {
		return;
	}
	else {
		this->updateEntity(ctx.entityManager, ctx.componentManager, ctx.window, ctx.assetManager);
		this->updateRender(ctx.entityManager, ctx.componentManager, ctx.window);
	}
}

void TR::TextboxSystem::render(const Engine::SystemContext& ctx) {

}

void TR::TextboxSystem::quit(const Engine::SystemContext& ctx) {
	this->~TextboxSystem();
}