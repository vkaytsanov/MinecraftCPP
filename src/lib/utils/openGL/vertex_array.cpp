//
// Created by Viktor on 17.2.2021 г..
//

#include "include/vertex_array.h"
#include "../../../../../DuckHunt/src/lib/include/lib.h"

VertexArray::VertexArray() {
	glGenVertexArrays(1, &arrayObject);
}

VertexArray::~VertexArray() {
	Lib::app->log("VertexArray", "deleting");
	glDeleteVertexArrays(1, &arrayObject);
}

void VertexArray::bind() const {
	glBindVertexArray(arrayObject);
}

void VertexArray::unbind() const{
	glBindVertexArray(0);
}
