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
	int playerX = (int) camera->position->x / CHUNK_SIZE_X;
	int playerZ = (int) camera->position->z / CHUNK_SIZE_Z;

	glEnable(GL_CULL_FACE);

	chunkRenderer.beginChunkRendering(camera);
	for (int x = playerX - RENDER_DISTANCE; x < playerX + RENDER_DISTANCE; x++) {
		for (int z = playerZ - RENDER_DISTANCE; z < playerZ + RENDER_DISTANCE; z++) {
			chunkRenderer.renderChunk(world->getChunk(x, z), x, z);
		}
	}

	glDisable(GL_CULL_FACE);

	for (int x = playerX - RENDER_DISTANCE; x < playerX + RENDER_DISTANCE; x++) {
		for (int z = playerZ - RENDER_DISTANCE; z < playerZ + RENDER_DISTANCE; z++) {
			chunkRenderer.renderTransparentChunk(world->getChunk(x, z), x, z);
		}
	}
	chunkRenderer.endChunkRendering();
}

WorldRenderer::~WorldRenderer() {
}


