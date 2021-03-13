//
// Created by Viktor on 10.3.2021 г..
//

#include "include/player_system.h"
#include "../components/include/player_controller.h"
#include "../../lib/utils/geometry/include/ray.h"
#include "../events/chunk_regeneration_event.h"
#include "include/terrain_system.h"


PlayerSystem::PlayerSystem(World* world) : m_pWorld(world) {

}

void PlayerSystem::configure(entityx::EntityManager& entities, entityx::EventManager& events) {
	// create player
	m_player = entities.create();
	m_player.addComponent<PlayerController>();
	m_playerTransform = m_player.addComponent<Transform>(Vector3f(0, 95, 0));

	//m_cameraController.setTransform(m_playerTransform.get());
}

void PlayerSystem::update(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) {
	handleButtons(dt);
	handleMouse(events, dt);
}


void PlayerSystem::handleButtons(float dt) {
	// TODO Inventory etc
}

void PlayerSystem::handleMouse(entityx::EventManager& events, float dt) {
	if (Lib::input->isMouseLeftClick()) {
		// Destroy block
		rayCast(events, true);
	}
	else if (Lib::input->isMouseRightClick()) {
		//Add block
		rayCast(events, false);
	}

}

void PlayerSystem::rayCast(entityx::EventManager& events, bool destroyBlock) {
	Ray ray(m_playerTransform->position,
	        m_playerTransform->forward);
	Vector3f lastPosition;

	m_breakingTimer += Lib::graphics->getDeltaTime();
	if (m_breakingTimer > BREAKING_TIME) {
		for (int i = 0; i < MAX_CUBE_REACH; i++) {
			ray.shoot(1.00f);
			Vector3f position = ray.getEndPoint();
			if (position.y < 0 || position.y > CHUNK_SIZE_Y - 1) break;

			if (destroyBlock) {
				Vector3i chunkPos = m_pWorld->fromWorldCoordinatesToChunkCoordinates(position);
				Vector3i cubePos = m_pWorld->fromWorldCoordinatesToCubeCoordinates(chunkPos, position);
				if (m_pWorld->tryRemoveCube(chunkPos, cubePos)) {
					onRayCastEnd(chunkPos, cubePos);
					events.post<ChunkRegenerationEvent>(chunkPos.x, chunkPos.z);
					m_breakingTimer = 0.0f;
					break;
				}
			}
			else {
				// place block
				Vector3i lastChunkPos = m_pWorld->fromWorldCoordinatesToChunkCoordinates(lastPosition);
				Vector3i lastCubePos = m_pWorld->fromWorldCoordinatesToCubeCoordinates(lastChunkPos, lastPosition);
				if (m_pWorld->tryAddCube(lastChunkPos, lastCubePos)) {
					onRayCastEnd(lastChunkPos, lastCubePos);
					events.post<ChunkRegenerationEvent>(lastChunkPos.x, lastChunkPos.z);
					m_breakingTimer = 0.0f;
					break;
				}
				lastPosition = position;
			}
		}
	}
}

void PlayerSystem::onRayCastEnd(const Vector3i& chunkPos, const Vector3i& cubePos) {
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

