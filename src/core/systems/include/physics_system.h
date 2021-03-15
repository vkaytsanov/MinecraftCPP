//
// Created by Viktor on 13.3.2021 г..
//

#ifndef PHYSICS_SYSTEM_H
#define PHYSICS_SYSTEM_H


#include "../../../lib/entityx/System.h"
#include "../../components/include/transform.h"
#include "../../components/include/rigid_body.h"
#include "chunk_renderer.h"
#include "../../data/include/world.h"
#include "../../components/include/box_collider.h"

class PhysicsSystem : public entityx::System<PhysicsSystem>{
private:
	const float GRAVITY_CONSTANT = 9.81f;
	const float FRICTION_CONSTANT = 2.32;
	const int SIMULATING_DISTANCE = 6;
	World* m_pWorld;
	/** simulating only around the player */
	Transform* m_pPlayerTransform;

	void applyForce(RigidBody* rigidBody, float dt);
	void applyGravity(RigidBody* rigidBody, float dt);
	void handleCollision(RigidBody* rigidBody, Transform* transform, BoxCollider* boxCollider, Vector3f& acceleration);
public:
	PhysicsSystem(World* world);
	void configure(entityx::EntityManager& entities, entityx::EventManager& events) override;
	void preUpdate(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) override;
	void update(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) override;
};


#endif //PHYSICS_SYSTEM_H
