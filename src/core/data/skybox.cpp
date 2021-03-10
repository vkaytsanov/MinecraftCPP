//
// Created by Viktor on 24.2.2021 г..
//

#include <vector>
#include "include/skybox.h"
#include "include/asset_manager.h"

Skybox::Skybox(){
	float vertices[3 * 6 * 6] = {
			-10.0f,  10.0f, -10.0f,
			-10.0f, -10.0f, -10.0f,
			10.0f, -10.0f, -10.0f,
			10.0f, -10.0f, -10.0f,
			10.0f,  10.0f, -10.0f,
			-10.0f,  10.0f, -10.0f,

			-10.0f, -10.0f,  10.0f,
			-10.0f, -10.0f, -10.0f,
			-10.0f,  10.0f, -10.0f,
			-10.0f,  10.0f, -10.0f,
			-10.0f,  10.0f,  10.0f,
			-10.0f, -10.0f,  10.0f,

			10.0f, -10.0f, -10.0f,
			10.0f, -10.0f,  10.0f,
			10.0f,  10.0f,  10.0f,
			10.0f,  10.0f,  10.0f,
			10.0f,  10.0f, -10.0f,
			10.0f, -10.0f, -10.0f,

			-10.0f, -10.0f,  10.0f,
			-10.0f,  10.0f,  10.0f,
			10.0f,  10.0f,  10.0f,
			10.0f,  10.0f,  10.0f,
			10.0f, -10.0f,  10.0f,
			-10.0f, -10.0f,  10.0f,

			-10.0f,  10.0f, -10.0f,
			10.0f,  10.0f, -10.0f,
			10.0f,  10.0f,  10.0f,
			10.0f,  10.0f,  10.0f,
			-10.0f,  10.0f,  10.0f,
			-10.0f,  10.0f, -10.0f,

			-10.0f, -10.0f, -10.0f,
			-10.0f, -10.0f,  10.0f,
			10.0f, -10.0f, -10.0f,
			10.0f, -10.0f, -10.0f,
			-10.0f, -10.0f,  10.0f,
			10.0f, -10.0f,  10.0f
	};
	// to get the path to the assets
	AssetManager::getInstance();
	std::vector<std::string> paths = {
			ASSETS_LOCATION + "skybox/skybox-right.png",
			ASSETS_LOCATION + "skybox/skybox-left.png",
			ASSETS_LOCATION + "skybox/skybox-front.png",
			ASSETS_LOCATION + "skybox/skybox-bottom.png",
			ASSETS_LOCATION + "skybox/skybox-front.png",
			ASSETS_LOCATION + "skybox/skybox-back.png",
	};

	textureCubeMap = TextureCubeMap(paths);

	vao.bind();
	vbo.bind();
	vbo.bufferData(sizeof(vertices), vertices, GL_STATIC_DRAW);
	vbo.vertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
	vao.unbind();
}


const VertexArray& Skybox::getVao() const {
	return vao;
}



