//
// Created by Viktor on 14.2.2021 г..
//

#ifndef CUBE_H
#define CUBE_H

#include "../../lib/utils/geometry/include/vector3.h"
#include "../../../lib/utils/geometry/include/vector2.h"
#include "../../lib/utils/include/shaders.h"
#include "cube_type.h"
#include "entity.h"

static const float SIZE = 16.0f;

static GLfloat vertices[6 * 4 * 3] = {
		// Front
		-SIZE / 2.0f, -SIZE / 2.0f,  SIZE / 2.0f, // 0
		 SIZE / 2.0f, -SIZE / 2.0f,  SIZE / 2.0f, // 1
		 SIZE / 2.0f,  SIZE / 2.0f,  SIZE / 2.0f, // 2
		-SIZE / 2.0f,  SIZE / 2.0f,  SIZE / 2.0f, // 3

		// Back
		-SIZE / 2.0f, -SIZE / 2.0f, -SIZE / 2.0f, // 4
		-SIZE / 2.0f,  SIZE / 2.0f, -SIZE / 2.0f, // 5
		 SIZE / 2.0f,  SIZE / 2.0f, -SIZE / 2.0f, // 6
		 SIZE / 2.0f, -SIZE / 2.0f, -SIZE / 2.0f, // 7

		// Top
		-SIZE / 2.0f,  SIZE / 2.0f, -SIZE / 2.0f, // 8
		 SIZE / 2.0f,  SIZE / 2.0f, -SIZE / 2.0f, // 9
		 SIZE / 2.0f,  SIZE / 2.0f,  SIZE / 2.0f, // 10
		-SIZE / 2.0f,  SIZE / 2.0f,  SIZE / 2.0f, // 11

		// Bottom
		-SIZE / 2.0f, -SIZE / 2.0f, -SIZE / 2.0f, // 12
		 SIZE / 2.0f, -SIZE / 2.0f, -SIZE / 2.0f, // 13
		 SIZE / 2.0f, -SIZE / 2.0f,  SIZE / 2.0f, // 14
		-SIZE / 2.0f, -SIZE / 2.0f,  SIZE / 2.0f, // 15

		// Left
		-SIZE / 2.0f, -SIZE / 2.0f, -SIZE / 2.0f, // 16
		-SIZE / 2.0f, -SIZE / 2.0f,  SIZE / 2.0f, // 17
		-SIZE / 2.0f,  SIZE / 2.0f,  SIZE / 2.0f, // 18
		-SIZE / 2.0f,  SIZE / 2.0f, -SIZE / 2.0f, // 19

		 // Right
		 SIZE / 2.0f, -SIZE / 2.0f, -SIZE / 2.0f, // 20
		 SIZE / 2.0f, -SIZE / 2.0f,  SIZE / 2.0f, // 21
		 SIZE / 2.0f,  SIZE / 2.0f,  SIZE / 2.0f, // 22
		 SIZE / 2.0f,  SIZE / 2.0f, -SIZE / 2.0f  // 23
};

static float indices[6 * 6] = {
		0,  1,  2,  2,  3,  0,  // Front
		4,  5,  6,  6,  7,  4,  // Back
		8,  9, 10, 10, 11,  8,  // Top
		12, 13, 14, 14, 15, 12, // Bottom
		16, 17, 18, 18, 19, 16, // Left
		20, 21, 22, 22, 23, 20  // Right
};

static float normals[6 * 4 * 3] = {
		// Front
		0.0f,  0.0f,  1.0f,
		0.0f,  0.0f,  1.0f,
		0.0f,  0.0f,  1.0f,
		0.0f,  0.0f,  1.0f,

		// Back
		0.0f,  0.0f, -1.0f,
		0.0f,  0.0f, -1.0f,
		0.0f,  0.0f, -1.0f,
		0.0f,  0.0f, -1.0f,

		// Top
		0.0f,  1.0f,  0.0f,
		0.0f,  1.0f,  0.0f,
		0.0f,  1.0f,  0.0f,
		0.0f,  1.0f,  0.0f,

		// Bottom
		0.0f, -1.0f,  0.0f,
		0.0f, -1.0f,  0.0f,
		0.0f, -1.0f,  0.0f,
		0.0f, -1.0f,  0.0f,

		// Left
		-1.0f,  0.0f,  0.0f,
		-1.0f,  0.0f,  0.0f,
		-1.0f,  0.0f,  0.0f,
		-1.0f,  0.0f,  0.0f,

		// Right
		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f
};

static float uvs[6 * 4 * 2] = {
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,

		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,

		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,

		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,

		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,

		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f
};

class Cube : public Entity{
private:
	CubeType type;
	Vector3f position;
	Vector2i chunk;
	Shaders* shaders;
public:
	Cube(CubeType type);
};


#endif //CUBE_H
