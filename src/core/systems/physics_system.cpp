//
// Created by Viktor on 13.3.2021 г..
//

#include "include/physics_system.h"
#include "../components/include/player_controller.h"


PhysicsSystem::PhysicsSystem(World* world) : m_pWorld(world){

}

void PhysicsSystem::configure(entityx::EntityManager& entities, entityx::EventManager& events) {
	for (const auto& entity : entities.entities_with_components<PlayerController>()) {
		m_pPlayerTransform = entity.getComponent<Transform>().get();
	}
}

void PhysicsSystem::preUpdate(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) {
	for(const auto& entity : entities.entities_with_components<RigidBody>()){
		entityx::ComponentHandle<RigidBody> rigidBody = entity.getComponent<RigidBody>();
		if(rigidBody->m_isActive){
			entityx::ComponentHandle<Transform> transform = entity.getComponent<Transform>();

			//rigidBody->m_velocity = Vector3f(0, 0, 0);
			applyForce(rigidBody.get(), dt);

			if(rigidBody->m_useGravity){
				applyGravity(rigidBody.get(), dt);
			}
			Vector3f acceleration = rigidBody->m_velocity * dt;
			if(entity.has_component<BoxCollider>()){
				entityx::ComponentHandle<BoxCollider> boxCollider = entity.getComponent<BoxCollider>();
				// so we dont have to update the camera position to be on the top of the bounding box
				boxCollider->updateInverse(transform->position);
				handleCollision(rigidBody.get(), transform.get(), boxCollider.get(), acceleration);
			}
			transform->translate(rigidBody->m_velocity * dt);
		}
	}
}

void PhysicsSystem::update(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) {

}

void PhysicsSystem::applyForce(RigidBody* rigidBody, float dt) {
	float drag = 1.00f - rigidBody->m_drag * dt;
	if(drag < 0.00f) drag = 0.00f;
	rigidBody->m_velocity *= Vector3f(drag, 1, drag);
	if(std::abs(rigidBody->m_velocity.x) < 0.05f) rigidBody->m_velocity.x = 0.0f;
	if(std::abs(rigidBody->m_velocity.y) < 0.05f) rigidBody->m_velocity.y = 0.0f;
	if(std::abs(rigidBody->m_velocity.z) < 0.05f) rigidBody->m_velocity.z = 0.0f;
}

void PhysicsSystem::applyGravity(RigidBody* rigidBody, float dt) {
	float gravityForce =  rigidBody->m_mass * -GRAVITY_CONSTANT;
	rigidBody->m_velocity.y += gravityForce * dt;
}

void PhysicsSystem::handleCollision(RigidBody* rigidBody, Transform* transform, BoxCollider* boxCollider, Vector3f& acceleration) {
	static BoxCollider cubeCollider(Vector3f(1, 1, 1));

	// check for collision on X axis
	if(rigidBody->m_velocity.x != 0.0f) {
		Vector3f cubePos = Vector3f(transform->position.x + acceleration.x, boxCollider->m_boundingBox.min.y + boxCollider->m_dimensions.y / 2, transform->position.z);
		Cube* cube = m_pWorld->getCubeFromWorldCoordinates(cubePos);

		if (cube->isCollidable()) {
			cubeCollider.update(Vector3f::floor(cubePos));
			if (cubeCollider.intersectsWith(boxCollider)) {
				if(rigidBody->m_velocity.x < 0.00f){
					transform->position.x = transform->position.x + 0.05f;
				}
				else{
					transform->position.x = transform->position.x - 0.05f;
				}
				rigidBody->m_velocity.x = 0;
			}
		}
	}
	// check for collision on Y axis
	if(rigidBody->m_velocity.y != 0.0f) {
		Vector3f cubePos = Vector3f(transform->position.x, boxCollider->m_boundingBox.min.y + acceleration.y, transform->position.z);
		Cube* cube = m_pWorld->getCubeFromWorldCoordinates(cubePos);
		if (cube->isCollidable()) {
			cubeCollider.update(Vector3f::floor(cubePos));
			if (cubeCollider.intersectsWith(boxCollider)) {
				transform->position.y = boxCollider->m_dimensions.y + boxCollider->m_boundingBox.min.y;
				rigidBody->m_velocity.y = 0;
				rigidBody->m_isGrounded = true;
			}
		}
	}
	// check for collision on Z axis
	if(rigidBody->m_velocity.z != 0.0f) {
		Vector3f cubePos = Vector3f(transform->position.x, boxCollider->m_boundingBox.min.y + boxCollider->m_dimensions.y / 2, transform->position.z + acceleration.z);
		Cube* cube = m_pWorld->getCubeFromWorldCoordinates(cubePos);
		if (cube->isCollidable()) {
			cubeCollider.update(Vector3f::floor(cubePos));
			if (cubeCollider.intersectsWith(boxCollider)) {
				if(rigidBody->m_velocity.z < 0.00f){
					transform->position.z = transform->position.z + 0.05f;
				}
				else{
					transform->position.z = transform->position.z - 0.05f;
				}
				rigidBody->m_velocity.z = 0;
			}
		}
	}
}




