//
// Created by Viktor on 17.2.2021 г..
//

#ifndef CUBE_DATA_BASE_H
#define CUBE_DATA_BASE_H


#include <unordered_map>
#include "../../../lib/utils/include/texture_region.h"
#include "cube.h"

namespace CubeDatabase {

	const int UVS_COUNT = 6 * 4 * 2;

	static uint8_t faceLightningLevel[6]{
		6, 7, 10, 3, 6, 7
	};
	// u * 3.0f for third part
	// u * 2.0f, u2 * 0.67  for second part
	// u2 * 0.50f for first part
	static float uvs3side[UVS_COUNT]{
			// front
			1.0f, 1.0f,
			0.50f, 1.0f,
			0.50f, 1.0f,
			1.0f, 1.0f,
			// back
			0.50f, 1.0f,
			1.0f, 1.0f,
			1.0f, 1.0f,
			0.50f, 1.0f,
			// top
			2.0f, 1.0f,
			0.67f, 1.0f,
			0.67f, 1.0f,
			2.0f, 1.0f,
			//bottom
			3.0f, 1.0f,
			1.0f, 1.0f,
			1.0f, 1.0f,
			3.0f, 1.0f,
			//left
			1.0f, 1.0f,
			0.50f, 1.0f,
			0.50f, 1.0f,
			1.0f, 1.0f,
			//right
			1.0f, 1.0f,
			1.0f, 1.0f,
			0.50f, 1.0f,
			0.50f, 1.0f,
	};


	struct TextureCubeData {
		float* uvs = nullptr;

		TextureCubeData(TextureRegion region, int sides = 1);
		TextureCubeData() = default;
	};

//	struct TextureEntityData{
//		float* uvs = nullptr;
//		float* vertices = nullptr;
//		TextureEntityData(TextureRegion region);
//		TextureEntityData() = default;
//	};


	void init(Texture* texture);

	float* getUVs(CubeType type);

	void freeMemory();

}


#endif //CUBE_DATA_BASE_H
