//
// Created by Viktor on 18.12.2020 г..
//

#include "include/data_system.h"


DataSystem::DataSystem() : defaultShader("textures/shader.vert", "textures/shader.frag"){
	CubeDatabase::init(assets.getSprite("spriteSheet"));
}

DataSystem::~DataSystem() {
	CubeDatabase::freeMemory();

}

