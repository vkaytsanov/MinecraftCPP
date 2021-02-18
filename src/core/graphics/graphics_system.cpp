//
// Created by Viktor on 16.2.2021 г..
//

#include <iostream>
#include "include/graphics_system.h"
#include "../../lib/include/lib.h"
#include "screens/include/playing_screen.h"
#include "../include/minecraft.h"
#include "../../lib/utils/include/perspective_camera.h"


int GRAPHICS_WIDTH;

int GRAPHICS_HEIGHT;

float WORLD_WIDTH = 240;

float WORLD_HEIGHT = 120;

GraphicsSystem::GraphicsSystem(Minecraft* game) : game(game) {
	GRAPHICS_WIDTH = Lib::graphics->getWidth();
	GRAPHICS_HEIGHT = Lib::graphics->getHeight();

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_TEXTURE_2D);
//	glEnable(GL_CULL_FACE);
//	glCullFace(GL_BACK);

	viewport = new UniversalViewport(WORLD_WIDTH, WORLD_HEIGHT,new PerspectiveCamera(70));
	viewport->update(GRAPHICS_WIDTH, GRAPHICS_HEIGHT, false);
}

void GraphicsSystem::create() {
	screens[Playing] = new PlayingScreen(game);

	screens[Playing]->start();
}

void GraphicsSystem::render(const float dt) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.4, 0.4, 0.4, 1.0);

	screens[game->gameStateManager->getCurrentState()]->render(dt);
}

void GraphicsSystem::resizeViewport(const int width, const int height) {
	viewport->update(width, height, false);
}

void GraphicsSystem::start(int state) {
	screens[state]->start();
}

UniversalViewport* GraphicsSystem::getViewport() const {
	return viewport;
}


GraphicsSystem::~GraphicsSystem() {
	for (auto& screen : screens) {
		delete screen;
	}

	delete viewport;
}


