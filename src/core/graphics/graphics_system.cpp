//
// Created by Viktor on 16.2.2021 г..
//

#include <iostream>
#include "include/graphics_system.h"
#include "../../lib/include/lib.h"
#include "screens/include/playing_screen.h"
#include "../include/minecraft.h"
#include "../../lib/utils/camera/include/perspective_camera.h"


int GRAPHICS_WIDTH;

int GRAPHICS_HEIGHT;

float WORLD_WIDTH = 240;

float WORLD_HEIGHT = 120;

GraphicsSystem::GraphicsSystem(Minecraft* game) : m_pGame(game) {
	GRAPHICS_WIDTH = Lib::graphics->getWidth();
	GRAPHICS_HEIGHT = Lib::graphics->getHeight();

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);



	m_pViewport = new UniversalViewport(WORLD_WIDTH, WORLD_HEIGHT, new PerspectiveCamera(70));
	m_pViewport->update(GRAPHICS_WIDTH, GRAPHICS_HEIGHT, false);
}

void GraphicsSystem::create() {
	m_pScreen[Playing] = new PlayingScreen(m_pGame);

	m_pScreen[Playing]->start();
}

void GraphicsSystem::render(const float dt) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.4, 0.4, 0.4, 1.0);

	m_pScreen[m_pGame->m_gameStateManager.getCurrentState()]->render(dt);
}

void GraphicsSystem::resizeViewport(const int width, const int height) {
	m_pViewport->update(width, height, false);
}

void GraphicsSystem::start(int state) {
	m_pScreen[state]->start();
}

UniversalViewport* GraphicsSystem::getViewport() const {
	return m_pViewport;
}


GraphicsSystem::~GraphicsSystem() {
	for (auto& screen : m_pScreen) {
		delete screen;
	}

	delete m_pViewport;
}


