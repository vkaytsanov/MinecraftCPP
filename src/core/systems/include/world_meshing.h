//
// Created by Viktor on 7.3.2021 г..
//

#ifndef WORLD_MESHING_H
#define WORLD_MESHING_H

#include <array>
#include <vector>
#include "../../../lib/utils/openGL/include/vertex.h"
#include "../../data/terrain/include/cube.h"
#include "../../data/terrain/include/cube_constants.h"
#include "../../components/include/chunk.h"
#include "../../../lib/entityx/System.h"
#include "../../events/chunks_packed.h"
#include "../../components/include/transform.h"
#include "../../data/include/world.h"

typedef std::array<std::array<std::array<Cube, CHUNK_SIZE_X>, CHUNK_SIZE_Y>, CHUNK_SIZE_Z> ChunkContents;
typedef std::array<std::array<std::array<Cube, CHUNK_SIZE_X>, CHUNK_SIZE_Y>, CHUNK_SIZE_Z>* ChunkContentsPtr;

static const float planes[6 * 4 * 3] = {
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

class WorldMeshing{
private:
	std::array<std::vector<Vertex>, 3> m_vertices;

	void addFace(CubeType type, CubeFaceType face, Vector3f& position, bool isTransparent);
	void addModel(CubeType type, Vector3f& position);
	static bool isVisibleEdge(ChunkContentsPtr chunkData, ChunkContentsPtr lowerNeighbourData,
	                          ChunkContentsPtr upperNeighbourData, int x, int y, int z, Axis axis);
	static bool isVisibleSide(ChunkContentsPtr chunkData, int x, int y, int z, int side, Axis axis);
	static bool isVisibleUpperEdge(ChunkContentsPtr chunkData, ChunkContentsPtr neighbourData, int x, int y, int z, Axis axis);
	static bool isVisibleUpperInsideEdge(ChunkContentsPtr chunkData, int x, int y, int z, Axis axis);
	static bool isVisibleLowerEdge(ChunkContentsPtr chunkData, ChunkContentsPtr neighbourData, int x, int y, int z, Axis axis);
	static bool isVisibleLowerInsideEdge(ChunkContentsPtr chunkData, int x, int y, int z, Axis axis);
public:
	void build(const ChunksPacked& chunksPacked);

};
#endif //WORLD_MESHING_H
