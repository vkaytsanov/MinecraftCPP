//
// Created by Viktor on 17.2.2021 г..
//

#ifndef CHUNK_RENDERER_H
#define CHUNK_RENDERER_H

#include "../../../lib/utils/include/shaders.h"
#include "../../components/include/chunk_mesh.h"
#include "../../../lib/utils/camera/include/camera.h"
#include "../../data/include/asset_manager.h"

class ChunkRenderer {
private:
	const Texture* m_texture;
	Shaders m_defaultChunkShader;
public:
	ChunkRenderer();
	void beginChunkRendering(Camera* camera, const int renderDistance);
	void renderChunk(ChunkMesh* chunkMesh, int x, int z);
	void renderTransparentChunk(ChunkMesh* chunkMesh, int x, int z);
	void renderModelChunk(ChunkMesh* chunkMesh, int x, int z);
	void endChunkRendering();
};


#endif //CHUNK_RENDERER_H
