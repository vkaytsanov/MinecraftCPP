//
// Created by Viktor on 17.2.2021 г..
//

#ifndef VERTEX_H
#define VERTEX_H

#include <SDL.h>
#include "../../geometry/include/vector3.h"
#include "../../geometry/include/vector2.h"

class Vertex {
public:
	Vector3f position;
	Vector2f uvs;
	uint8_t lightningLevel;
};


#endif //VERTEX_H
