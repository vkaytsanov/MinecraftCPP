//
// Created by Viktor on 17.2.2021 г..
//

#ifndef CUBE_CONSTANTS_H
#define CUBE_CONSTANTS_H


#include <unordered_map>
#include "../../../../lib/utils/include/texture_region.h"
#include "cube.h"

namespace CubeDatabase {

	const int UVS_COUNT = 6 * 4 * 2;

	static const uint8_t modelVertices[3 * 8]{
			0, 0, 0,
			1, 0, 1,
			1, 1, 1,
			0, 1, 0,
			1, 0, 0,
			0, 0, 1,
			0, 1, 1,
			1, 1, 0,
	};

	static const uint8_t faceLightningLevel[6]{
			6, 7, 10, 3, 6, 7
	};
	// u * 3.0f for third part
	// u * 2.0f, u2 * 0.67  for second part
	// u2 * 0.50f for first part
	static const float uvs3side[UVS_COUNT]{
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
			// front
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

	static const float uvs2side[UVS_COUNT]{
			// front
			1.0f, 1.0f,
			0.84f, 1.0f,
			0.84f, 1.0f,
			1.0f, 1.0f,
			// back
			0.84f, 1.0f,
			1.0f, 1.0f,
			1.0f, 1.0f,
			0.84f, 1.0f,
			// front
			1.25f, 1.0f,
			1.0f, 1.0f,
			1.0f, 1.0f,
			1.25f, 1.0f,
			//bottom
			1.25f, 1.0f,
			1.0f, 1.0f,
			1.0f, 1.0f,
			1.25f, 1.0f,
			//left
			1.0f, 1.0f,
			0.84f, 1.0f,
			0.84f, 1.0f,
			1.0f, 1.0f,
			//right
			1.0f, 1.0f,
			1.0f, 1.0f,
			0.84f, 1.0f,
			0.84f, 1.0f,
	};
}


#endif //CUBE_CONSTANTS_H
