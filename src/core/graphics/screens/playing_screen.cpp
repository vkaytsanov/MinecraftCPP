//
// Created by Viktor on 16.2.2021 г..
//

#include "include/playing_screen.h"
#include "../../include/minecraft.h"
#include "../../../lib/include/lib.h"

PlayingScreen::PlayingScreen(Minecraft* game) : game(game){
	cameraController = new FirstPersonCameraController(game->graphicsSystem->getViewport()->getCamera());
	cubeRenderer = new CubeRenderer(game);
	game->graphicsSystem->getViewport()->getCamera()->position->x = 5;
	game->graphicsSystem->getViewport()->getCamera()->position->z = 30;
}

void PlayingScreen::render(const float dt) {
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

	cameraController->update(dt);

	game->batch->setProjectionMatrix(game->graphicsSystem->getViewport()->getCamera()->combined);
    game->batch->begin();

    cubeRenderer->render();
	game->batch->end();
}

void PlayingScreen::start() {
	Lib::input->setProcessor(cameraController);
}

PlayingScreen::~PlayingScreen() {
	delete cameraController;
}


