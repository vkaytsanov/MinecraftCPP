//
// Created by Viktor on 18.3.2021 г..
//

#ifndef CUBE_DESTROYED_EVENT_H
#define CUBE_DESTROYED_EVENT_H

#include "../../lib/entityx/Entity.h"
#include "../../lib/utils/geometry/include/vector3.h"
#include "../data/terrain/include/cube.h"

struct CubeDestroyedEvent : public entityx::Event<CubeDestroyedEvent>{
	Vector3f cubePos;
	CubeType cubeType;
	CubeDestroyedEvent(Vector3f cubePos, CubeType cubeType) : cubePos(cubePos), cubeType(cubeType){}
};


#endif //CUBE_DESTROYED_EVENT_H
