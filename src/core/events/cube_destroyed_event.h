//
// Created by Viktor on 18.3.2021 г..
//

#ifndef CUBE_DESTROYED_EVENT_H
#define CUBE_DESTROYED_EVENT_H

#include "../../lib/entityx/Entity.h"

struct CubeDestroyedEvent : public entityx::Event<CubeDestroyedEvent>{
	Vector3i cubePos;
};


#endif //CUBE_DESTROYED_EVENT_H
