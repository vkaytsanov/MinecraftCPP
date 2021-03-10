//
// Created by Viktor on 6.3.2021 г..
//

#include "include/terrain_system.h"
#include "../components/include/player_controller.h"

using namespace entityx;


TerrainSystem::TerrainSystem(World* world) : m_pWorld(world) {

}

TerrainSystem::~TerrainSystem() {

}


void TerrainSystem::receive(const ChunkRegenerationEvent& cre) {
	buildNewCoordinates(cre.x, cre.z);
}

void TerrainSystem::configure(entityx::EntityManager& entities, entityx::EventManager& events) {
	for (const Entity& entity : entities.entities_with_components<PlayerController>()) {
		m_playerTransform = entity.getComponent<Transform>().get();
		break;
	}

	const int chunkX = static_cast<int>(m_playerTransform->position.x / CHUNK_SIZE_X);
	const int chunkZ = static_cast<int>(m_playerTransform->position.z / CHUNK_SIZE_Z);

	exploreNewCoordinates(entities, chunkX, chunkZ);
	buildNewCoordinates(chunkX, chunkZ);
	m_lastPlayerX = chunkX;
	m_lastPlayerZ = chunkZ;
	events.subscribe<ChunkRegenerationEvent>(*this);
}

void TerrainSystem::update(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) {
	const int chunkX = static_cast<int>(m_playerTransform->position.x / CHUNK_SIZE_X);
	const int chunkZ = static_cast<int>(m_playerTransform->position.z / CHUNK_SIZE_Z);

	if (m_lastPlayerX != chunkX || m_lastPlayerZ != chunkZ) {
		exploreNewCoordinates(entities, chunkX, chunkZ);
		buildNewCoordinates(chunkX, chunkZ);
		m_lastPlayerX = chunkX;
		m_lastPlayerZ = chunkZ;
	}

}

void TerrainSystem::exploreNewCoordinates(entityx::EntityManager& entities, int chunkX, int chunkZ) {
	int counter = 0;
	for (int x = chunkX - EXPLORE_DISTANCE; x < chunkX + EXPLORE_DISTANCE; x++) {
		for (int z = chunkZ - EXPLORE_DISTANCE; z < chunkZ + EXPLORE_DISTANCE; ++z) {
			Chunk* chunk = m_pWorld->addChunk(entities, x, z)->getComponent<Chunk>().get();
			if (chunk->m_chunkState == Empty) {
				m_worldGeneration.generateChunkContents(chunk, x, z);
				counter++;
			}
		}
	}
	Lib::app->log("WorldGeneration", ("Added " + std::to_string(counter) + " m_chunks").c_str());

}

void TerrainSystem::buildNewCoordinates(const int chunkX, const int chunkZ) {
	int counter = 0;
	for (int x = chunkX - BUILD_DISTANCE; x < chunkX + BUILD_DISTANCE; x++) {
		for (int z = chunkZ - BUILD_DISTANCE; z < chunkZ + BUILD_DISTANCE; ++z) {
			ChunkMesh* chunkMesh = m_pWorld->getChunk(x, z)->getComponent<ChunkMesh>().get();
			if (chunkMesh->m_chunkMeshState == UnBuilt) {
				m_worldMeshing.build(ChunksPacked(
						m_pWorld->getChunk(chunkX, z + 1),
						m_pWorld->getChunk(x, z - 1),
						m_pWorld->getChunk(x, z),
						m_pWorld->getChunk(x + 1, z),
						m_pWorld->getChunk(x - 1, z)));
				counter++;
			}
		}
	}
	Lib::app->log("WorldGeneration", ("Constructed " + std::to_string(counter) + " meshes").c_str());
}



