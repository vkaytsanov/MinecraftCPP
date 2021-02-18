//
// Created by Viktor on 18.12.2020 г..
//

#include "include/data_system.h"


DataSystem::DataSystem(){
	assets = new Assets();

	CubeDatabase::init(assets->getSprite("spriteSheet"));

	defaultShader = new Shaders("textures/shader.vert", "textures/shader.frag");

	world = new World();
}

DataSystem::~DataSystem() {
	CubeDatabase::freeMemory();
	delete assets;
	delete world;
}


