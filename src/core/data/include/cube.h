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
	CubeType type;
	TextureRegion textureRegion;
	Vector3f position;
	Vector3i chunk;
	Shaders* shaders;
public:
	Cube(TextureRegion textureRegion, CubeType type, Shaders* shaders, int sides = 0);
	~Cube();
	void draw();
	Shaders* getShaders();
	const Vector3f& getPosition() const;
};

#endif //CUBE_H
