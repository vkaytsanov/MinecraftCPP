//
// Created by Viktor on 15.2.2021 г..
//

#include "include/cubes_db.h"
#include "cubes/include/grass_cube.h"
#include "cubes/include/dirt_cube.h"


CubesDB::CubesDB(Assets* assets) {
	TextureRegion spriteSheet(assets->getSprite("spriteSheet"));
	regions = spriteSheet.split(32, 32);
	textureShaders = new Shaders("textures/shader.vert", "textures/shader.frag");
	colorShaders = new Shaders("basic/shader.vert", "basic/shader.frag");
	cubes.emplace_back(new DirtCube(regions[3][0], textureShaders));
	cubes.emplace_back(new GrassCube(regions[1][0] + regions[2][0] + regions[3][0], textureShaders));
}

Cube* CubesDB::getCube(CubeType type) {
	return cubes[type];
}

CubesDB::~CubesDB() {
	for(auto& cube : cubes){
		delete cube;
	}
	delete textureShaders;
	delete colorShaders;
	delete regions;

}
