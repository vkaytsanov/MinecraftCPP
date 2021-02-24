//
// Created by Viktor on 16.2.2021 г..
//

#ifndef WORLD_H
#define WORLD_H


#include <unordered_map>
#include <map>
#include "chunk.h"

struct Coordinates {
	uint64_t x;
	uint64_t y;
	const int64_t code;

	Coordinates(uint64_t x, uint64_t y) : x(x), y(y), code(toMorton()) {

	}

	uint64_t toMorton() {
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
	std::unordered_map<Coordinates, Chunk, HashPair> chunks;
	void addChunk(int16_t x, int16_t z);
	Chunk* getChunk(int16_t x, int16_t z);
};


#endif //WORLD_H
