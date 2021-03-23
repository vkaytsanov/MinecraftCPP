//
// Created by Viktor on 23.3.2021 г..
//

#include "include/particle_emitter.h"
#include "../data/include/asset_manager.h"

/** Draws particles in a single draw call at @param emittingPosition, using 2 Vertex Buffers.
 * One is for the constant vertices and uvs that are shared between all the particles,
 * and one vertex buffer that has the position and size of each instanced particle */
ParticleEmitter::ParticleEmitter(CubeType type) : cubeType(type) {
	vao.bind();
	vbo.bind();

	vbo.vertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ParticleVertex),
	                        (void*) (offsetof(ParticleVertex, vertices)));
	vbo.vertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(ParticleVertex),
	                        (void*) (offsetof(ParticleVertex, uvs)));

	positionsVbo.bind();
	positionsVbo.vertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(ParticleInstancedVertex),
	                                 (void*) (offsetof(ParticleInstancedVertex, position)));
	positionsVbo.vertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(ParticleInstancedVertex),
	                                 (void*) (offsetof(ParticleInstancedVertex, size)));


	glVertexAttribDivisor(0, 0); // particles vertices : always reuse the same 4 vertices
	glVertexAttribDivisor(1, 0); // uvs : always reuse
	glVertexAttribDivisor(2, 1); // positions : one per quad
	glVertexAttribDivisor(3, 1); // sizes : one per quad

	const float* uvs = AssetManager::getInstance().getCubeUVs(cubeType);
	int verticesCounter = 0;
	int uvsCounter = 4 * 2 * CubeFaceType::Bottom;

	std::array<ParticleVertex, 4> vertices;
	for (int i = 0; i < 4; i++) {
		ParticleVertex vertex;
		vertex.vertices = Vector3f(particleVertices[verticesCounter + i],
		                           particleVertices[verticesCounter + i + 1],
		                           particleVertices[verticesCounter + i + 2]);
		vertex.uvs = Vector2f(uvs[uvsCounter + i + 0],
		                      uvs[uvsCounter + i + 1]);
		vertices[i] = vertex;
		verticesCounter += 2;
		uvsCounter += 1;
	}

	vbo.bind();
	vbo.bufferData(sizeof(vertices), &vertices[0], GL_STATIC_DRAW);
	vbo.unbind();

}

void ParticleEmitter::update(float dt) {
	lifetime -= dt;
	int counter = 0;
	std::vector<float> particlesInstances(particles.size() * 6);
	// update the particles positions' buffer
	for (auto& particle : particles) {
		particle.update(dt);
		particlesInstances[counter + 0] = emittingPosition.x + particle.position.x;
		particlesInstances[counter + 1] = emittingPosition.y + particle.position.y;
		particlesInstances[counter + 2] = emittingPosition.z + particle.position.z;
		particlesInstances[counter + 3] = particle.size.x;
		particlesInstances[counter + 4] = particle.size.y;
		counter += 5;
	}

	positionsVbo.bind();
	positionsVbo.bufferData(particlesInstances.size() * sizeof(ParticleInstancedVertex), nullptr, GL_DYNAMIC_DRAW);
	positionsVbo.bufferSubData(0, particlesInstances.size() * sizeof(ParticleInstancedVertex), &particlesInstances[0]);

}

void ParticleEmitter::setToExplosionEmitter() {
	// Creating a circle starting from pi counter clockwise
	particles.reserve(8);
	lifetime = 0.6f;
	particles.emplace_back(Particle(Vector3f(2.0f, 0, 0)));
	particles.emplace_back(Particle(Vector3f(1.5f, 1.5f, 0)));
	particles.emplace_back(Particle(Vector3f(0, 2.0f, 0)));
	particles.emplace_back(Particle(Vector3f(-1.5f, 1.5f, 0)));
	particles.emplace_back(Particle(Vector3f(-2.0f, 0.0f, 0)));
	particles.emplace_back(Particle(Vector3f(-1.5f, -1.5f, 0)));
	particles.emplace_back(Particle(Vector3f(0.0f, -2.0f, 0)));
	particles.emplace_back(Particle(Vector3f(1.5f, -1.5f, 0)));

	for (auto& particle : particles) {
		particle.size = Vector2f(static_cast<float>(rand()) / RAND_MAX / 3,
		                         static_cast<float>(rand()) / RAND_MAX / 3);
	}

}
