#pragma once

#include "Engine/ECS/ComponentManager.hpp"
#include "Engine/ECS/EntityManager.hpp"
#include "Engine/ECS/SystemManager.hpp"

namespace Engine {
	class ECSManager {
	public:
		ECSManager() = default;
        ~ECSManager() {
            componentManager.release();
            entityManager.release();
            systemManager.release();
        }

        /// @brief Initilizes the ECS Manager
        /// @param window The current application's window
        /// @param input The application's current input manager
        /// @param assets The application's asset manager
        void init(const std::unique_ptr<Window>& window, const std::unique_ptr<Input>& input, const std::unique_ptr<AssetManager>& assets) {
            componentManager = std::make_unique<ComponentManager>();
            entityManager = std::make_unique<EntityManager>();
            systemManager = std::make_unique<SystemManager>();

            systemManager->setManager<ComponentManager>(componentManager);
            systemManager->setManager<EntityManager>(entityManager);
            systemManager->setManager<Window>(window);
            systemManager->setManager<Input>(input);
            systemManager->setManager<AssetManager>(assets);
            
        }

        /// @brief Creates a new entity
        /// @return The newly created entity
        Entity createEntity() {
            return entityManager->createEntity();
        }

        /// @brief Destroys an existing entity
        /// @param entity The entity to destroy
        void destroyEntity(Entity entity) {
            componentManager->clearComponents(entity);
            entityManager->destroy(entity);
            return;
        }

        /// @brief Destroys all current entities
        void destroyAllEntities() {
            componentManager->clearAllComponents();
            entityManager->destroyAll();
            return;
        }

        /// @brief Adds a component to an entity
        /// @tparam ComponentType The type of component to add
        /// @tparam ...Args The arguments to construct the component
        /// @param entity The entity to which the component will be added
        /// @param ...args The arguments for the component constructor
        /// @return A reference to the added component
        template<typename ComponentType, typename... Args>
        ComponentType& addComponent(Entity entity, Args&&... args) {
            return componentManager->addComponent<ComponentType>(entity, std::forward<Args>(args)...);
        }

        /// @brief Retrieves a component from an entity
        /// @tparam Component The type of component to retrieve
        /// @param entity The entity from which to retrieve the component
        /// @return A pointer to the component, or nullptr if the component does not exist
        template<typename ComponentType>
        ComponentType* getComponent(Entity entity) {
            return componentManager->getComponent<ComponentType>(entity);
        }


        /// @brief Checks whether an entity has a component
        /// @tparam Component The type of component to search
        /// @param entity The entity from which to retrieve the component
        /// @return A boolean whether it exists or not
        template<typename ComponentType>
        bool hasComponent(Entity entity) {
            return componentManager->hasComponent<ComponentType>(entity);
        }

        /// @brief Checks whether a component exists
        /// @tparam Component The type of component to search
        /// @return A boolean whether it exists or not
        template<typename ComponentType>
        bool componentExists() {
            return componentManager->componentExists<ComponentType>();
        }


		template<typename SystemType>
		void addSystem(std::unique_ptr<SystemType> system) {
            systemManager->addSystem<SystemType>(system);
		}

        template<typename SystemType>
        void addSystem() {
            systemManager->addSystem<SystemType>();
        }

		template<typename SystemType>
		void toggleSystem(bool isRunning) {
            systemManager->toggleSystem<SystemType>(isRunning);
		}

        template<typename SystemType>
        bool isSystemRunning() {
            return systemManager->isSystemRunning<SystemType>();
        }

		template<typename SystemType>
		void initSystem() {
            systemManager->initSystem<SystemType>();
		}



		void create() {
            systemManager->create();
		}

		void update() {
            systemManager->update();
		}

		void render() {
            systemManager->render();
		}

		void quit() {
            systemManager->quit();
            this->destroyAllEntities();
		}

	private:
		std::unique_ptr<ComponentManager> componentManager;
		std::unique_ptr<EntityManager> entityManager;
		std::unique_ptr<SystemManager> systemManager;
	};
}