#include "Engine/ECS/System/DebugSystem.hpp"


namespace Engine {

	// Helper Functions

	static std::string buildPromptString() {
		std::string result;

		for (size_t ind = 0; ind < DebugComponent::_prompt_strings.size(); ++ind) {
			result += DebugComponent::_prompt_strings[ind];
			if (ind == DebugComponent::_prompt_index) {
				result += " <--";
			}
			result += "\n";
		}

		return result;
	}

	// 

	void DebugSystem::initDebug(EntityManager* entityManager, ComponentManager* componentManager) {
		if (_is_init) {
			return;
		}

		_debug_entity_text = entityManager->getEntity(DEBUG_TEXT_ENTITY_NAME.data());
		if (!_debug_entity_text) {
			Engine::Entity TEXT = entityManager->createEntity(DEBUG_TEXT_ENTITY_NAME.data());
			componentManager->addComponent<TransformComponent>(TEXT, DEBUG_TEXT_POSITION);
			componentManager->addComponent<TextComponent>(TEXT, 
				DEBUG_FONT_SIZE, DEBUG_TEXT_COLOR, DEBUG_TEXT_SIZE);
		}

		_debug_entity_prompt = entityManager->getEntity(DEBUG_PROMPT_ENTITY_NAME.data());
		if (!_debug_entity_prompt) {
			Engine::Entity PROMPT = entityManager->createEntity(DEBUG_PROMPT_ENTITY_NAME.data());
			componentManager->addComponent<TransformComponent>(PROMPT, DEBUG_PROMPT_POSITION);
			componentManager->addComponent<TextComponent>(PROMPT, 
				DEBUG_FONT_SIZE, DEBUG_TEXT_COLOR, DEBUG_PROMPT_SIZE);
		}
		if (auto inputSet = componentManager->allEntities<InputComponent>(); !inputSet->empty()) {
			_screen_input = componentManager->getComponent<InputComponent>(*(inputSet->begin()));
		}

		_is_init = true;
	}

	void DebugSystem::updateText(EntityManager* entityManager, ComponentManager* componentManager) {
		TextComponent* textComponent = entityManager->getComponent<TextComponent>(
			DEBUG_TEXT_ENTITY_NAME.data(), componentManager);
		if (textComponent && !DebugComponent::_current_text.empty()) {
			textComponent->setText(DebugComponent::_current_text.c_str());
		}
	}

	void DebugSystem::updatePrompt(EntityManager* entityManager, ComponentManager* componentManager) {
		TextComponent* promptComponent = entityManager->getComponent<TextComponent>(
			DEBUG_PROMPT_ENTITY_NAME.data(), componentManager);

		if (!promptComponent) {
			return;
		}

		if (DebugComponent::_prompt_active) {
			std::string promptText = buildPromptString();

			if (promptComponent->getText() != promptText) {
				promptComponent->setText(promptText.c_str());
			}
		}
		else {
			if (promptComponent->getText() != "") {
				promptComponent->setText("");
			}
		}
	}

	void DebugSystem::updateInput(ComponentManager* componentManager) {
		if (_screen_input && DebugComponent::_prompt_active) {
			if (_screen_input->keyPressed(SDL_SCANCODE_RIGHT) || 
				_screen_input->keyPressed(SDL_SCANCODE_DOWN)) {
				if (DebugComponent::_prompt_index < DebugComponent::_prompt_strings.size() - 1) {
					DebugComponent::_prompt_index++;
				}
			}
			if (_screen_input->keyPressed(SDL_SCANCODE_LEFT) || 
				_screen_input->keyPressed(SDL_SCANCODE_UP)) {
				if (DebugComponent::_prompt_index > 0) {
					DebugComponent::_prompt_index--;
				}
			}
		}
	}

	void DebugSystem::updateEntities(EntityManager* entityManager, ComponentManager* componentManager) {
		if (!DebugComponent::_debug_active) {
			if (!_debug_entity_text) {
				entityManager->destroy(DEBUG_TEXT_ENTITY_NAME.data());
				_debug_entity_text = 0;
			}
			if (!_debug_entity_prompt) {
				entityManager->destroy(DEBUG_PROMPT_ENTITY_NAME.data());
				_debug_entity_prompt = 0;
			}
			_is_init = false;
			return;
		}

		if (!_debug_entity_text || !_debug_entity_prompt || _screen_input == nullptr) {
			this->initDebug(entityManager, componentManager);
		}

	}

	void DebugSystem::create(const SystemContext& ctx) {
		if (!ctx.entityManager || !ctx.componentManager) {
			return;
		}
		else {
			this->initDebug(ctx.entityManager, ctx.componentManager);
		}
	}

	void DebugSystem::update(const SystemContext& ctx) {
		if (!ctx.entityManager || !ctx.componentManager) {
			return;
		}
		else {
			this->updateEntities(ctx.entityManager, ctx.componentManager);
			this->updateText(ctx.entityManager, ctx.componentManager);
			this->updatePrompt(ctx.entityManager, ctx.componentManager);
			this->updateInput(ctx.componentManager);
		}
	}

	void DebugSystem::render(const SystemContext& ctx) {

	}

	void DebugSystem::quit(const SystemContext& ctx) {
		_is_init = false;
		_debug_entity_text = 0;
		_debug_entity_prompt = 0;
		_screen_input = nullptr;
	}


}