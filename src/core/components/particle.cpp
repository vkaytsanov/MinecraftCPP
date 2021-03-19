//
// Created by Viktor on 18.3.2021 г..
//

#include "include/particle.h"

Particle::Particle() {
	Vector2f translations[100];
	int index = 0;
	float offset = 0.1f;
	for (int y = -10; y < 10; y += 2) {
		for (int x = -10; x < 10; x += 2) {
			Vector2f translation;
			translation.x = (float) x / 10.0f + offset;
			translation.y = (float) y / 10.0f + offset;
			translations[index++] = translation;
		}
	}
	std::vector<InstancedVertex> vertices;
	vertices.emplace_back(InstancedVertex({-0.05f,  0.05f}, {1.0f, 0.0f, 0.0f}));
	vertices.emplace_back(InstancedVertex({0.05f, -0.05f}, {1.0f, 0.0f, 0.0f}));
	vertices.emplace_back(InstancedVertex({-0.05f, -0.05f}, {1.0f, 0.0f, 0.0f}));
	vertices.emplace_back(InstancedVertex({-0.05f, 0.05f}, {1.0f, 0.0f, 0.0f}));
	vertices.emplace_back(InstancedVertex({0.05f, 0.05f}, {1.0f, 1.0f, 0.0f}));
	vertices.emplace_back(InstancedVertex({0.05f, -0.05f}, {1.0f, 0.0f, 1.0f}));
	vao.bind();
	vbo.bind();
	vbo.vertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(InstancedVertex),
	                        (void*) (offsetof(InstancedVertex, position)));
	vbo.vertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(InstancedVertex),
	                        (void*) (offsetof(InstancedVertex, color)));
	vbo.bufferData(vertices.size() * sizeof(InstancedVertex), &vertices[0], GL_STATIC_DRAW);
	instancedVbo.bind();
	instancedVbo.vertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
	instancedVbo.bufferData(100 * sizeof(Vector2f), &translations[0], GL_STATIC_DRAW);
	instancedVbo.unbind();
	glVertexAttribDivisor(2, 1);
}

void Particle::updateLife(float dt) {
	lifetime -= dt;
}

bool Particle::isAlive() {
	return lifetime > 0;
}

void Particle::setData() {

}


