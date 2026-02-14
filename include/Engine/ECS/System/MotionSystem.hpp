#pragma once

#include <tuple>

#include <Engine/ECS/System/BaseSystem.hpp>

namespace Engine {

class MotionSystem {
public:

	enum TransType : bool {
		isSingleTrans = false,
		isMultiTrans = true,
	};

	enum VelType : bool {
		isSingleVel = false,
		isMultiVel = true,
	};

	enum ColType : bool {
		noCollider = false,
		hasCollider = true,
	};

	MotionSystem() = default;
	~MotionSystem() = default;

	void init(const EntityManager* entityManager, ComponentManager* componentManager);

	void movementUpdate(const EntityManager* entityManager, ComponentManager* componentManager);

	// Overloaded functions

	void create(const SystemContext& ctx);

	void update(const SystemContext& ctx);

	void render(const SystemContext& ctx);

	void quit(const SystemContext& ctx);

private:
	std::unordered_map<Entity, std::tuple<TransType, VelType, ColType>> _entities; // Entities within for the movemment system
};

}
