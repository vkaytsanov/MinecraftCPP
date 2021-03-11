//
// Created by Viktor on 16.2.2021 г..
//

#include "include/world.h"
#include "../../lib/include/lib.h"
#include "../components/include/chunk_mesh.h"
#include "../components/include/chunk.h"
#include "../components/include/frustum_aabb.h"

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
		entity.addComponent<FrustumAABB>(Vector3f(CHUNK_SIZE_X, CHUNK_SIZE_Y, CHUNK_SIZE_Z),
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

Cube* World::getCubeFromWorldCoordinates(Vector3f& point) {
	return nullptr;
}

Vector3i World::fromWorldCoordinatesToChunkCoordinates(const Vector3f& position) {
	return Vector3i(static_cast<int>(std::floor(position.x / CHUNK_SIZE_X)),
	                0,
	                static_cast<int>(floor(position.z / CHUNK_SIZE_Z)));
}

Vector3i World::fromWorldCoordinatesToCubeCoordinates(const Vector3i& chunk, const Vector3f& position) {
	return Vector3i(std::floor(position.x) - static_cast<int>(chunk.x * CHUNK_SIZE_X),
	                static_cast<int>(floor(position.y)),
	                std::floor(position.z) - static_cast<int>(chunk.z * CHUNK_SIZE_Z));
}














