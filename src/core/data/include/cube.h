//
// Created by Viktor on 14.2.2021 г..
//

#ifndef CUBE_H
#define CUBE_H

#include "../../../lib/utils/geometry/include/vector3.h"
#include "../../../lib/utils/geometry/include/vector2.h"
#include "../../../lib/utils/include/texture_region.h"
#include "cube_type.h"
#include "entity.h"



class Cube : public Entity{
private:
	TextureRegion textureRegion;
public:
	Cube(TextureRegion textureRegion, Shaders* shaders, int sides = 0);
	~Cube();
	void draw();
};

#endif //CUBE_H
