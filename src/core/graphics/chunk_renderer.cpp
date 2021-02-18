//
// Created by Viktor on 17.2.2021 г..
//

#include "include/chunk_renderer.h"

ChunkRenderer::ChunkRenderer(DataSystem* dataSystem) {
	texture = dataSystem->assets->getSprite("spriteSheet");
	defaultShader = dataSystem->defaultShader;
}

ChunkRenderer::~ChunkRenderer() {
	delete defaultShader;
}

void ChunkRenderer::beginChunkRendering(Camera* camera) {
	defaultShader->begin();
	defaultShader->setMatrix4("proj", camera->combined);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->getBuffer());
	defaultShader->setInt("tex_id", 0);


}

void ChunkRenderer::renderChunk(Chunk* chunk) {
	if(chunk->getChunkMesh()->verticesCount > 0){
		chunk->getChunkMesh()->vertexArray.bind();
		glDrawElements(GL_TRIANGLES, (GLuint) floor(chunk->getChunkMesh()->verticesCount / 4) * 6, GL_UNSIGNED_INT, nullptr);
		chunk->getChunkMesh()->vertexArray.unbind();
	}
}

void ChunkRenderer::endChunkRendering() {

	glBindTexture(GL_TEXTURE_2D, 0);
	defaultShader->end();
}
