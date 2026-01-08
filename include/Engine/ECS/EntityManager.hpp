#pragma once
#include <iostream>
#include <unordered_set>
#include <ECS/Components/Components.hpp>

namespace Engine {

struct Entity {
    Uint16 _id;
    ComponentGroup<> _components;
};

class EntityManager {
public:
    EntityManager() = default;
    ~EntityManager() = default;

    /// @brief Creates a new entity
    /// @return The newly created entity
    Entity createEntity() {
        Entity id = nextEntity++;
        entities.insert(id);
        return id;
    }

    /// @brief Destroys an existing entity
    /// @param entity The entity to destroy
    void destroy(Entity entity) {
        entities.erase(entity);
    }

    /// @brief Adds a component to an entity
    /// @tparam Component The type of component to add
    /// @tparam ...Args The arguments to construct the component
    /// @param entity The entity to which the component will be added
    /// @param ...args The arguments for the component constructor
    /// @return A reference to the added component
    template<typename Component, typename... Args>
    Component& addComponent(Entity entity, Args&&... args) {
        auto& group = entity._components;
        group.components.get<Component>() = Component(std::forward<Args>(args)...);
        return group.components.get<Component>();
    }

    /// @brief Retrieves a component from an entity
    /// @tparam Component The type of component to retrieve
    /// @param entity The entity from which to retrieve the component
    /// @return A pointer to the component, or nullptr if the component does not exist
    template<typename Component>
    Component* getComponent(Entity entity) {
        return std::get<Component>(entity._components.components);
    }

    bool hasComponent(Entity entity) {
    }
    
private:
    Entity nextEntity = 1;
    std::unordered_set<Entity> entities;

    // std::unordered_set<std::type_index,
        // std::hash<std::type_index>> componentTypes;
};
} // namespace Engine