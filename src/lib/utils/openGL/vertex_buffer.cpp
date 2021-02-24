//
// Created by Viktor on 17.2.2021 г..
//

#include "include/vertex_buffer.h"
#include "../../include/lib.h"

VertexBuffer::VertexBuffer() {
	buffer = 0;
	glGenBuffers(1, &buffer);
}

VertexBuffer::~VertexBuffer() {
	glDeleteBuffers(1, &buffer);
	unbind();
}

void VertexBuffer::bufferData(GLsizeiptr size, void* data, GLenum usage) {
	glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}

void VertexBuffer::vertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride,
                                       const GLvoid* pointer) {
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}

void VertexBuffer::bind() {
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
}

void VertexBuffer::unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::vertexAttribIPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid* pointer) {
	glEnableVertexAttribArray(index);
	glVertexAttribIPointer(index, size, type, stride, pointer);
}
