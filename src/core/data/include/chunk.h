//
// Created by Viktor on 16.2.2021 г..
//

#ifndef CHUNK_H
#define CHUNK_H

#include "cube_type.h"
#include "../../../lib/utils/geometry/include/vector2.h"

#define CHUNK_SIZE_X 16
#define CHUNK_SIZE_Y 16
#define CHUNK_SIZE_Z 16

class Chunk {
private:
	CubeType cubes[CHUNK_SIZE_X][CHUNK_SIZE_Y][CHUNK_SIZE_Z];
	Vector2i position;
public:
	Chunk();
	void generate();
	CubeType getCube(int x, int y, int z);
};


#endif //CHUNK_H
