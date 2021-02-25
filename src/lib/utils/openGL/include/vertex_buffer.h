//
// Created by Viktor on 17.2.2021 г..
//

#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include "GL/glew.h"

class VertexBuffer {
private:
	unsigned int buffer;
public:
	VertexBuffer();
	~VertexBuffer();
	void bufferData(GLsizeiptr size, void* data, GLenum usage);
	void vertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride,
	                         const GLvoid* pointer);
	void vertexAttribIPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid* pointer);
	void bind();
	void unbind();
};


#endif //VERTEX_BUFFER_H
