//
// Created by Viktor on 16.2.2021 г..
//

#ifndef WORLD_H
#define WORLD_H


#include "chunk.h"
#include <map>

class World {
public:
	std::vector<Chunk> chunks;
	Chunk* getChunk(int x);
	explicit World();
	~World();
	void generate();
};


#endif //WORLD_H
