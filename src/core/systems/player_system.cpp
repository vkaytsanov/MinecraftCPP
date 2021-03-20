//
// Created by Viktor on 10.3.2021 г..
//

#include "include/player_system.h"
#include "../components/include/player_controller.h"

#include "../events/chunk_regeneration_event.h"
#include "include/terrain_system.h"


Vector3f PlayerSystem::m_sHitBoxCube;
bool PlayerSystem::m_sIsRayHit = false;

PlayerSystem::PlayerSystem(World* world) : m_pWorld(world){

}

void PlayerSystem::configure(entityx::EntityManager& entities, entityx::EventManager& events) {
	// create player
	m_player = entities.create();
	m_player.addComponent<PlayerController>();
	m_playerTransform = m_player.addComponent<Transform>(Vector3f(0, 100, 0));
	m_playerRigidBody = m_player.addComponent<RigidBody>();
	m_playerBoxCollider = m_player.addComponent<BoxCollider>(Vector3f(0.75f, 1.65f, 0.75f));

}

void PlayerSystem::update(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) {
	handleButtons(dt);
	handleMouse(events, dt);
}


void PlayerSystem::handleButtons(float dt) {
	// TODO Inventory etc
	handleButtonMovement(dt);
}

void PlayerSystem::handleMouse(entityx::EventManager& events, float dt) {
	if (Lib::input->isKeyPressed(SDLK_ESCAPE)) {
		m_shouldMouseMove = !m_shouldMouseMove;
	}
	if (m_shouldMouseMove){
		handleMouseMovement(dt);

		m_breakingTimer += dt;
		rayCast();
	}

	if (Lib::input->isMouseLeftClick()) {
		// Destroy block
		editBlock(events, true);
	}
	else if (Lib::input->isMouseRightClick()) {
		//Add block
		editBlock(events, false);
	}

}

void PlayerSystem::rayCast() {
	m_sIsRayHit = false;
	m_ray = Ray(m_playerTransform->position, m_playerTransform->forward);

	for (int i = 0; i < MAX_CUBE_REACH; i++) {
		m_ray.step();
		m_sHitBoxCube = Vector3f::floor(m_ray.getEndPoint());

		if (m_sHitBoxCube.y < 0 || m_sHitBoxCube.y > CHUNK_SIZE_Y - 1) break;
		Vector3i chunkPos = m_pWorld->fromWorldCoordinatesToChunkCoordinates(m_sHitBoxCube);
		Vector3i cubePos = m_pWorld->fromWorldCoordinatesToCubeCoordinates(chunkPos, m_sHitBoxCube);
		entityx::Entity* chunkEntity = m_pWorld->getChunk(chunkPos.x, chunkPos.z);
		entityx::ComponentHandle<Chunk> chunk = chunkEntity->getComponent<Chunk>();
		ChunkContentsPtr chunkContents = chunk->getChunkContents();
		Cube* cube = &chunkContents->at(cubePos.x).at(cubePos.y).at(cubePos.z);
		if (cube->m_type != Air && !cube->isLiquid()) {
			m_sIsRayHit = true;

			break;
		}
	}
}

void PlayerSystem::onEditBlockEnd(const Vector3i& chunkPos, const Vector3i& cubePos) {
	m_pWorld->getChunk(chunkPos.x, chunkPos.z)->getComponent<ChunkMesh>()->m_chunkMeshState = UnBuilt;

	if (cubePos.x == 0) {
		m_pWorld->getChunk(chunkPos.x - 1, chunkPos.z)->getComponent<ChunkMesh>()->m_chunkMeshState = UnBuilt;
	}
	else if (cubePos.x == CHUNK_SIZE_X - 1) {
		m_pWorld->getChunk(chunkPos.x + 1, chunkPos.z)->getComponent<ChunkMesh>()->m_chunkMeshState = UnBuilt;
	}
	if (cubePos.z == 0) {
		m_pWorld->getChunk(chunkPos.x, chunkPos.z - 1)->getComponent<ChunkMesh>()->m_chunkMeshState = UnBuilt;
	}
	else if (cubePos.z == CHUNK_SIZE_Z - 1) {
		m_pWorld->getChunk(chunkPos.x, chunkPos.z + 1)->getComponent<ChunkMesh>()->m_chunkMeshState = UnBuilt;
	}

}

void PlayerSystem::handleButtonMovement(float dt) {
	float horizontalInput = 0.0f;
	float verticalInput = 0.0f;

	if (Lib::input->isKeyPressed(SDLK_a)) {
		horizontalInput -= (CHARACTER_MOVEMENT_THRUST);
	}
	if (Lib::input->isKeyPressed(SDLK_d)) {
		horizontalInput += (CHARACTER_MOVEMENT_THRUST);
	}
	if (Lib::input->isKeyPressed(SDLK_w)) {
		verticalInput -= (CHARACTER_MOVEMENT_THRUST);
	}
	if (Lib::input->isKeyPressed(SDLK_s)) {
		verticalInput += (CHARACTER_MOVEMENT_THRUST);
	}
	if(Lib::input->isKeyPressed(SDLK_SPACE) && m_playerRigidBody->m_isGrounded){
		m_playerRigidBody->addForceImpulse(Vector3f(0, 1, 0) * CHARACTER_JUMPING_THRUST);
		m_playerRigidBody->m_isGrounded = false;
	}

	if (horizontalInput != 0.0f || verticalInput != 0.0f) {
		Vector3f totalForce = m_playerTransform->forward * verticalInput + m_playerTransform->right * horizontalInput;
		// so it doesnt fly when the forward vector is pointing the sky or ground
		totalForce.y = 0;
		m_playerRigidBody->addForce(totalForce);
	}
}

void PlayerSystem::handleMouseMovement(float dt) {
	if (!m_firstTimeMovingMouse) {
		float xRot = -(Lib::input->getMouseDeltaY()) * dt * CAMERA_MOVEMENT_INTENSITY;
		float yRot = (Lib::input->getMouseDeltaX()) * dt * CAMERA_MOVEMENT_INTENSITY;
		m_playerTransform->rotateClampX(Vector3f(xRot, yRot, 0), 90.0f);
	}
	else {
		m_firstTimeMovingMouse = false;
	}
	Lib::input->resetMouse();
}

void PlayerSystem::editBlock(entityx::EventManager& events, bool destroy) {
	if(m_sIsRayHit){
		if(m_breakingTimer < BREAKING_TIME) return;

		if(destroy){
			Vector3i chunkPos = m_pWorld->fromWorldCoordinatesToChunkCoordinates(m_sHitBoxCube);
			Vector3i cubePos = m_pWorld->fromWorldCoordinatesToCubeCoordinates(chunkPos, m_sHitBoxCube);
			if (m_pWorld->tryRemoveCube(chunkPos, cubePos)) {
				onEditBlockEnd(chunkPos, cubePos);
				events.post<ChunkRegenerationEvent>(chunkPos.x, chunkPos.z);
				m_breakingTimer = 0.0f;
			}
		}
		else{
			m_sHitBoxCube = m_ray.getEndPoint() + m_ray.getNormal();
			// place block
			Vector3i lastChunkPos = m_pWorld->fromWorldCoordinatesToChunkCoordinates(m_sHitBoxCube);
			Vector3i lastCubePos = m_pWorld->fromWorldCoordinatesToCubeCoordinates(lastChunkPos, m_sHitBoxCube);
			if (m_pWorld->tryAddCube(lastChunkPos, lastCubePos)) {
				onEditBlockEnd(lastChunkPos, lastCubePos);
				events.post<ChunkRegenerationEvent>(lastChunkPos.x, lastChunkPos.z);
				m_breakingTimer = 0.0f;
			}
		}
	}
}
