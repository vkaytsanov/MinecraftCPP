//
// Created by Viktor on 16.2.2021 г..
//

#ifndef WORLD_H
#define WORLD_H


#include <unordered_map>
#include <map>
#include "../../../lib/entityx/Entity.h"
#include "../../../lib/utils/geometry/include/vector3.h"
#include "asset_manager.h"



struct Coordinates {
	int64_t m_x;
	int64_t m_y;
	const int64_t code;

	Coordinates(int64_t x, int64_t y) : m_x(x), m_y(y), code(toMorton(x, y)) {

	}

	uint64_t toMorton(int64_t x, int64_t y) {
		x = (x | (x << 16)) & 0x0000FFFF0000FFFF;
		x = (x | (x << 8)) & 0x00FF00FF00FF00FF;
		x = (x | (x << 4)) & 0x0F0F0F0F0F0F0F0F;
		x = (x | (x << 2)) & 0x3333333333333333;
		x = (x | (x << 1)) & 0x5555555555555555;

		y = (y | (y << 16)) & 0x0000FFFF0000FFFF;
		y = (y | (y << 8)) & 0x00FF00FF00FF00FF;
		y = (y | (y << 4)) & 0x0F0F0F0F0F0F0F0F;
		y = (y | (y << 2)) & 0x3333333333333333;
		y = (y | (y << 1)) & 0x5555555555555555;

		return x | y << 1;
	}

	bool operator==(const Coordinates& rhs) const {
		return code == rhs.code;
	}
};

struct HashPair {
	size_t operator()(const Coordinates& coords) const {
		return coords.code;
	}

};

class World {
private:
	long long seed;
public:
	World() = default;
	World(long long seed);
	std::unordered_map<Coordinates, entityx::Entity, HashPair> m_chunks;
	entityx::Entity* addChunk(entityx::EntityManager& entityManager, int16_t x, int16_t z);
	entityx::Entity* getChunk(int16_t x, int16_t z);
	Vector3i fromWorldCoordinatesToChunkCoordinates(const Vector3f& position);
	Vector3i fromWorldCoordinatesToCubeCoordinates(const Vector3i& chunk, const Vector3f& position);
	Cube* getCubeFromWorldCoordinates(Vector3f& point);

};


#endif //WORLD_H
