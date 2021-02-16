//
// Created by Viktor on 16.2.2021 г..
//

#ifndef DIRT_CUBE_H
#define DIRT_CUBE_H

#include "../../include/cube.h"

class DirtCube : public Cube{
public:
	DirtCube(TextureRegion texture, Shaders* shaders);
};


#endif //DIRT_CUBE_H
