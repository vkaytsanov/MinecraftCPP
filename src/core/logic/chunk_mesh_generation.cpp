//
// Created by Viktor on 24.2.2021 г..
//

#include "include/chunk_mesh_generation.h"
#include "../../lib/include/lib.h"

using namespace CubeDatabase;

ChunkMeshGeneration::ChunkMeshGeneration(World* world) : m_world(world) {}

void ChunkMeshGeneration::generate(int16_t chunkX, int16_t chunkZ) {
	Chunk* chunk = m_world->getChunk(chunkX, chunkZ);
	Chunk* frontChunk = m_world->getChunk(chunkX, chunkZ + 1);
	Chunk* backChunk = m_world->getChunk(chunkX, chunkZ - 1);
	Chunk* rightChunk = m_world->getChunk(chunkX + 1, chunkZ);
	Chunk* leftChunk = m_world->getChunk(chunkX - 1, chunkZ);

	if (!frontChunk || !backChunk || !leftChunk || !rightChunk) {
		Lib::app->log("ChunkMesh", "Skipping");
		return;
	}

	ChunkContentsPtr front = frontChunk->getChunkContents();
	ChunkContentsPtr back = backChunk->getChunkContents();
	ChunkContentsPtr left = leftChunk->getChunkContents();
	ChunkContentsPtr right = rightChunk->getChunkContents();

	Vector3f cubePosition;

	ChunkContentsPtr chunkData = chunk->getChunkContents();
	HeightMap* heightMap = &chunk->m_heightMap;

	for (int x = 0; x < CHUNK_SIZE_X; x++) {
		for (int z = 0; z < CHUNK_SIZE_Z; z++) {
			for (int y = std::max(heightMap->at(x).at(z) - 64, 0); y < heightMap->at(x).at(z); y++) {
				Cube* cube = &chunkData->at(x).at(y).at(z);
				if (cube->m_type != CubeType::Air) {
					cubePosition.set(x, y, z);

					if (cube->isModel()) {
						addModel(cube->m_type, cubePosition);
						continue;
					}

					bool isTransparent = cube->isTransparent();

					if (isVisibleEdge(chunkData, back, front, x, y, z, Z)) {
						addFace(cube->m_type, Front, cubePosition, isTransparent);
						addFace(cube->m_type, Back, cubePosition, isTransparent);
					}
					else {
						if (isVisibleSide(chunkData, x, y, z, 1, Z)) {
							addFace(cube->m_type, Front, cubePosition, isTransparent);
						}
						if (isVisibleSide(chunkData, x, y, z, -1, Z)) {
							addFace(cube->m_type, Back, cubePosition, isTransparent);
						}
					}

					if (isVisibleEdge(chunkData, left, right, x, y, z, X)) {
						addFace(cube->m_type, Right, cubePosition, isTransparent);
						addFace(cube->m_type, Left, cubePosition, isTransparent);
					}
					else {
						if (isVisibleSide(chunkData, x, y, z, 1, X)) {

							addFace(cube->m_type, Right, cubePosition, isTransparent);
						}
						if (isVisibleSide(chunkData, x, y, z, -1, X)) {
							addFace(cube->m_type, Left, cubePosition, isTransparent);
						}
					}

					if (isVisibleSide(chunkData, x, y, z, -1, Y) ||
					    (y == 0 && chunkData->at(x).at(y + 1).at(z).isTransparent())) {
						addFace(cube->m_type, Bottom, cubePosition, isTransparent);
					}
					if (isVisibleSide(chunkData, x, y, z, 1, Y) || y == CHUNK_SIZE_Y - 1) {
						// little offset for more realistic water and lava levels
						if (cube->isLiquid()) cubePosition.y -= 0.2f;
						addFace(cube->m_type, Top, cubePosition, isTransparent);
					}
				}
//				else if(cube->isGround()){
//					break;
//				}
			}
		}
	}

	chunk->getChunkMesh()->setMesh(m_vertices);
	for (int i = 0; i < m_vertices.size(); i++) {
		m_vertices.at(i).clear();
	}

	chunk->m_chunkMeshState = Built;

}


void ChunkMeshGeneration::addFace(CubeType type, CubeFaceType face, Vector3f& position, bool isTransparent) {
	Vertex currVertex;
	float* uvs = CubeDatabase::getUVs(type);

	int posOffset = 4 * 3 * face;
	int uvsOffset = 4 * 2 * face;

	for (int i = 0; i < 4; i++) {
		currVertex.position = position + Vector3f(planes[posOffset + i],
		                                          planes[posOffset + i + 1],
		                                          planes[posOffset + i + 2]);
		currVertex.uvs = Vector2f(uvs[uvsOffset + i],
		                          uvs[uvsOffset + i + 1]);
		currVertex.lightningLevel = faceLightningLevel[face];


		posOffset += 2;
		uvsOffset += 1;
		m_vertices.at(static_cast<int>(isTransparent)).emplace_back(currVertex);

	}
}

void ChunkMeshGeneration::addModel(CubeType type, Vector3f& position) {
	Vertex currVertex;
	float* uvs = CubeDatabase::getUVs(type);
	int posOffset = 0;
	int uvsOffset = 0;
	for (int i = 0; i < 8; i++) {
		currVertex.position = position + Vector3f(modelVertices[posOffset + i],
		                                          modelVertices[posOffset + i + 1],
		                                          modelVertices[posOffset + i + 2]);
		currVertex.uvs = Vector2f(uvs[uvsOffset + i],
		                          uvs[uvsOffset + i + 1]);
		currVertex.lightningLevel = 10;


		posOffset += 2;
		uvsOffset += 1;
		m_vertices.at(2).emplace_back(currVertex);
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
		}
		else if (x == CHUNK_SIZE_Z - 1) {
			x2 = 0;
			x3 = CHUNK_SIZE_Z - 2;
			neighbourData = upperNeighbourData;
		}
		else {
			return false;
		}
		z2 = z;
		z3 = z;
	}
	else if (axis == Axis::Z) {
		if (z == 0) {
			z2 = CHUNK_SIZE_Z - 1;
			z3 = 1;
			neighbourData = lowerNeighbourData;
		}
		else if (z == CHUNK_SIZE_Z - 1) {
			z2 = 0;
			z3 = CHUNK_SIZE_Z - 2;
			neighbourData = upperNeighbourData;
		}
		else {
			return false;
		}
		x2 = x;
		x3 = x;
	}

	if (chunkData->at(x).at(y).at(z).isTransparent()) {
		if (neighbourData->at(x2).at(y).at(z2).isTransparent() &&
		    neighbourData->at(x2).at(y).at(z2).m_type != chunkData->at(x).at(y).at(z).m_type) {
			return true;
		}
		if (chunkData->at(x3).at(y).at(z3).isTransparent() &&
		    chunkData->at(x3).at(y).at(z3).m_type != chunkData->at(x).at(y).at(z).m_type) {
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
	}
	else if (axis == Y) {
		if (y == 0 || y == CHUNK_SIZE_Y - 1) return false;
		x2 = x;
		y2 = y + side;
		z2 = z;
	}
	else if (axis == Z) {
		if (z == 0 || z == CHUNK_SIZE_Z - 1) return false;
		x2 = x;
		y2 = y;
		z2 = z + side;
	}
	if (chunkData->at(x).at(y).at(z).isTransparent()) {
		return chunkData->at(x2).at(y2).at(z2).isTransparent() &&
		       chunkData->at(x2).at(y2).at(z2).m_type != chunkData->at(x).at(y).at(z).m_type;
	}
	return chunkData->at(x2).at(y2).at(z2).isTransparent();
}







