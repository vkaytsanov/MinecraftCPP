//
// Created by Viktor on 17.2.2021 г..
//

#include "include/world_renderer.h"

WorldRenderer::WorldRenderer(DataSystem* dataSystem, Camera* camera) : world(dataSystem->world), camera(camera){
	chunkRenderer = new ChunkRenderer(dataSystem);
}
void WorldRenderer::render() {
	chunkRenderer->beginChunkRendering(camera);

	chunkRenderer->renderChunk(world->getChunk(0));

	chunkRenderer->endChunkRendering();
}

WorldRenderer::~WorldRenderer() {
	delete chunkRenderer;
}


