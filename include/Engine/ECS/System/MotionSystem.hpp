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

	enum AccelType : uint8_t {
		noAccel = 0,
		isSingleAccel = 1,
		isMultiAccel = 2,
	};

	enum ColType : bool {
		noCollider = false,
		hasCollider = true,
	};

	struct MotionObject {
		TransType transformationType{ isSingleTrans };
		VelType velocityType{ isSingleVel };
		AccelType accelerationType{ isSingleAccel };
		ColType colliderType{ noCollider };

		MotionObject(TransType t = isSingleTrans, VelType v = isSingleVel, AccelType a = noAccel, ColType c = noCollider)
			: transformationType(t), velocityType(v), accelerationType(a), colliderType(c) {}
	};

	MotionSystem() = default;
	~MotionSystem() = default;

	void initMotion(const EntityManager* entityManager, ComponentManager* componentManager);

	/// @brief Checks for any collider objects were removed or created
	/// @param entityManager For checking whether entities were removed
	/// @param componentManager For the init of the component manager
	void updateEntities(EntityManager* entityManager, ComponentManager* componentManager);

	void movementUpdate(const EntityManager* entityManager, ComponentManager* componentManager);

	// Overloaded functions

	void create(const SystemContext& ctx);

	void update(const SystemContext& ctx);

	void render(const SystemContext& ctx);

	void quit(const SystemContext& ctx);

private:
	std::unordered_map<Entity, MotionObject> _entities; // Entities within for the movemment system
};

}
