//
// Created by Viktor on 23.3.2021 г..
//

#ifndef PARTICLE_EMITTER_H
#define PARTICLE_EMITTER_H


#include "../../../lib/entityx/entityx.h"
#include "../../../lib/utils/geometry/include/vector3.h"
#include "../../../lib/utils/geometry/include/vector2.h"
#include "../../../lib/utils/openGL/include/vertex_array.h"
#include "../../../lib/utils/openGL/include/vertex_buffer.h"
#include "../../data/terrain/include/cube.h"
#include "particle.h"

struct ParticleEmitter : public entityx::Component<ParticleEmitter>{
	std::vector<Particle> particles;
	Vector3f emittingPosition;
	bool hasGravity = false;
	CubeType cubeType;
	float lifetime = 1.0f;
	VertexArray vao;
	VertexBuffer vbo;
	VertexBuffer positionsVbo;

	ParticleEmitter(CubeType type);
	void update(float dt);
	void setToExplosionEmitter();

};


#endif //PARTICLE_EMITTER_H
