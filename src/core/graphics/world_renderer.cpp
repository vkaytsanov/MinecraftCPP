//
// Created by Viktor on 17.2.2021 г..
//

#include "include/world_renderer.h"
#include "../../lib/include/lib.h"

WorldRenderer::WorldRenderer(DataSystem* dataSystem, Camera* camera) : world(&dataSystem->world),
                                                                       camera(camera),
                                                                       chunkRenderer(dataSystem) {

}

void WorldRenderer::render() {
	int playerX = (int) camera->m_position.x / CHUNK_SIZE_X;
	int playerZ = (int) camera->m_position.z / CHUNK_SIZE_Z;

	chunkRenderer.beginChunkRendering(camera);
	for (int x = playerX - RENDER_DISTANCE; x < playerX + RENDER_DISTANCE; x++) {
		for (int z = playerZ - RENDER_DISTANCE; z < playerZ + RENDER_DISTANCE; z++) {
			Chunk* chunk = world->getChunk(x, z);
			if(camera->m_frustum.boxInFrustum(chunk->m_frustumAABB)){
				chunkRenderer.renderChunk(chunk, x, z);
			}
		}
	}

	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for (int x = playerX - RENDER_DISTANCE; x < playerX + RENDER_DISTANCE; x++) {
		for (int z = playerZ - RENDER_DISTANCE; z < playerZ + RENDER_DISTANCE; z++) {
			Chunk* chunk = world->getChunk(x, z);
			if(camera->m_frustum.boxInFrustum(chunk->m_frustumAABB)){
				chunkRenderer.renderTransparentChunk(chunk, x, z);
			}
		}
	}

	for (int x = playerX - RENDER_DISTANCE; x < playerX + RENDER_DISTANCE; x++) {
		for (int z = playerZ - RENDER_DISTANCE; z < playerZ + RENDER_DISTANCE; z++) {
			Chunk* chunk = world->getChunk(x, z);
			if(camera->m_frustum.boxInFrustum(chunk->m_frustumAABB)){
				chunkRenderer.renderModelChunk(chunk, x, z);
			}
		}
	}
	chunkRenderer.endChunkRendering();
	glEnable(GL_CULL_FACE);
	glDisable(GL_BLEND);
}

WorldRenderer::~WorldRenderer() {
}


