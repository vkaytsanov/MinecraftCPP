//
// Created by Viktor on 16.2.2021 г..
//

#include "include/cube_renderer.h"
#include "../include/minecraft.h"

CubeRenderer::CubeRenderer(Minecraft* game) : game(game) {

}

void CubeRenderer::render() {
	for (int i = 0; i < CHUNK_SIZE_X; i++) {
		for (int j = 0; j < CHUNK_SIZE_Y; j++) {
			for (int k = 0; k < CHUNK_SIZE_Z; k++) {
				game->batch->draw(
						game->dataSystem->cubesDb->getCube(
								game->dataSystem->world->chunk->getCube(i, j, k)
						),
						Vector3f(i, j, k)
				);
			}
		}
	}
//	game->batch->draw(
//			game->dataSystem->cubesDb->getCube(
//					game->dataSystem->world->chunk->getCube(0,0,0)
//			),
//			Vector3f(0,0,0)
//	);

}
