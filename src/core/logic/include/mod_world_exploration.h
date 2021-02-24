//
// Created by Viktor on 19.2.2021 г..
//

#ifndef MOD_WORLD_EXPLORATION_H
#define MOD_WORLD_EXPLORATION_H


#include "mod_logic.h"
#include "world_generation.h"
#include "chunk_mesh_generation.h"

#define EXPLORATION_DISTANCE 5
#define BUILD_DISTANCE 4

class Minecraft;

class ModWorldExploration : public ModLogic{
private:
	Minecraft* game;
	WorldGeneration worldGeneration;
	ChunkMeshGeneration chunkMeshGeneration;
	int lastPlayerX;
	int lastPlayerZ;
	void constructNewCoordinates(int x, int z);
public:
	explicit ModWorldExploration(Minecraft* game);
	void init() override;
	void update() override;
	void post(Event* e) override;
	void reinit() override;
};


#endif //MOD_WORLD_EXPLORATION_H
