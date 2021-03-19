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

struct InstancedVertex{
	Vector2f position;
	Vector3f color;

	InstancedVertex(Vector2f position, Vector3f color) : position(position), color(color){}
};

struct Particle : public entityx::Component<Particle>{
	Vector3f position;
	Vector3f velocity;
	float lifetime;
	CubeType cubeType;

	VertexBuffer vbo;
	VertexBuffer instancedVbo;
	VertexArray vao;

	Particle();
	void updateLife(float dt);
	void setData();
	bool isAlive();
};


#endif //PARTICLE_H
