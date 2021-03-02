//
// Created by Viktor on 17.2.2021 г..
//

#include "include/chunk_mesh.h"
#include "include/chunk.h"
#include "../../../lib/include/lib.h"


ChunkMesh::ChunkMesh() {
	static bool indexBufferInitialized = false;
	static IndexBuffer indexBuffer;
	if (!indexBufferInitialized) {
		indexBufferInitialized = true;
		const unsigned int indices = CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z * 6;
		unsigned int indicesOffset = 0;
		// indices count will be 16 x 256 x 16 x 6 = 393216
		auto* buffer = new GLuint[indices * 6];

		for (int i = 0; i < indices; i += 6) {
			buffer[i + 0] = 0 + indicesOffset;
			buffer[i + 1] = 1 + indicesOffset;
			buffer[i + 2] = 2 + indicesOffset;
			buffer[i + 3] = 2 + indicesOffset;
			buffer[i + 4] = 3 + indicesOffset;
			buffer[i + 5] = 0 + indicesOffset;
			indicesOffset += 4;
		}
		indexBuffer.bind();
		indexBuffer.bufferData(indices * 6 * sizeof(GLuint), buffer, GL_STATIC_DRAW);
		delete[] buffer;
	}

	for (int i = 0; i < vao.size(); i++) {
		vao.at(i).bind();
		vbo.at(i).bind();
		indexBuffer.bind();

		vbo.at(i).vertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		                              (void*) (offsetof(Vertex, position)));
		vbo.at(i).vertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		                              (void*) (offsetof(Vertex, uvs)));
		vbo.at(i).vertexAttribIPointer(2, 1, GL_UNSIGNED_BYTE, sizeof(Vertex),
		                               (void*) offsetof(Vertex, lightningLevel));

		vao.at(i).unbind();
	}

}

ChunkMesh::~ChunkMesh() {

}

void ChunkMesh::setMesh(std::array<std::vector<Vertex>, 3>& vertices) {
	for (int i = 0; i < vertices.size(); i++) {
		indicesCount.at(i) = 0;
		std::string type;
		if(i == 0){
			type = " normal";
		}
		else if(i == 1){
			type = " transparent";
		}
		else{
			type = " model";
		}
		Lib::app->log(("ChunkMesh " + std::to_string(i)).c_str(),
		              (std::to_string(vertices.at(i).size()) + type +
		               " m_vertices").c_str());
		if (!vertices.at(i).empty()) {
			vbo.at(i).bind();
			vbo.at(i).bufferData(vertices.at(i).size() * sizeof(Vertex), &vertices.at(i)[0], GL_STATIC_DRAW);
			indicesCount.at(i) = std::floor(vertices.at(i).size() / 4) * 6;
			vertices.at(i).clear();
		}

	}
}

VertexArray* ChunkMesh::getVao() {
	return &vao.at(0);
}

VertexArray* ChunkMesh::getTransparentVao() {
	return &vao.at(1);
}

VertexArray* ChunkMesh::getModelVao() {
	return &vao.at(2);
}

unsigned int ChunkMesh::getIndicesCount() {
	return indicesCount.at(0);
}

unsigned int ChunkMesh::getTransparentIndicesCount() {
	return indicesCount.at(1);
}

unsigned int ChunkMesh::getModelIndicesCount() {
	return indicesCount.at(2);
}









