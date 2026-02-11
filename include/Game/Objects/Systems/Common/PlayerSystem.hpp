#include <vector>

#include "Engine/ECS/System/BaseSystem.hpp"
#include "Game/Objects/Components/Common/PlayerComponent.hpp"

namespace TR {
	class PlayerSystem {

	public:
		PlayerSystem() = default;
		~PlayerSystem();

		void init(const Engine::EntityManager* entityManager, Engine::ComponentManager* componentManager);

		// Overloaded functions

		void create(const Engine::SystemContext& ctx);

		void update(const Engine::SystemContext& ctx);

		void render(const Engine::SystemContext& ctx);

		void quit(const Engine::SystemContext& ctx);

	private:
		std::vector<std::pair<Engine::Entity, std::unique_ptr<Player_Data>>> _players{ }; // Set of multi sprite objects
	};
}