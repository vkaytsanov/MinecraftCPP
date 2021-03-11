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
		// Add block
		//rayCast(false);
	}

}

void PlayerSystem::rayCast(entityx::EventManager& events, bool destroyBlock) {
	Ray ray(m_playerTransform->eulerAngles.x * MathUtils::DEG2RADIANS,
	        (m_playerTransform->eulerAngles.y + 90) * MathUtils::DEG2RADIANS,
	        m_playerTransform->position);

	while(std::abs(ray.getLength()) < MAX_CUBE_REACH){
		if(m_playerTransform->eulerAngles.y > 0){
			ray.shoot(0.9f);
		}
		else{
			ray.shoot(-0.9f);
		}
		const Vector3i point = {static_cast<int>(ray.getEndPoint().x), static_cast<int>(ray.getEndPoint().y), static_cast<int>(ray.getEndPoint().z)};
		if(point.y < 0 || point.y > CHUNK_SIZE_Y - 1) break;
		Cube* cube = m_pWorld->getCubeFromWorldCoordinates(point.x, point.y, point.z);

		if(cube->m_type != Air && !cube->isLiquid()){
			Lib::app->log("player", "broke cube");
			Lib::app->log("playerx", m_playerTransform->position.x);
			Lib::app->log("playery", m_playerTransform->position.y);
			Lib::app->log("playerz", m_playerTransform->position.z);
			Lib::app->log("x", point.x);
			Lib::app->log("y", point.y);
			Lib::app->log("z", point.z);
			cube->m_type = Air;
			int chunkX = m_playerTransform->position.x / CHUNK_SIZE_X;
			int chunkZ = m_playerTransform->position.z / CHUNK_SIZE_Z;
			m_pWorld->getChunk(chunkX, chunkZ)->getComponent<ChunkMesh>()->m_chunkMeshState = UnBuilt;
			// TODO
			if (point.x == 0) {
				m_pWorld->getChunk(chunkX - 1, chunkZ)->getComponent<ChunkMesh>()->m_chunkMeshState = UnBuilt;
			}
			else if (point.x == CHUNK_SIZE_X - 1) {
				m_pWorld->getChunk(chunkX + 1, chunkZ)->getComponent<ChunkMesh>()->m_chunkMeshState = UnBuilt;
			}

			if (point.z == 0) {
				m_pWorld->getChunk(chunkX, chunkZ - 1)->getComponent<ChunkMesh>()->m_chunkMeshState = UnBuilt;
			}
			else if (point.z == CHUNK_SIZE_Z - 1) {
				m_pWorld->getChunk(chunkX, chunkZ + 1)->getComponent<ChunkMesh>()->m_chunkMeshState = UnBuilt;
			}
			events.post<ChunkRegenerationEvent>(chunkX, chunkZ);
			break;
		}
	}
}

