//
// Created by Viktor on 16.2.2021 г..
//

#include "include/playing_screen.h"
#include "../../include/minecraft.h"
#include "../../../lib/include/lib.h"

PlayingScreen::PlayingScreen(Minecraft* game) : m_pGame(game),
                                                m_cameraController(game->m_pGraphicsSystem->getViewport()->getCamera()),
                                                m_worldRenderer(game->m_pDataSystem, m_cameraController.getCamera()),
                                                m_skyboxRenderer(game->m_pDataSystem, m_cameraController.getCamera()){


	m_cameraController.getCamera()->m_position.x = 0;
	m_cameraController.getCamera()->m_position.y = 95;
	m_cameraController.getCamera()->m_position.z = 0;
}

void PlayingScreen::render(const float dt) {
	if (Lib::input->isKeyPressed(SDLK_TAB)) {
		if (m_isWireframe) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		m_isWireframe = !m_isWireframe;
	}

	m_cameraController.update(dt);
	m_skyboxRenderer.render();
	m_worldRenderer.render();
}

void PlayingScreen::start() {
	Lib::input->setProcessor(&m_cameraController);
}

PlayingScreen::~PlayingScreen() {

}


