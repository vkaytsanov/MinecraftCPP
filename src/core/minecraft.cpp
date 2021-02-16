//
// Created by Viktor on 23.12.2020 г..
//

#include "include/minecraft.h"
#include "../lib/include/lib.h"
#include "../lib/utils/include/perspective_camera.h"



void Minecraft::create() {
    batch = new SpriteBatch();
    gameStateManager = new GameStateManager();
	dataSystem = new DataSystem();
	graphicsSystem = new GraphicsSystem(this);
	logicSystem = new LogicSystem(this);

	graphicsSystem->create();
}

void Minecraft::render() {
	graphicsSystem->render(Lib::graphics->getDeltaTime());
}

void Minecraft::pause() {

}

void Minecraft::resume() {

}

void Minecraft::resize(const int width, const int height) {
    graphicsSystem->resizeViewport(width, height);
}

Minecraft::~Minecraft(){
    delete batch;
    delete gameStateManager;
	delete graphicsSystem;
	delete dataSystem;
}

