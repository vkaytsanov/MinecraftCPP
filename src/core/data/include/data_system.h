//
// Created by Viktor on 18.12.2020 г..
//

#ifndef DATA_SYSTEM_H
#define DATA_SYSTEM_H


#include "assets.h"
#include "world.h"
#include "../../../lib/utils/include/shaders.h"

class DataSystem {
public:
	Shaders* defaultShader;
	Assets* assets;
	World* world;
	DataSystem();
	~DataSystem();
};


#endif //DATA_SYSTEM_H
