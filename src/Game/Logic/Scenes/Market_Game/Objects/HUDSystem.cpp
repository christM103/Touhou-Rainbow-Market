#include "Game/Objects/Systems/Market/HUDSystem.hpp"
#include <format>


void TR::HUDSystem::initHUD(Engine::EntityManager* eM, Engine::ComponentManager* cM, Engine::Window* wM, Engine::AssetManager* aM) {
	auto Player_Entity = eM->getEntity(PLAYER1_ENTITY_NAME.data());
	if (!Player_Entity) {
		return;
	}
	_player_component = cM->getComponent<PlayerComponent>(Player_Entity);

	auto Keyboard_Entity = eM->getEntity(KEYBOARD_ENTITY_NAME.data());
	if (!Keyboard_Entity) {
		return;
	}
	_input_component = cM->getComponent<Engine::InputComponent>(Keyboard_Entity);

	auto HUD_Entity = eM->getEntity(HUD_ENTITY_NAME.data());
	if (!HUD_Entity) {
		HUD_Entity = eM->createEntity(HUD_ENTITY_NAME.data());
		cM->addComponent<HUDComponent>(HUD_Entity);
	}
	_HUD_Component = cM->getComponent<HUDComponent>(HUD_Entity);
}

void TR::HUDSystem::updateEntites(Engine::EntityManager* eM, Engine::ComponentManager* cM, Engine::Window* wM, Engine::AssetManager* aM) {
	if (!_HUD_Component || !_player_component) {
		_systemEnable = false;

		if (eM->entityExists(PLAYER1_ENTITY_NAME.data())) {
			initHUD(eM, cM, wM, aM);
		}

	}
	else {
		if (!_systemEnable) {
			_systemEnable = true;
		}
	}
}

void TR::HUDSystem::updateData(Engine::EntityManager* eM, Engine::ComponentManager* cM, Engine::Window* wM) {
	const auto& assign_if_diff = [=](auto a, auto b) {
		TEXT_TEMP_VALUE.at(a) = 
			(TEXT_TEMP_VALUE.at(a) != b) ? b : TEXT_TEMP_VALUE.at(a);
	};

	const auto& debug_component = Engine::DebugManager::instance();

	assign_if_diff("player_char", 
		CHAR_STATE_TO_STR.at(_player_component->current_char));
	assign_if_diff("player_type", 
		std::to_string(_player_component->char_type));
	assign_if_diff("player_profit", 
		std::format("{:.2f}", _player_component->player_data->getProfit()));
	assign_if_diff("player_lot", 
		_player_component->lot_data->get()->getMarketList());
	assign_if_diff("game_timer", 
		std::to_string(0));
	assign_if_diff("player_act_pla",
		std::to_string(_player_component->player_actions));
	assign_if_diff("player_act_mar",
		std::to_string(_player_component->market_actions));

	if (has_flag(_HUD_Component->hudFlags, HUD_Flags::Focus_Market)) {
		auto ent_name = LAND_STATE_TO_STR.at(_HUD_Component->highlightedLand);
		_market_component = eM->getComponent<MarketComponent>(ent_name.data(), cM);

		assign_if_diff("market_active",
			std::to_string(_market_component->market_active));
		assign_if_diff("market_id",
			std::to_string(static_cast<int>(_market_component->market_ID)));
	}
	else {
		if (_market_component) {
			_market_component = nullptr;
		}
	}

}

void TR::HUDSystem::recordInput() {
	const auto& landFocus = [=](Land_ID land) {
		_HUD_Component->highlightedLand = land;
		_HUD_Component->hudFlags |= HUD_Flags::Focus_Market;
	};

	if (!_HUD_Component->isHUDEnabled) {
		return;
	}

	if (!has_flag(_HUD_Component->hudFlags, HUD_Flags::Focus_Market) &&
		!has_flag(_HUD_Component->hudFlags, HUD_Flags::Focus_Player) ) {
		if (_input_component->keyPressed(SDL_SCANCODE_1)) {
			landFocus(Land_ID::Land_1);
		}
		else if (_input_component->keyPressed(SDL_SCANCODE_2)) {
			landFocus(Land_ID::Land_2);
		}
		else if (_input_component->keyPressed(SDL_SCANCODE_3)) {
			landFocus(Land_ID::Land_3);
		}
		else if (_input_component->keyPressed(SDL_SCANCODE_4)) {
			landFocus(Land_ID::Land_4);
		}
		else if (_input_component->keyPressed(SDL_SCANCODE_5)) {
			landFocus(Land_ID::Land_5);
		}
		else if (_input_component->keyPressed(SDL_SCANCODE_6)) {
			landFocus(Land_ID::Land_6);
		} 
		else if (_input_component->keyPressed(SDL_SCANCODE_Z)) {
			_HUD_Component->hudFlags |= HUD_Flags::Focus_Player;
		}
		
	}
	
}

void TR::HUDSystem::create(const Engine::SystemContext& ctx) {
	if (!ctx.entityManager || !ctx.componentManager || !ctx.window || !ctx.assetManager) {
		return;
	}
	else {
		this->initHUD(ctx.entityManager, ctx.componentManager, ctx.window, ctx.assetManager);
	}
}

void TR::HUDSystem::update(const Engine::SystemContext& ctx) {
	if (!ctx.entityManager || !ctx.componentManager || !ctx.window || !ctx.assetManager) {
		return;
	}
	else {
		this->updateEntites(ctx.entityManager, ctx.componentManager, ctx.window, ctx.assetManager);
		if (_systemEnable) {
			this->updateData(ctx.entityManager, ctx.componentManager, ctx.window);
			this->recordInput();
		}
	}
}

void TR::HUDSystem::render(const Engine::SystemContext& ctx) {

}

void TR::HUDSystem::quit(const Engine::SystemContext& ctx) {
	this->~HUDSystem();
}