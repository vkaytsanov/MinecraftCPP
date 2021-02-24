//
// Created by Viktor on 16.2.2021 г..
//

#include "include/playing_screen.h"
#include "../../include/minecraft.h"
#include "../../../lib/include/lib.h"

PlayingScreen::PlayingScreen(Minecraft* game) : game(game),
                                                cameraController(game->graphicsSystem->getViewport()->getCamera()),
                                                worldRenderer(game->dataSystem, cameraController.getCamera()) {


	cameraController.getCamera()->position->x = 0;
	cameraController.getCamera()->position->y = CHUNK_SIZE_Y / 1.5f;
	cameraController.getCamera()->position->z = 0;
}

void PlayingScreen::render(const float dt) {
	if (Lib::input->isKeyPressed(SDLK_TAB)) {
		if (isWireframe) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		} else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		isWireframe = !isWireframe;
	}

	cameraController.update(dt);
	worldRenderer.render();
}

void PlayingScreen::start() {
	Lib::input->setProcessor(&cameraController);
}

PlayingScreen::~PlayingScreen() {

}


