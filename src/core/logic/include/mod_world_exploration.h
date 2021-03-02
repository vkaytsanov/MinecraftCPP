//
// Created by Viktor on 19.2.2021 г..
//

#ifndef MOD_WORLD_EXPLORATION_H
#define MOD_WORLD_EXPLORATION_H


#include "mod_logic.h"
#include "world_generation.h"
#include "chunk_mesh_generation.h"

#define EXPLORATION_DISTANCE 8
#define BUILD_DISTANCE 7

class Minecraft;

class ModWorldExploration : public ModLogic {
private:
	Minecraft* m_pGame;
	WorldGeneration m_worldGeneration;
	ChunkMeshGeneration m_chunkMeshGeneration;
	int m_lastPlayerX;
	int m_lastPlayerZ;
	void constructNewCoordinates(int x, int z);
public:
	explicit ModWorldExploration(Minecraft* game);
	void init() override;
	void update() override;
	void post(Event* e) override;
	void reinit() override;
};


#endif //MOD_WORLD_EXPLORATION_H
