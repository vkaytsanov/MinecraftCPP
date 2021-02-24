//
// Created by Viktor on 24.2.2021 г..
//

#include "include/chunk_mesh_generation.h"

using namespace CubeDatabase;

ChunkMeshGeneration::ChunkMeshGeneration(World* world) : world(world){}

void ChunkMeshGeneration::generate(int16_t chunkX, int16_t chunkZ) {
	Chunk* chunk      = world->getChunk(chunkX, chunkZ);
	Chunk* frontChunk = world->getChunk(chunkX, chunkZ + 1);
	Chunk* backChunk  = world->getChunk(chunkX, chunkZ - 1);
	Chunk* rightChunk = world->getChunk(chunkX + 1, chunkZ);
	Chunk* leftChunk  = world->getChunk(chunkX - 1, chunkZ);

	if (!frontChunk || !backChunk || !leftChunk || !rightChunk) {
		return;
	}

	ChunkContentsPtr front = frontChunk->getChunkContents();
	ChunkContentsPtr back = backChunk->getChunkContents();
	ChunkContentsPtr left = leftChunk->getChunkContents();
	ChunkContentsPtr right = rightChunk->getChunkContents();

	Vector3f cubePosition;

	ChunkContentsPtr chunkData = chunk->getChunkContents();
	HeightMap* heightMap = &chunk->heightMap;

	for (int x = 0; x < CHUNK_SIZE_X; x++) {
		for (int z = 0; z < CHUNK_SIZE_Z; z++) {
			for (int y = 0; y < heightMap->at(x).at(z); y++) {
				Cube* cube = &chunkData->at(x).at(y).at(z);
				if (cube->type != CubeType::Air) {
					cubePosition.set(x, y, z);
					bool isTransparent = cube->isTransparent();

					if (isVisibleSide(chunkData, x, y, z, 1, Z)) {
						addFace(cube->type, Front, cubePosition, isTransparent);
					}
					else if (isVisibleSide(chunkData, x, y, z, -1, Z)) {
						addFace(cube->type, Back, cubePosition, isTransparent);
					}
					else if (isVisibleEdge(chunkData, back, front, x, y, z, Z)) {
						addFace(cube->type, Front, cubePosition, isTransparent);
						addFace(cube->type, Back, cubePosition, isTransparent);
					}

					if (isVisibleSide(chunkData, x, y, z, 1, X)) {
						addFace(cube->type, Right, cubePosition, isTransparent);
					}
					else if (isVisibleSide(chunkData, x, y, z, -1, X)) {
						addFace(cube->type, Left, cubePosition, isTransparent);
					}
					else if (isVisibleEdge(chunkData, left, right, x, y, z, X)) {
						addFace(cube->type, Left, cubePosition, isTransparent);
						addFace(cube->type, Right, cubePosition, isTransparent);
					}

					if (isVisibleSide(chunkData, x, y, z, -1, Y) ||
					    (y == 0 && chunkData->at(x).at(y + 1).at(z).isTransparent())) {
						addFace(cube->type, Bottom, cubePosition, isTransparent);
					} else if (isVisibleSide(chunkData, x, y, z, 1, Y) || y == CHUNK_SIZE_Y - 1) {
						addFace(cube->type, Top, cubePosition, isTransparent);
					}
				}
			}
		}
	}

	chunk->getChunkMesh()->setMesh(vertices);
	for(int i = 0; i < vertices.size(); i++){
		vertices.at(i).clear();
	}

	chunk->chunkMeshState = Built;

}


void ChunkMeshGeneration::addFace(CubeType type, CubeFaceType face, Vector3f& position, bool isTransparent) {
	Vertex currVertex;
	float* uvs = CubeDatabase::getUVs(type);

	int normalsOffset = 4 * 3 * face;
	int uvsOffset = 4 * 2 * face;
	for (int i = 0; i < 4; i++) {
		currVertex.position = position + Vector3f(planes[normalsOffset + i],
		                                          planes[normalsOffset + i + 1],
		                                          planes[normalsOffset + i + 2]);
		currVertex.normals = Vector3f(normals[normalsOffset + i],
		                              normals[normalsOffset + i + 1],
		                              normals[normalsOffset + i + 2]);
		currVertex.uvs = Vector2f(uvs[uvsOffset + i],
		                          uvs[uvsOffset + i + 1]);
		normalsOffset += 2;
		uvsOffset += 1;
		vertices.at(static_cast<int>(isTransparent)).emplace_back(currVertex);

	}

}

bool ChunkMeshGeneration::isVisibleEdge(ChunkContentsPtr chunkData, ChunkContentsPtr lowerNeighbourData,
                              ChunkContentsPtr upperNeighbourData, int x, int y, int z, Axis axis) {
	int x2, x3;
	int z2, z3;
	ChunkContentsPtr neighbourData;
	if (axis == Axis::X) {
		if (x == 0) {
			x2 = CHUNK_SIZE_Z - 1;
			x3 = 1;
			neighbourData = lowerNeighbourData;
		} else if (x == CHUNK_SIZE_Z - 1) {
			x2 = 0;
			x3 = CHUNK_SIZE_Z - 2;
			neighbourData = upperNeighbourData;
		} else {
			return false;
		}
		z2 = z;
		z3 = z;
	} else if (axis == Axis::Z) {
		if (z == 0) {
			z2 = CHUNK_SIZE_Z - 1;
			z3 = 1;
			neighbourData = lowerNeighbourData;
		} else if (z == CHUNK_SIZE_Z - 1) {
			z2 = 0;
			z3 = CHUNK_SIZE_Z - 2;
			neighbourData = upperNeighbourData;
		} else {
			return false;
		}
		x2 = x;
		x3 = x;
	}

	if (chunkData->at(x).at(y).at(z).isTransparent()) {
		if (neighbourData->at(x2).at(y).at(z2).isTransparent() &&
		    neighbourData->at(x2).at(y).at(z2).type != chunkData->at(x).at(y).at(z).type) {
			return true;
		}
		if (chunkData->at(x3).at(y).at(z3).isTransparent() &&
		    chunkData->at(x3).at(y).at(z3).type != chunkData->at(x).at(y).at(z).type) {
			return true;
		}
		return false;
	}
	return neighbourData->at(x2).at(y).at(z2).isTransparent() || chunkData->at(x3).at(y).at(z3).isTransparent();


}

bool ChunkMeshGeneration::isVisibleSide(ChunkContentsPtr chunkData, int x, int y, int z, int side, Axis axis) {
	int x2;
	int y2;
	int z2;
	if (axis == X) {
		if (x == 0 || x == CHUNK_SIZE_X - 1) return false;
		x2 = x + side;
		y2 = y;
		z2 = z;
	} else if (axis == Y) {
		if (y == 0 || y == CHUNK_SIZE_Y - 1) return false;
		x2 = x;
		y2 = y + side;
		z2 = z;
	} else if (axis == Z) {
		if (z == 0 || z == CHUNK_SIZE_Z - 1) return false;
		x2 = x;
		y2 = y;
		z2 = z + side;
	}
	if (chunkData->at(x).at(y).at(z).isTransparent()) {
		return chunkData->at(x2).at(y2).at(z2).isTransparent() &&
		       chunkData->at(x2).at(y2).at(z2).type != chunkData->at(x).at(y).at(z).type;
	}
	return chunkData->at(x2).at(y2).at(z2).isTransparent();
}





