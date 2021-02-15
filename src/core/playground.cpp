//
// Created by Viktor on 23.12.2020 г..
//

#include "include/playground.h"
#include "../lib/include/lib.h"
#include "../lib/utils/include/perspective_camera.h"



void Playground::create() {
    batch = new SpriteBatch();
    viewport = new UniversalViewport(240, 120, new PerspectiveCamera(70));
    viewport->update(Lib::graphics->getWidth(), Lib::graphics->getHeight(), false);
    cameraController = new FirstPersonCameraController(viewport->getCamera());

    Lib::input->setProcessor(cameraController);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_TEXTURE_2D);
//	glEnable(GL_CULL_FACE);
//	glCullFace(GL_BACK);

	dataSystem = new DataSystem();

}

void Playground::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.4, 0.4, 0.4, 1.0);

	if(Lib::input->isKeyPressed(SDLK_TAB)) {
		if(isWireframe){
			glPolygonMode(GL_FRONT, GL_FILL);
			glPolygonMode(GL_BACK, GL_FILL);
		}
		else {
			glPolygonMode(GL_FRONT, GL_LINE);
			glPolygonMode(GL_BACK, GL_LINE);
		}
		isWireframe = !isWireframe;
	}
    const float dt = Lib::graphics->getDeltaTime();

    cameraController->update(dt);

    batch->setProjectionMatrix(viewport->getCamera()->combined);

    batch->begin();
    batch->draw(dataSystem->cubesDb->getCube(Grass));
	batch->end();


}

void Playground::pause() {

}

void Playground::resume() {

}

void Playground::resize(const int width, const int height) {
    viewport->update(width, height, false);
}

Playground::~Playground(){
    delete viewport;
    delete batch;
    delete cameraController;
}

