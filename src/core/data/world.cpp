//
// Created by Viktor on 16.2.2021 г..
//

#include "include/world.h"
#include "../components/include/chunk_mesh.h"
#include "../components/include/chunk.h"
#include "../components/include/chunk_aabb.h"

World::World(long long seed) {
	this->seed = seed;
}

entityx::Entity* World::addChunk(entityx::EntityManager& entityManager, int16_t x, int16_t z) {
	Coordinates coords = Coordinates(x, z);
	auto chunkIter = m_chunks.find(coords);
	if (chunkIter == m_chunks.end()) {
		entityx::Entity entity = entityManager.create();
		entity.addComponent<Chunk>();
		entity.addComponent<ChunkMesh>();
		entity.addComponent<ChunkAABB>(Vector3f(CHUNK_SIZE_X, CHUNK_SIZE_Y, CHUNK_SIZE_Z),
		                               Vector3f(x * CHUNK_SIZE_X, 0, z * CHUNK_SIZE_Z));
		m_chunks.try_emplace(coords, entity);
	}
	return &m_chunks.at(coords);
}

entityx::Entity* World::getChunk(int16_t x, int16_t z) {
	Coordinates coords = Coordinates(x, z);
	auto chunk = m_chunks.find(coords);
	if (chunk == m_chunks.end()) return nullptr;
	return &m_chunks.at(Coordinates(x, z));
}


Vector3i World::fromWorldCoordinatesToChunkCoordinates(const Vector3f& position) {
	return Vector3i(static_cast<int>(std::floor(position.x / CHUNK_SIZE_X)),
	                0,
	                static_cast<int>(floor(position.z / CHUNK_SIZE_Z)));
}

Vector3i World::fromWorldCoordinatesToCubeCoordinates(const Vector3i& chunk, const Vector3f& position) {
	return Vector3i(static_cast<int>(std::floor(position.x)) - static_cast<int>(chunk.x * CHUNK_SIZE_X),
	                static_cast<int>(floor(position.y)),
	                static_cast<int>(std::floor(position.z)) - static_cast<int>(chunk.z * CHUNK_SIZE_Z));
}

bool World::tryAddCube(const Vector3i& chunkPos, const Vector3i& cubePos) {
	entityx::Entity* lastChunkEntity = getChunk(chunkPos.x, chunkPos.z);
	Cube* lastCube = &lastChunkEntity->getComponent<Chunk>()->getChunkContents()->at(cubePos.x).at(cubePos.y).at(cubePos.z);
	if (lastCube->m_type == Air) {
		lastCube->m_type = Diamond;
		// update the heightmap
		HeightMap* lastChunkHeightmap = lastChunkEntity->getComponent<Chunk>()->getHeightMap();
		lastChunkHeightmap->at(cubePos.x).at(cubePos.z) = std::max(lastChunkHeightmap->at(cubePos.x).at(cubePos.z), cubePos.y + 1);
		return true;
	}
	return false;
}

bool World::tryRemoveCube(const Vector3i& chunkPos, const Vector3i& cubePos) {
	entityx::Entity* chunkEntity = getChunk(chunkPos.x, chunkPos.z);
	entityx::ComponentHandle<Chunk> chunk = chunkEntity->getComponent<Chunk>();
	ChunkContentsPtr chunkContents = chunk->getChunkContents();
	Cube* cube = &chunkContents->at(cubePos.x).at(cubePos.y).at(cubePos.z);
	if (cube->m_type != Air && !cube->isLiquid()) {
		cube->m_type = Air;
		// update the heightmap
		int level = cubePos.y;
		if (chunk->getHeightMap()->at(cubePos.x).at(cubePos.z) == level) {
			while(chunkContents->at(cubePos.x).at(level).at(cubePos.y).m_type == Air){
				level--;
			}
			chunk->getHeightMap()->at(cubePos.x).at(cubePos.z) = level;
		}
		else {
			level++;
			Cube* upperCube = &chunkContents->at(cubePos.x).at(level).at(cubePos.z);
			if (upperCube->isModel()) {
				upperCube->m_type = Air;
				// update the heightmap
				if (chunk->getHeightMap()->at(cubePos.x).at(cubePos.z) == level) {
					while(chunkContents->at(cubePos.x).at(level).at(cubePos.y).m_type == Air){
						level--;
					}
					chunk->getHeightMap()->at(cubePos.x).at(cubePos.z) = level;
				}
			}
		}
		return true;
	}
	return false;
}

Cube* World::getCubeFromWorldCoordinates(const Vector3f& position) {
	Vector3i chunkPos = fromWorldCoordinatesToChunkCoordinates(position);
	Vector3i cubePos = fromWorldCoordinatesToCubeCoordinates(chunkPos, position);
	return &getChunk(chunkPos.x, chunkPos.z)->getComponent<Chunk>()->getChunkContents()->at(cubePos.x).at(cubePos.y).at(cubePos.z);
}















