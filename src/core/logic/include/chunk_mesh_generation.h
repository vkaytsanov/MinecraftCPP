//
// Created by Viktor on 24.2.2021 г..
//

#ifndef CHUNK_MESH_GENERATION_H
#define CHUNK_MESH_GENERATION_H


#include <array>
#include <vector>
#include "../../lib/utils/openGL/include/vertex.h"
#include "../../data/include/world.h"
#include "../../data/include/cube.h"
#include "../../data/include/cube_data_base.h"


typedef std::array<std::array<std::array<Cube, CHUNK_SIZE_X>, CHUNK_SIZE_Y>, CHUNK_SIZE_Z> ChunkContents;
typedef std::array<std::array<std::array<Cube, CHUNK_SIZE_X>, CHUNK_SIZE_Y>, CHUNK_SIZE_Z>* ChunkContentsPtr;

static float planes[6 * 4 * 3] = {
		// Front
		0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f,
		// Back
		1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		// Top
		0.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		// Bottom
		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		// Left
		0.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		// Right
		1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
};

class ChunkMeshGeneration {
private:
	World* world;
	std::array<std::vector<Vertex>, 2> vertices;
	void addFace(CubeType type, CubeFaceType face, Vector3f& position, bool isTransparent);
	static bool isVisibleEdge(ChunkContentsPtr chunkData, ChunkContentsPtr lowerNeighbourData,
	                          ChunkContentsPtr upperNeighbourData, int x, int y, int z, Axis axis);
	static bool isVisibleSide(ChunkContentsPtr chunkData, int x, int y, int z, int side, Axis axis);
public:
	ChunkMeshGeneration(World* world);
	void generate(int16_t chunkX, int16_t chunkZ);
};


#endif //CHUNK_MESH_GENERATION_H
