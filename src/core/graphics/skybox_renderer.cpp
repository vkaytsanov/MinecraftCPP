//
// Created by Viktor on 24.2.2021 г..
//

#include "include/skybox_renderer.h"

SkyboxRenderer::SkyboxRenderer(DataSystem* dataSystem, Camera* camera) : skybox(&dataSystem->skybox),
                                                                         skyboxShader(&dataSystem->skyboxShader),
                                                                         camera(camera) {

}

void SkyboxRenderer::render() {
	glDepthMask(GL_FALSE);

	skyboxShader->begin();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skybox->textureCubeMap.getBuffer());

	Matrix4f mat = camera->combined;
	mat.a[A31] = 0;
	mat.a[A32] = 0;
	mat.a[A33] = 1;
	mat.a[A30] = 0;
	skyboxShader->setMatrix4("proj", mat);
	skyboxShader->setInt("texSkybox", 0);

	skybox->getVao().bind();
	glDrawArrays(GL_TRIANGLES, 0, 36);
	skybox->getVao().unbind();

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	skyboxShader->end();

	glDepthMask(GL_TRUE);

}
