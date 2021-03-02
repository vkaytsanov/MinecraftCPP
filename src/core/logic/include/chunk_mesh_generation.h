//
// Created by Viktor on 24.2.2021 г..
//

#ifndef CHUNK_MESH_GENERATION_H
#define CHUNK_MESH_GENERATION_H


#include <array>
#include <vector>
#include "../../lib/utils/openGL/include/vertex.h"
#include "../../data/include/world.h"
#include "../../data/terrain/include/cube.h"
#include "../../data/terrain/include/cube_data_base.h"


typedef std::array<std::array<std::array<Cube, CHUNK_SIZE_X>, CHUNK_SIZE_Y>, CHUNK_SIZE_Z> ChunkContents;
typedef std::array<std::array<std::array<Cube, CHUNK_SIZE_X>, CHUNK_SIZE_Y>, CHUNK_SIZE_Z>* ChunkContentsPtr;

static const int8_t planes[6 * 4 * 3] = {
		// Front
		0, 0, 1,
		1, 0, 1,
		1, 1, 1,
		0, 1, 1,
		// Back
		1, 0, 0,
		0, 0, 0,
		0, 1, 0,
		1, 1, 0,
		// Top
		0, 1, 1,
		1, 1, 1,
		1, 1, 0,
		0, 1, 0,
		// Bottom
		0, 0, 0,
		1, 0, 0,
		1, 0, 1,
		0, 0, 1,
		// Left
		0, 1, 1,
		0, 1, 0,
		0, 0, 0,
		0, 0, 1,
		// Right
		1, 0, 0,
		1, 1, 0,
		1, 1, 1,
		1, 0, 1,
};

class ChunkMeshGeneration {
private:
	World* m_world;
	std::array<std::vector<Vertex>, 3> m_vertices;
	void addFace(CubeType type, CubeFaceType face, Vector3f& position, bool isTransparent);
	void addModel(CubeType type, Vector3f& position);
	static bool isVisibleEdge(ChunkContentsPtr chunkData, ChunkContentsPtr lowerNeighbourData,
	                          ChunkContentsPtr upperNeighbourData, int x, int y, int z, Axis axis);
	static bool isVisibleSide(ChunkContentsPtr chunkData, int x, int y, int z, int side, Axis axis);
public:
	ChunkMeshGeneration(World* world);
	void generate(int16_t chunkX, int16_t chunkZ);
};


#endif //CHUNK_MESH_GENERATION_H
