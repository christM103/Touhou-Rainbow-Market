#pragma once

#include "Engine/ECS/ComponentManager.hpp"


namespace Engine {

class EntityManager {
public:
    EntityManager() = default;
    ~EntityManager() = default;

    Entity createEntity() {
        Entity id = nextEntity++;
        entities.insert(id);
        return id;
    }

    void destroy(Entity entity) {
        entities.erase(entity);

    }

    void destroyAll() {
        entities.clear();
        //nextEntity = 1;
    }

    const std::unordered_set<Entity>& getEntities() const {
        return entities;
    }

    
private:

    Entity nextEntity{ 1 };
    std::unordered_set<Entity> entities{ };

};
} // namespace Engine

