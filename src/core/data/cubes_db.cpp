//
// Created by Viktor on 15.2.2021 г..
//

#include "include/cubes_db.h"
#include "cubes/include/grass_cube.h"
#include "cubes/include/dirt_cube.h"


CubesDB::CubesDB(Assets* assets) {
	const int SPRITE_SIZE = 32;

	TextureRegion spriteSheet(assets->getSprite("spriteSheet"));
	TextureRegion** regions = spriteSheet.split(SPRITE_SIZE, SPRITE_SIZE);

	textureShaders = new Shaders("textures/shader.vert", "textures/shader.frag");
	colorShaders = new Shaders("basic/shader.vert", "basic/shader.frag");

	cubes[CubeType::Dirt] = new DirtCube(regions[3][0], textureShaders);
	cubes[CubeType::Grass] = new GrassCube(regions[1][0] + regions[2][0] + regions[3][0], textureShaders);

	const int regionsSize = spriteSheet.getTexture()->getWidth() / SPRITE_SIZE;
	for(int i = 0; i < regionsSize; i++){
		delete[] regions[i];
	}
	delete[] regions;
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


}
