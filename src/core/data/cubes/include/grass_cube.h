//
// Created by Viktor on 15.2.2021 г..
//

#ifndef GRASS_CUBE_H
#define GRASS_CUBE_H


#include "../../include/cube.h"



class GrassCube : public Cube{
public:
	GrassCube(TextureRegion texture, Shaders* shaders);
};


#endif //GRASS_CUBE_H
