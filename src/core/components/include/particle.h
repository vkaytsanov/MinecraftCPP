//
// Created by Viktor on 18.3.2021 г..
//

#ifndef PARTICLE_H
#define PARTICLE_H

#include "../../../lib/entityx/entityx.h"
#include "../../../lib/utils/geometry/include/vector3.h"
#include "../../../lib/utils/geometry/include/vector2.h"
#include "../../../lib/utils/openGL/include/vertex_array.h"
#include "../../../lib/utils/openGL/include/vertex_buffer.h"
#include "../../data/terrain/include/cube.h"

const float particleVertices[] = {
		0.5f, -0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		-0.5f, -0.5f, 0.5f,
		-0.5f, 0.5f, 0.5f,
};

struct ParticleVertex{
	Vector3f vertices;
	Vector2f uvs;
};

struct ParticleInstancedVertex{
	Vector3f position;
	Vector2f size;
};

struct Particle{
	Vector3f position;
	Vector3f velocity;
	Vector2f size = Vector2f(1.0f, 1.0f);
	float lifetime = 1.0f;
	float elapsedTime = 0.0f;
	bool isAlive() const;
	void update(float dt);
	Particle(Vector3f velocity) : velocity(velocity){}
	Particle() = default;


};




#endif //PARTICLE_H
