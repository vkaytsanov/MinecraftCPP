//
// Created by Viktor on 14.2.2021 г..
//

#ifndef ENTITY_H
#define ENTITY_H

#include "../../../lib/utils/include/shaders.h"

class Entity {
protected:
	Shaders* shaders;
	unsigned int vertexArrayObject;
	unsigned int indicesBuffer;
	unsigned int indicesCount;
	void generateBuffers(GLfloat* vertices, GLfloat* normals, GLfloat* uvs, GLuint* indices, unsigned int verticesCount,
	                     unsigned int indicesCount);
public:
	Entity(Shaders* shaders);
	Shaders* getShaders();

};


#endif //ENTITY_H
