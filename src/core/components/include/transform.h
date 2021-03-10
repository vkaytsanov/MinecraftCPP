//
// Created by Viktor on 4.3.2021 г..
//

#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "../../../lib/utils/geometry/include/vector3.h"

struct Transform {
	Vector3f position;
	Vector3f rotation;
	Vector3f scale = Vector3f(1, 1, 1);
	Transform(){}
	Transform(const Vector3f& position) : position(position){}
};


#endif //TRANSFORM_H
