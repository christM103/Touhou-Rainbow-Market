#pragma once
#include <vector>

#include <Engine/ECS/System/BaseSystem.hpp>

namespace Engine {
	class CollisionSystem {
	public:

		CollisionSystem() = default;
		~CollisionSystem() = default;

		/// @brief Initilize new colliders into a collider into the deque
		/// @param componentManager SDL_Renderer to draw the sprite on
		void initCollision(ComponentManager* componentManager);

		/// @brief Checks for any collider objects were removed or created
		/// @param entityManager For checking whether entities were removed
		/// @param componentManager For the init of the component manager
		void updateEntities(EntityManager* entityManager, ComponentManager* componentManager);
		
		/// @brief Updates the positioning of the object collision box
		/// @param componentManager To get the component's position & and the camera data
		void updatePosition(ComponentManager* componentManager);

		/// @brief Checks for any collision cases
		/// @param componentManager To check collision cases.
		void updateCollision(ComponentManager* componentManager);

		// Overloaded functions

		void create(const SystemContext& ctx);

		void update(const SystemContext& ctx);

		void render(const SystemContext& ctx);

		void quit(const SystemContext& ctx);
	private:
		std::vector<std::pair<Entity, ColliderComponent*>> _collision_entities;
	};
}