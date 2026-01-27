#pragma once

#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <utility>
#include <tuple>
#include <any>

#include "Engine/ECS/Components/Components.hpp"

namespace Engine {
    using Entity = unsigned int;


	class ComponentManager {
	public:
		ComponentManager() = default;
		~ComponentManager() = default;

        template<typename ComponentType, typename... Args>
        ComponentType& addComponent(Entity entity, Args&&... args) {

            Component component = std::type_index(typeid(ComponentType));
            ComponentType newComponent(std::forward<Args>(args)...);
            
            if (!this->hasComponent<ComponentType>(entity)) {
                componentTypes.insert(component);

                componentToEntity.try_emplace(component);
                componentToEntity[component].insert(entity);
                
                entityToComponent.try_emplace(entity);
                entityToComponent[entity].try_emplace(component, newComponent);
            }
            else {
                entityToComponent[entity][component] = newComponent;
            }

            auto& compRef = entityToComponent[entity][component];
            return std::any_cast<ComponentType&>(compRef);;
        }

        template<typename ComponentType>
        const ComponentType* getComponent(Entity entity) const {
            if (!this->hasComponent<ComponentType>(entity)) {
                return nullptr;
            }
            else {
                Component component = std::type_index(typeid(ComponentType));
                auto& data = entityToComponent.at(entity).at(component);
                return std::any_cast<const ComponentType>(&data);
            }
        }

        template<typename ComponentType>
        bool hasComponent(Entity entity) const {
            Component compType = std::type_index(typeid(ComponentType));
            auto it = componentTypes.find(compType);
            if (it != componentTypes.end()) {
                return (componentToEntity.at(compType).find(entity) != componentToEntity.at(compType).end());
            }
            return false;
        }

        template<typename ComponentType>
        bool removeComponent(Entity entity) {
            if (this->hasComponent<ComponentType>(entity)) {
                Component component = std::type_index(typeid(ComponentType));

                entityToComponent[entity].erase(component);
                componentToEntity[component].erase(entity);
                if (componentToEntity[component].empty()) {
                    componentToEntity.erase(component);
                    componentTypes.erase(component);
                }
                return true;
            }
            else {
                std::cout << "Unable to remove component: Component does not exist" << std::endl;
                return false;
            }
        }

        bool clearComponents(Entity entity) {
            if (entityToComponent.find(entity) != entityToComponent.end()) {
                entityToComponent[entity].clear();
                entityToComponent.erase(entity);

                for (auto& component : componentToEntity) {
                    component.second.erase(entity);
                    if (component.second.empty()) {
                        componentTypes.erase(component.first);
                        componentToEntity.erase(component.first);
                    }
                }

                return true;
            }
            else {
                std::cout << "Entity does not exist in component" << std::endl;
                return false;
            }
            return false;
        }

        void clearAllComponents() {
            entityToComponent.clear();
            componentToEntity.clear();
            componentTypes.clear();
        }

	private:

        std::unordered_set<Component> componentTypes{ };
        std::unordered_map<Component, std::unordered_set<Entity>> componentToEntity;
        std::unordered_map<Entity, std::unordered_map<Component, std::any> > entityToComponent;
	};
}