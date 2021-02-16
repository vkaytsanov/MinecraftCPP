//
// Created by Viktor on 15.2.2021 г..
//

#ifndef CUBES_DB_H
#define CUBES_DB_H


#include <vector>
#include "cube.h"
#include "assets.h"

class CubesDB {
private:
	Cube* cubes[CubeType::TYPES_COUNT];
	Shaders* textureShaders;
	Shaders* colorShaders;
public:
	explicit CubesDB(Assets* assets);
	~CubesDB();
	Cube* getCube(CubeType type);
};


#endif //CUBES_DB_H
