//
// Created by Viktor on 14.2.2021 г..
//

#ifndef ENTITY_H
#define ENTITY_H

#include "../../../lib/utils/include/shaders.h"
#include "../../../lib/utils/openGL/include/vertex_array.h"
#include "../../../lib/utils/openGL/include/index_buffer.h"
#include "../../../lib/utils/openGL/include/vertex_buffer.h"

class Entity {
protected:
	Shaders* shaders;
	VertexArray vertexArray;
	IndexBuffer indexBuffer;
	unsigned int indicesCount;
	void generateBuffers(GLfloat* vertices, GLfloat* normals, GLfloat* uvs, GLuint* indices, unsigned int verticesCount,
	                     unsigned int indicesCount);
public:
	explicit Entity(Shaders* shaders);
	Shaders* getShaders();

};


#endif //ENTITY_H
