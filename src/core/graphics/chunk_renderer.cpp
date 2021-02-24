//
// Created by Viktor on 17.2.2021 г..
//

#include "include/chunk_renderer.h"
#include "../../lib/include/lib.h"

ChunkRenderer::ChunkRenderer(DataSystem* dataSystem) {
	texture = dataSystem->assets.getSprite("spriteSheet");
	defaultShader = &dataSystem->defaultShader;
}

ChunkRenderer::~ChunkRenderer() {
}

void ChunkRenderer::beginChunkRendering(Camera* camera) {
	defaultShader->begin();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->getBuffer());
	defaultShader->setMatrix4("proj", camera->combined);
	defaultShader->setInt("tex_id", 0);
	defaultShader->setInt("CHUNK_SIZE_X", CHUNK_SIZE_X);
	defaultShader->setInt("CHUNK_SIZE_Z", CHUNK_SIZE_Z);
}

void ChunkRenderer::renderChunk(Chunk* chunk, int x, int z) {
	if(chunk->getChunkMesh()->getIndicesCount() > 0){
		defaultShader->setInt("chunkX", x);
		defaultShader->setInt("chunkZ", z);

		chunk->getChunkMesh()->getVao()->bind();
		glDrawElements(GL_TRIANGLES, chunk->getChunkMesh()->getIndicesCount(), GL_UNSIGNED_INT, nullptr);
		chunk->getChunkMesh()->getVao()->unbind();
	}
}

void ChunkRenderer::renderTransparentChunk(Chunk* chunk, int x, int z) {
	if(chunk->getChunkMesh()->getTransparentIndicesCount() > 0){
		defaultShader->setInt("chunkX", x);
		defaultShader->setInt("chunkZ", z);

		chunk->getChunkMesh()->getTransparentVao()->bind();
		glDrawElements(GL_TRIANGLES, chunk->getChunkMesh()->getTransparentIndicesCount(), GL_UNSIGNED_INT, nullptr);
		chunk->getChunkMesh()->getTransparentVao()->unbind();
	}
}


void ChunkRenderer::endChunkRendering() {

	glBindTexture(GL_TEXTURE_2D, 0);
	defaultShader->end();
}

