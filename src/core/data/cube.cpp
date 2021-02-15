//
// Created by Viktor on 14.2.2021 г..
//

#include "include/cube.h"



Cube::Cube(TextureRegion textureRegion, CubeType type, Shaders* shaders) : textureRegion(textureRegion), type(type){
	GLfloat vertices[6 * 4 * 3] = {
			// Front
			-SIZE, -SIZE,  SIZE, // 0
			SIZE, -SIZE,  SIZE, // 1
			SIZE,  SIZE,  SIZE, // 2
			-SIZE,  SIZE,  SIZE, // 3

			// Back
			-SIZE, -SIZE, -SIZE, // 4
			-SIZE,  SIZE, -SIZE, // 5
			SIZE,  SIZE, -SIZE, // 6
			SIZE, -SIZE, -SIZE, // 7

			// Top
			-SIZE,  SIZE, -SIZE, // 8
			SIZE,  SIZE, -SIZE, // 9
			SIZE,  SIZE,  SIZE, // 10
			-SIZE,  SIZE,  SIZE, // 11

			// Bottom
			-SIZE, -SIZE, -SIZE, // 12
			SIZE, -SIZE, -SIZE, // 13
			SIZE, -SIZE,  SIZE, // 14
			-SIZE, -SIZE,  SIZE, // 15

			// Left
			-SIZE, -SIZE, -SIZE, // 16
			-SIZE, -SIZE,  SIZE, // 17
			-SIZE,  SIZE,  SIZE, // 18
			-SIZE,  SIZE, -SIZE, // 19

			// Right
			SIZE, -SIZE, -SIZE, // 20
			SIZE, -SIZE,  SIZE, // 21
			SIZE,  SIZE,  SIZE, // 22
			SIZE,  SIZE, -SIZE  // 23
	};

	GLuint indices[6 * 6] = {
			0,  1,  2,  2,  3,  0,  // Front
			4,  5,  6,  6,  7,  4,  // Back
			8,  9, 10, 10, 11,  8,  // Top
			12, 13, 14, 14, 15, 12, // Bottom
			16, 17, 18, 18, 19, 16, // Left
			20, 21, 22, 22, 23, 20  // Right
	};

	GLfloat normals[6 * 4 * 3] = {
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

	GLfloat* uvs = textureRegion.getUVs();
	this->shaders = shaders;
	Entity::generateBuffers(vertices, normals, uvs, indices, 6 * 4 * 3, 6 * 6);
	delete uvs;
}

void Cube::draw() {

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureRegion.getTexture()->getBuffer());

	glBindVertexArray(vertexArrayObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBuffer);
	glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, nullptr);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_2D, 0);

}



Cube::~Cube() {
	glDeleteBuffers(1, &indicesBuffer);
	glDeleteVertexArrays(1, &vertexArrayObject);
}


Shaders* Cube::getShaders() {
	return shaders;
}

const Vector3f& Cube::getPosition() const {
	return position;
}


