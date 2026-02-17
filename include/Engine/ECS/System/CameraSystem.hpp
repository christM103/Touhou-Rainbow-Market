#pragma once

#include <Engine/ECS/System/BaseSystem.hpp>

namespace Engine {
	class CameraSystem {
	public:
		CameraSystem() = default;
		~CameraSystem() = default;

		/// @brief Updates the entities within the camera
		/// @param componentManager For checking for the camera component.
		void initCamera(ComponentManager* componentManager);

		/// @brief Checks for any camera objects were removed or created
		/// @param entityManager For checking whether entities were removed
		/// @param componentManager For the init of the component manager
		void updateEntities(EntityManager* entityManager, ComponentManager* componentManager);

		/// @brief Updates any values for the camera
		/// @param componentManager For using the other components within the entity
		void updateCamera(ComponentManager* componentManager);

		// Overloaded functions

		void create(const SystemContext& ctx);

		void update(const SystemContext& ctx);

		void render(const SystemContext& ctx);

		void quit(const SystemContext& ctx);
	private:
		Entity _camera_entity;
		CameraComponent* _current_camera;
	};
}