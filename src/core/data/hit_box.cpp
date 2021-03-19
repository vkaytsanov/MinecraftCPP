//
// Created by Viktor on 19.3.2021 г..
//

#include "include/hit_box.h"


HitBox::HitBox() {
	float vertices[] = {
			-0.01f, -0.01f, 1.01f,
			1.01f, -0.01f, 1.01f,
			1.01f, 1.01f, 1.01f,
			-0.01f, 1.01f, 1.01f,

			-0.01f, -0.01f, -0.01f,
			1.01f, -0.01f, -0.01f,
			1.01f, 1.01f, -0.01f,
			-0.01f, 1.01f, -0.01f,
	};
	unsigned int indices[] = {
			0, 1, 1, 2, 2, 3, 3, 0,
			4, 5, 5, 6, 6, 7, 7, 4,
			0, 4, 1, 5, 2, 6, 3, 7
	};

	m_cubeIbo.bind();
	m_cubeIbo.bufferData(sizeof(indices), &indices, GL_STATIC_DRAW);

	m_cubeVao.bind();
	m_cubeVbo.bind();
	m_cubeIbo.bind();
	m_cubeVbo.vertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr);
	m_cubeVao.unbind();

	m_cubeVbo.bind();
	m_cubeVbo.bufferData(sizeof(vertices), &vertices, GL_STATIC_DRAW);
	m_cubeVbo.unbind();

}

