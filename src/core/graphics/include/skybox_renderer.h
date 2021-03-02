//
// Created by Viktor on 24.2.2021 г..
//

#ifndef SKYBOX_RENDERER_H
#define SKYBOX_RENDERER_H

#include "../../data/include/skybox.h"
#include "../../../lib/utils/include/shaders.h"
#include "../../../lib/utils/camera/include/camera.h"
#include "../../data/include/data_system.h"

class SkyboxRenderer {
private:
	Skybox* skybox;
	Camera* camera;
	Shaders* skyboxShader;
public:
	SkyboxRenderer(DataSystem* dataSystem, Camera* camera);
	void render();

};


#endif //SKYBOX_RENDERER_H
