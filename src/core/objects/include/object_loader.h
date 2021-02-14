//
// Created by Viktor on 9.1.2021 г..
//

#ifndef OBJECT_LOADER_H
#define OBJECT_LOADER_H

#include <vector>
#include "../../lib/utils/geometry/include/vector3.h"
#include "../../lib/utils/geometry/include/vector2.h"
#include "../../lib/include/lib.h"


void loadOBJ(
        const char * path,
        std::vector<Vector3f> & out_vertices,
        std::vector<Vector2f> & out_uvs,
        std::vector<Vector3f> & out_normals
);


#endif //OBJECT_LOADER_H
