//
// Created by Viktor on 17.2.2021 г..
//

#ifndef CHUNK_RENDERER_H
#define CHUNK_RENDERER_H

#include "../../../lib/utils/include/shaders.h"
#include "graphics_system.h"
#include "../../data/include/chunk.h"
#include "../../data/include/data_system.h"


class ChunkRenderer {
private:
	Texture* texture;
	Shaders* defaultShader;
public:
	ChunkRenderer(DataSystem* dataSystem);
	~ChunkRenderer();
	void beginChunkRendering(Camera* camera);
	void renderChunk(Chunk* chunk);
	void endChunkRendering();
};


#endif //CHUNK_RENDERER_H
