//
// Created by Viktor on 19.2.2021 г..
//

#include "include/mod_world_exploration.h"
#include "events/include/chunk_ticket_event.h"
#include "../include/minecraft.h"
#include "../../lib/include/lib.h"

ModWorldExploration::ModWorldExploration(Minecraft* game) : p_game(game),
                                                            m_chunkMeshGeneration(&game->dataSystem->world) {

}

void ModWorldExploration::init() {
	int x = (int) p_game->graphicsSystem->getViewport()->getCamera()->position->x / CHUNK_SIZE_X;
	int z = (int) p_game->graphicsSystem->getViewport()->getCamera()->position->z / CHUNK_SIZE_Z;

	constructNewCoordinates(x, z);

	m_lastPlayerX = x;
	m_lastPlayerZ = z;

}

void ModWorldExploration::update() {
	// 2 cubes difference so it can start constructing before
	int x = (int) p_game->graphicsSystem->getViewport()->getCamera()->position->x / (CHUNK_SIZE_X - 2);
	int z = (int) p_game->graphicsSystem->getViewport()->getCamera()->position->z / (CHUNK_SIZE_Z - 2);

	if (m_lastPlayerX != x || m_lastPlayerZ != z) {
		constructNewCoordinates(x, z);
		m_lastPlayerX = x;
		m_lastPlayerZ = z;
	}
}

void ModWorldExploration::post(Event* e) {

}

void ModWorldExploration::reinit() {

}

void ModWorldExploration::constructNewCoordinates(int x, int z) {
	int counter = 0;
	for (int i = x - EXPLORATION_DISTANCE; i < x + EXPLORATION_DISTANCE; i++) {
		for (int j = z - EXPLORATION_DISTANCE; j < z + EXPLORATION_DISTANCE; j++) {
			p_game->dataSystem->world.addChunk(i, j);
			if (p_game->dataSystem->world.getChunk(i, j)->chunkState == Empty) {
				counter++;
				m_worldGeneration.generateChunkContents(p_game->dataSystem->world.getChunk(i, j), i, j);
			}

		}
	}
	Lib::app->log("WorldGeneration", ("Added " + std::to_string(counter) + " chunks").c_str());
	counter = 0;
	for (int i = x - BUILD_DISTANCE; i < x + BUILD_DISTANCE; i++) {
		for (int j = z - BUILD_DISTANCE; j < z + BUILD_DISTANCE; j++) {
			if (p_game->dataSystem->world.getChunk(i, j)->chunkMeshState == UnBuilt) {
				m_chunkMeshGeneration.generate(i, j);
				counter++;
			}
		}
	}
	Lib::app->log("WorldGeneration", ("Constructed " + std::to_string(counter) + " meshes").c_str());
}
