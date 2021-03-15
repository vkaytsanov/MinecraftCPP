//
// Created by Viktor on 17.2.2021 г..
//

#include "include/chunk_renderer.h"
#include "../../lib/include/lib.h"

ChunkRenderer::ChunkRenderer() : m_texture(AssetManager::getInstance().getSprite("spriteSheet")),
                                 m_defaultChunkShader("textures/shader.vert", "textures/shader.frag") {
}


void ChunkRenderer::beginChunkRendering(Camera* camera, const int renderDistance) {
	m_defaultChunkShader.begin();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture->getBuffer());
	m_defaultChunkShader.setMatrix4("viewMatrix", camera->getTransformMatrix());
	m_defaultChunkShader.setMatrix4("projMatrix", camera->getProjectionMatrix());
	m_defaultChunkShader.setInt("tex_id", 0);
	m_defaultChunkShader.setInt("CHUNK_SIZE_X", CHUNK_SIZE_X);
	m_defaultChunkShader.setInt("CHUNK_SIZE_Z", CHUNK_SIZE_Z);
	m_defaultChunkShader.setInt("renderDistance", renderDistance);
}

void ChunkRenderer::renderChunk(ChunkMesh* chunkMesh, int x, int z) {
	if (chunkMesh->getIndicesCount() > 0) {
		m_defaultChunkShader.setInt("chunkX", x);
		m_defaultChunkShader.setInt("chunkZ", z);
		//std::cout << "Rendering chunk" << std::endl;
		chunkMesh->getVao()->bind();
		glDrawElements(GL_TRIANGLES, chunkMesh->getIndicesCount(), GL_UNSIGNED_INT, nullptr);
		chunkMesh->getVao()->unbind();
	}
}

void ChunkRenderer::renderTransparentChunk(ChunkMesh* chunkMesh, int x, int z) {
	if (chunkMesh->getTransparentIndicesCount() > 0) {
		m_defaultChunkShader.setInt("chunkX", x);
		m_defaultChunkShader.setInt("chunkZ", z);

		chunkMesh->getTransparentVao()->bind();
		glDrawElements(GL_TRIANGLES, chunkMesh->getTransparentIndicesCount(), GL_UNSIGNED_INT, nullptr);
		chunkMesh->getTransparentVao()->unbind();
	}
}

void ChunkRenderer::renderModelChunk(ChunkMesh* chunkMesh, int x, int z) {
	if (chunkMesh->getModelIndicesCount() > 0) {
		m_defaultChunkShader.setInt("chunkX", x);
		m_defaultChunkShader.setInt("chunkZ", z);

		chunkMesh->getModelVao()->bind();
		glDrawElements(GL_TRIANGLES, chunkMesh->getModelIndicesCount(), GL_UNSIGNED_INT, nullptr);
		chunkMesh->getModelVao()->unbind();
	}
}


void ChunkRenderer::endChunkRendering() {
	glBindTexture(GL_TEXTURE_2D, 0);
	m_defaultChunkShader.end();
}





