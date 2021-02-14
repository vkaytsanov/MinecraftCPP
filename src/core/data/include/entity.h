//
// Created by Viktor on 14.2.2021 г..
//

#ifndef ENTITY_H
#define ENTITY_H

#include "../../lib/utils/include/shaders.h"

class Entity {
protected:
	unsigned int vertexArrayObject;
//	unsigned int vertexBuffer;
//	unsigned int normalsBuffer;
//	unsigned int uvBuffer;
//	unsigned int indicesBuffer;
	void generateBuffers(float* vertices, float* normals, float* uvs, float* indices, unsigned int verticesCount,
	                     unsigned int indicesCount);

};


#endif //ENTITY_H
