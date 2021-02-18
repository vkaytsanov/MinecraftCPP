//
// Created by Viktor on 17.2.2021 г..
//

#ifndef WORLD_RENDERER_H
#define WORLD_RENDERER_H


#include "../../data/include/world.h"
#include "chunk_renderer.h"

class WorldRenderer {
private:
	World* world;
	Camera* camera;
	ChunkRenderer* chunkRenderer;
public:
	explicit WorldRenderer(DataSystem* dataSystem, Camera* camera);
	~WorldRenderer();
	void render();
};


#endif //WORLD_RENDERER_H
