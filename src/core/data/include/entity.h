//
// Created by Viktor on 25.2.2021 г..
//

#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include "../../../lib/utils/geometry/include/vector3.h"
#include "../../../lib/utils/geometry/include/vector2.h"
#include "../../../lib/utils/include/texture_region.h"

struct EntityVertex{
	Vector3f position;
	Vector2f uvs;
};

class Entity {
private:
public:
	Entity(TextureRegion& textureRegion);
	std::vector<EntityVertex> vertices;
};


#endif //ENTITY_H
