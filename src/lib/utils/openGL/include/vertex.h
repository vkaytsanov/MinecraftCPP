//
// Created by Viktor on 17.2.2021 г..
//

#ifndef VERTEX_H
#define VERTEX_H

#include "../../geometry/include/vector3.h"
#include "../../geometry/include/vector2.h"

class Vertex {
public:
	Vector3f position;
	Vector3f normals;
	Vector2f uvs;
};


#endif //VERTEX_H
