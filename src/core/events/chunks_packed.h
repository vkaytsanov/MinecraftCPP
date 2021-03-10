//
// Created by Viktor on 7.3.2021 г..
//

#ifndef CHUNKMESHINGEVENT_H
#define CHUNKMESHINGEVENT_H

#include "../../lib/entityx/Entity.h"

struct ChunksPacked {
	entityx::Entity* front;
	entityx::Entity* back;
	entityx::Entity* center;
	entityx::Entity* left;
	entityx::Entity* right;

	ChunksPacked(entityx::Entity* front, entityx::Entity* back, entityx::Entity* center, entityx::Entity* left,
	             entityx::Entity* right) : front(front), back(back), center(center), left(left), right(right) {}

	bool canMesh() const{
		return front && back && left && right;
	}
};

#endif //CHUNKMESHINGEVENT_H
