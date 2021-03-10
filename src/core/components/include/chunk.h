//
// Created by Viktor on 6.3.2021 г..
//

#ifndef CHUNK_H
#define CHUNK_H


#include <array>
#include "../../data/terrain/include/cube.h"
#include "../../data/terrain/include/biome.h"
#include "../../../lib/entityx/entityx.h"
#include "chunk_mesh.h"


typedef std::array<std::array<std::array<Cube, CHUNK_SIZE_X>, CHUNK_SIZE_Y>, CHUNK_SIZE_Z> ChunkContents;
typedef std::array<std::array<std::array<Cube, CHUNK_SIZE_X>, CHUNK_SIZE_Y>, CHUNK_SIZE_Z>* ChunkContentsPtr;
typedef std::array<std::array<int, CHUNK_SIZE_X>, CHUNK_SIZE_Z> HeightMap;
typedef std::array<std::array<BiomeType, CHUNK_SIZE_X>, CHUNK_SIZE_Z> BiomeMap;

enum ChunkState {
	Generated,
	Empty
};

class Chunk : public entityx::Component<Chunk>{
private:
	ChunkContentsPtr m_chunkContents;
	HeightMap m_heightMap;
	BiomeMap m_biomeMap;
public:
	ChunkState m_chunkState;
	Chunk();
	~Chunk();
	void setCube(CubeType type, int x, int y, int z);
	void setHeight(int height, int x, int z);
	ChunkContentsPtr getChunkContents() const;
	HeightMap* getHeightMap();
	BiomeMap* getBiomeMap();
};


#endif //CHUNK_H
