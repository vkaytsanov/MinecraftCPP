//
// Created by Viktor on 17.2.2021 г..
//

#include "include/chunk_mesh.h"
#include "../../lib/include/lib.h"


ChunkMesh::ChunkMesh() : m_chunkMeshState(UnBuilt){
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

	for (int i = 0; i < m_vao.size(); i++) {
		m_vao.at(i).bind();
		m_vbo.at(i).bind();
		indexBuffer.bind();

		m_vbo.at(i).vertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		                                (void*) (offsetof(Vertex, position)));
		m_vbo.at(i).vertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		                                (void*) (offsetof(Vertex, uvs)));
		m_vbo.at(i).vertexAttribIPointer(2, 1, GL_UNSIGNED_BYTE, sizeof(Vertex),
		                                 (void*) offsetof(Vertex, lightningLevel));

		m_vao.at(i).unbind();
	}

}

void ChunkMesh::setMesh(std::array<std::vector<Vertex>, 3>& vertices) {
	for (int i = 0; i < vertices.size(); i++) {
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
//		Lib::app->log(("ChunkMesh " + std::to_string(i)).c_str(),
//		              (std::to_string(vertices.at(i).size()) + cubeType +
//		               " m_vertices").c_str());
		if (!vertices.at(i).empty()) {
			m_vbo.at(i).bind();
			m_vbo.at(i).bufferData(vertices.at(i).size() * sizeof(Vertex), &vertices.at(i)[0], GL_STATIC_DRAW);
			m_indicesCount.at(i) = std::floor(vertices.at(i).size() / 4) * 6;
			vertices.at(i).clear();
		}
		else{
			m_indicesCount.at(i) = 0;
		}

	}
}

VertexArray* ChunkMesh::getVao() {
	return &m_vao.at(0);
}

VertexArray* ChunkMesh::getTransparentVao() {
	return &m_vao.at(1);
}

VertexArray* ChunkMesh::getModelVao() {
	return &m_vao.at(2);
}

unsigned int ChunkMesh::getIndicesCount() {
	return m_indicesCount.at(0);
}

unsigned int ChunkMesh::getTransparentIndicesCount() {
	return m_indicesCount.at(1);
}

unsigned int ChunkMesh::getModelIndicesCount() {
	return m_indicesCount.at(2);
}









