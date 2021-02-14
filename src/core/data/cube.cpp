//
// Created by Viktor on 14.2.2021 г..
//

#include "include/cube.h"

Cube::Cube(CubeType type) : type(type){
	Entity::generateBuffers(vertices, normals, uvs, indices, 6 * 4 * 3, 6 * 6);
}
