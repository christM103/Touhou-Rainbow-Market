#pragma once

#include "Game/Objects/Systems/Common/PlayerSystem.hpp"



TR::PlayerSystem::~PlayerSystem() {
	_players.clear();
}

void TR::PlayerSystem::init(const Engine::EntityManager* entityManager, Engine::ComponentManager* componentManager) {
	PlayerComponent* playerComp;
	const auto* entities = componentManager->allEntities<PlayerComponent>();

	for (auto& entity : *entities) {
		playerComp = componentManager->getComponent<PlayerComponent>(entity);
		auto playerIt = std::find_if(_players.begin(), _players.end(),
			[entity](const auto& p) { return p.first == entity; });

		if (playerIt == _players.end()) {
			switch (playerComp->current_char) {
				case Player_Data::S_Reimu:
					_players.emplace_back( entity, std::make_unique<Player_Reimu>(playerComp->char_type) );
					break;
				case Player_Data::S_Marisa:
					_players.emplace_back( entity, std::make_unique<Player_Marisa>(playerComp->char_type) );
					break;
				default:
					_players.emplace_back( entity, std::make_unique<Player_Null>(playerComp->char_type) );
			}

			playerComp->player_data = _players.back().second.get();
		}
	}

}


void TR::PlayerSystem::create(const Engine::SystemContext& ctx) {
	if (!ctx.entityManager || !ctx.componentManager) {
		return;
	}
	else {
		init(ctx.entityManager, ctx.componentManager);
	}
}

void TR::PlayerSystem::update(const Engine::SystemContext& ctx) {
	if (!ctx.entityManager || !ctx.componentManager) {
		return;
	}
	else {
		init(ctx.entityManager, ctx.componentManager);
	}
}

void TR::PlayerSystem::render(const Engine::SystemContext& ctx) {

}

void TR::PlayerSystem::quit(const Engine::SystemContext& ctx) {
	_players.clear();
}