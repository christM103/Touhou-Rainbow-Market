#pragma once

#include "Engine/ECS/ComponentManager.hpp"


namespace Engine {

class EntityManager {
public:
    EntityManager() = default;
    ~EntityManager() = default;

    Entity createEntity(std::string entity) {
        Entity id = nextEntity++;
        entities.emplace(entity, id);
        return id;
    }

    void destroy(std::string entity) {
        entities.erase(entity);

    }

    void destroyAll() {
        entities.clear();
        //nextEntity = 1;
    }

    Entity const getEntity(std::string entity_key) {
        return entities.at(entity_key);
    }

    const std::unordered_map<std::string, Entity>& getEntities() const {
        return entities;
    }

    bool entityExists(std::string entity) {
        return entities.contains(entity);
    }
    
private:

    Entity nextEntity{ 1 };
    std::unordered_map<std::string, Entity> entities{ };

};
} // namespace Engine

