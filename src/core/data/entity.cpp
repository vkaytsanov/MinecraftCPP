//
// Created by Viktor on 14.2.2021 г..
//

#include "GL/glew.h"
#include "include/entity.h"

Entity::Entity(Shaders* shaders) : shaders(shaders) {

}

void Entity::generateBuffers(GLfloat* vertices, GLfloat* normals, GLfloat* uvs, GLuint* indices,
                             unsigned int verticesCount, unsigned int indicesCount) {

	this->indicesCount = indicesCount;

	vertexArray.bind();

	VertexBuffer vertexBuffer;
	vertexBuffer.bind();
	vertexBuffer.bufferData(verticesCount * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
	vertexBuffer.vertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	vertexBuffer.unbind();

	VertexBuffer normalsBuffer;
	normalsBuffer.bind();
	normalsBuffer.bufferData(verticesCount * sizeof(GLfloat), normals, GL_STATIC_DRAW);
	normalsBuffer.vertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	normalsBuffer.unbind();

	VertexBuffer uvBuffer;
	uvBuffer.bind();
	uvBuffer.bufferData(verticesCount * 1.5 * sizeof(GLfloat), uvs, GL_STATIC_DRAW);
	uvBuffer.vertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	uvBuffer.unbind();

	indexBuffer.bind();
	indexBuffer.bufferData(indicesCount * sizeof(GLuint), indices, GL_STATIC_DRAW);
	indexBuffer.unbind();

	vertexArray.unbind();
}

Shaders* Entity::getShaders() {
	return shaders;
}


