//
// Created by Viktor on 19.2.2021 г..
//

#include "include/mod_world_exploration.h"
#include "events/include/chunk_ticket_event.h"
#include "../include/minecraft.h"
#include "../../lib/include/lib.h"

ModWorldExploration::ModWorldExploration(Minecraft* game) : m_pGame(game),
                                                            m_chunkMeshGeneration(&game->m_pDataSystem->world) {

}

void ModWorldExploration::init() {
	int x = (int) m_pGame->m_pGraphicsSystem->getViewport()->getCamera()->m_position.x / CHUNK_SIZE_X;
	int z = (int) m_pGame->m_pGraphicsSystem->getViewport()->getCamera()->m_position.z / CHUNK_SIZE_Z;

	constructNewCoordinates(x, z);

	m_lastPlayerX = x;
	m_lastPlayerZ = z;

}

void ModWorldExploration::update() {
	// 2 cubes difference so it can start constructing before
	int x = (int) m_pGame->m_pGraphicsSystem->getViewport()->getCamera()->m_position.x / (CHUNK_SIZE_X);
	int z = (int) m_pGame->m_pGraphicsSystem->getViewport()->getCamera()->m_position.z / (CHUNK_SIZE_Z);

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
			m_pGame->m_pDataSystem->world.addChunk(i, j);
			if (m_pGame->m_pDataSystem->world.getChunk(i, j)->m_chunkState == Empty) {
				m_worldGeneration.generateChunkContents(m_pGame->m_pDataSystem->world.getChunk(i, j), i, j);
				counter++;
			}

		}
	}
	Lib::app->log("WorldGeneration", ("Added " + std::to_string(counter) + " chunks").c_str());
	counter = 0;
	for (int i = x - BUILD_DISTANCE; i < x + BUILD_DISTANCE; i++) {
		for (int j = z - BUILD_DISTANCE; j < z + BUILD_DISTANCE; j++) {
			if (m_pGame->m_pDataSystem->world.getChunk(i, j)->m_chunkMeshState == UnBuilt) {
				m_chunkMeshGeneration.generate(i, j);
				counter++;
			}
		}
	}
	Lib::app->log("WorldGeneration", ("Constructed " + std::to_string(counter) + " meshes").c_str());
}
