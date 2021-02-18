//
// Created by Viktor on 16.2.2021 г..
//

#include "include/world.h"

World::World() {
}

void World::generate() {
	chunks.emplace_back();


}

World::~World() {

}

Chunk* World::getChunk(int x) {
	return &chunks[x];
}
