//
// Created by Viktor on 16.2.2021 г..
//

#include "include/world.h"
#include "../../lib/include/lib.h"

World::World(long long seed) {
	this->seed = seed;
}

void World::addChunk(int16_t x, int16_t z) {
	Coordinates coords = Coordinates(x, z);
	auto chunkIter = chunks.find(coords);
	if (chunkIter == chunks.end()) {
		chunks.try_emplace(coords);
	}
}

Chunk* World::getChunk(int16_t x, int16_t z) {
	Coordinates coords = Coordinates(x, z);
	auto chunk = chunks.find(coords);
	if (chunk == chunks.end()) return nullptr;
	return &chunks.at(Coordinates(x, z));
}













