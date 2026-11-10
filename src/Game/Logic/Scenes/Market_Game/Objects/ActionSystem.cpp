#include "Game/Objects/Systems/MarketGameSystems.hpp"


void TR::ActionSystem::actionInit(Engine::ComponentManager* cM) {
	auto entities = cM->allEntities<ActionComponent>();
	for (const auto& entity : *entities) {
		auto entity_comp = cM->getComponent<ActionComponent>(entity);
		if (std::ranges::find(_action_queue, entity_comp) == _action_queue.end()) {
			_action_queue.push_back(entity_comp);
		}
	}
}

void TR::ActionSystem::actionUpdate(Engine::ComponentManager* cM) {
	std::erase_if(_action_queue, [&](const auto& item) {
		return (item == nullptr);
	});

	std::erase_if(_action_queue, [&](ActionComponent* item) {
		return (has_flag(item->action_state, Action_States::Complete) && has_flag(item->action_state, ~Action_States::Active));
	});

	auto entities = cM->allEntities<ActionComponent>();
	if (entities->size() > _action_queue.size()) {
		this->actionInit(cM);
	}

}

void TR::ActionSystem::actionEnable(Engine::EntityManager* eM, Engine::ComponentManager* cM) {

	auto getPlayer = [&](auto player_id) -> PlayerComponent* {
		auto players = cM->allEntities<PlayerComponent>();
		for (auto player : *players) {
			auto entity_comp = cM->getComponent<PlayerComponent>(player);
			if (entity_comp->player_number == player_id) {
				return entity_comp;
			}
		}
		return nullptr;
	};

	

	for (const auto& action : _action_queue) {
		if (action->action_type.empty() || has_flag(action->action_state, ~Action_States::Active)) {
			return;
		}
		auto& type_array = action->action_type;

		switch (auto type = *action->action_type.begin()) {
			case Action_Type::Profit:
				profitActions(action);
				break;
			case Action_Type::Shutdown:
				shutdownActions(action);
				break;
			case Action_Type::Immunity:
				immunityActions(action);
				break;
			case Action_Type::Profit_Rates:
				profitRatesActions(action);
				break;
			case Action_Type::Sell:
				sellActions(action);
				break;
			case Action_Type::Destroy:
				destroyActions(action);
				break;
			case Action_Type::Other:
				otherActions(action);
				break;
			default:
				continue;
		}

		auto current_size = type_array.size();
		std::move(type_array.begin() + 1, type_array.begin() + current_size, type_array.begin());
		
		if (type_array.empty()) {
			disable_flag(action->action_state, Action_States::Active);
			enable_flag(action->action_state, Action_States::Complete);
		}
	}
}

void TR::ActionSystem::actionAnimate(Engine::ComponentManager* cM, Engine::Window* wM, Engine::AssetManager* aM) {
	for (const auto& action : _action_queue) {
		if (has_flag(action->action_state, Action_States::Animated)) {
			// Do animation
		}
	}
}


void TR::ActionSystem::profitActions(ActionComponent* action) {
	/*
	float profit = 0;
	auto player = getPlayer(action->target_player);

	switch (action->action_id) {
		case Action_ID::A_MYST:

			profit = 5000;

			for (const auto& market : player->player_lot) {
				if (market->market_ID != Market_ID::MID_Null) {
					profit = 2500;
					break;
				}
			}

			action->action_state ^= Action_States::Successful;
			action->action_state ^= Action_States::Animated;
			break;
	}
	*/


	};

void TR::ActionSystem::shutdownActions(ActionComponent* action) {

	};

void TR::ActionSystem::immunityActions(ActionComponent* action) {

	};

void TR::ActionSystem::profitRatesActions(ActionComponent* action) {

	};

void TR::ActionSystem::sellActions(ActionComponent* action) {

	};

void TR::ActionSystem::destroyActions(ActionComponent* action) {

	};

void TR::ActionSystem::otherActions(ActionComponent* action) {

	};

// Overloaded functions

void TR::ActionSystem::create(const Engine::SystemContext& ctx) {
	_action_queue.reserve(8);
	if (!ctx.entityManager || !ctx.componentManager) {
		return;
	}
	else {
		this->actionInit(ctx.componentManager);
	}
}

void TR::ActionSystem::update(const Engine::SystemContext& ctx) {
	if (!ctx.entityManager || !ctx.componentManager || !ctx.window || !ctx.assetManager) {
		return;
	}
	else {
		this->actionUpdate(ctx.componentManager);
		this->actionEnable(ctx.entityManager, ctx.componentManager);
		this->actionAnimate(ctx.componentManager, ctx.window, ctx.assetManager);
	}
}

void TR::ActionSystem::render(const Engine::SystemContext& ctx) {

}

void TR::ActionSystem::quit(const Engine::SystemContext& ctx) {

}