//
// Created by Viktor on 16.2.2021 г..
//

#include "include/world.h"

World::World() {
	chunk = new Chunk();
	chunk->generate();
}
