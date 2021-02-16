//
// Created by 1.0fiktor on 16.2.2021 г..
//

#ifndef CUBE_DATA_H
#define CUBE_DATA_H


const float SIZE = 0.5f;

static float vertices[6 * 4 * 3] = {
		// Front
		-SIZE, -SIZE, SIZE, // 0
		SIZE, -SIZE, SIZE, // 1
		SIZE, SIZE, SIZE, // 2
		-SIZE, SIZE, SIZE, // 3

		// Back
		-SIZE, -SIZE, -SIZE, // 4
		-SIZE, SIZE, -SIZE, // 5
		SIZE, SIZE, -SIZE, // 6
		SIZE, -SIZE, -SIZE, // 7

		// Top
		-SIZE, SIZE, -SIZE, // 8
		SIZE, SIZE, -SIZE, // 9
		SIZE, SIZE, SIZE, // 10
		-SIZE, SIZE, SIZE, // 11

		// Bottom
		-SIZE, -SIZE, -SIZE, // 12
		SIZE, -SIZE, -SIZE, // 13
		SIZE, -SIZE, SIZE, // 14
		-SIZE, -SIZE, SIZE, // 15

		// Left
		-SIZE, -SIZE, -SIZE, // 16
		-SIZE, -SIZE, SIZE, // 17
		-SIZE, SIZE, SIZE, // 18
		-SIZE, SIZE, -SIZE, // 19

		// Right
		SIZE, -SIZE, -SIZE, // 20
		SIZE, -SIZE, SIZE, // 21
		SIZE, SIZE, SIZE, // 22
		SIZE, SIZE, -SIZE  // 23
};

static unsigned int indices[6 * 6] = {
		0, 1, 2, 2, 3, 0,  // Front
		4, 5, 6, 6, 7, 4,  // Back
		8, 9, 10, 10, 11, 8,  // Top
		12, 13, 14, 14, 15, 12, // Bottom
		16, 17, 18, 18, 19, 16, // Left
		20, 21, 22, 22, 23, 20  // Right
};

static float normals[6 * 4 * 3] = {
		// Front
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,

		// Back
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,

		// Top
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,

		// Bottom
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,

		// Left
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,

		// Right
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f
};

// u * 3.0f for third part
// u * 2.0f, u2 * 0.67  for second part
// u2 * 0.50f for first part

static float uvs3side[6 * 4 * 2]{
		// front
		1.0f, 1.0f,
		0.50f, 1.0f,
		0.50f, 1.0f,
		1.0f, 1.0f,
		// back
		0.50f, 1.0f,
		0.50f, 1.0f,
		1.0f, 1.0f,
		1.0f, 1.0f,
		// top
		2.0f, 1.0f,
		0.67f, 1.0f,
		0.67f, 1.0f,
		2.0f, 1.0f,
		//bottom
		3.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 1.0f,
		3.0f, 1.0f,
		//left
		1.0f, 1.0f,
		0.50f, 1.0f,
		0.50f, 1.0f,
		1.0f, 1.0f,
		//right
		1.0f, 1.0f,
		0.50f, 1.0f,
		0.50f, 1.0f,
		1.0f, 1.0f,
};


#endif //CUBE_DATA_H
