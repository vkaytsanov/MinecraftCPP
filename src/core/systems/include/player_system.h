//
// Created by Viktor on 10.3.2021 г..
//

#ifndef PLAYER_SYSTEM_H
#define PLAYER_SYSTEM_H


#include "../../../lib/entityx/System.h"
#include "../../data/include/world.h"
#include "../../components/include/transform.h"
#include "../../components/include/rigid_body.h"
#include "../../../lib/utils/camera/include/first_person_camera_controller.h"

class PlayerSystem : public entityx::System<PlayerSystem>{
private:
	const float CAMERA_MOVEMENT_INTENSITY = 25.f;
	const float CHARACTER_MOVEMENT_THRUST = 20.f;
	const float CHARACTER_JUMPING_THRUST = 5.0f;
	// ray casting
	const int MAX_CUBE_REACH = 3;
	const float BREAKING_TIME = 0.10f;
	bool m_firstTimeMovingMouse = true;
	bool shouldMouseMove = true;

	float m_breakingTimer = 0.0f;
	World* m_pWorld;
	entityx::Entity m_player;
	entityx::ComponentHandle<Transform> m_playerTransform;
	entityx::ComponentHandle<RigidBody> m_playerRigidBody;

	void handleButtons(float dt);
	void handleMouse(entityx::EventManager& events, float dt);
	void handleButtonMovement(float dt);
	void handleMouseMovement(float dt);
	void rayCast(entityx::EventManager& events, bool destroyBlock);
	void onRayCastEnd(const Vector3i& chunkPos, const Vector3i& cubePos);
public:
	PlayerSystem(World* world);
	void configure(entityx::EntityManager& entities, entityx::EventManager& events) override;
	void update(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) override;

};


#endif //PLAYER_SYSTEM_H
