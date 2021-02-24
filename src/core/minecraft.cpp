//
// Created by Viktor on 23.12.2020 г..
//

#include "include/minecraft.h"
#include "../lib/include/lib.h"


void GLAPIENTRY
MessageCallback(GLenum source,
                GLenum type,
                GLuint id,
                GLenum severity,
                GLsizei length,
                const GLchar* message,
                const void* userParam) {
	fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
	        (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
	        type, severity, message);
}

void Minecraft::create() {
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);
	gameStateManager = new GameStateManager();
	dataSystem = new DataSystem();
	graphicsSystem = new GraphicsSystem(this);
	logicSystem = new LogicSystem(this);

	graphicsSystem->create();
	logicSystem->init();
}

void Minecraft::render() {
	logicSystem->update();
	graphicsSystem->render(Lib::graphics->getDeltaTime());
}

void Minecraft::pause() {

}

void Minecraft::resume() {

}

void Minecraft::resize(const int width, const int height) {
	graphicsSystem->resizeViewport(width, height);
}

Minecraft::~Minecraft() {
	delete gameStateManager;
	delete graphicsSystem;
	delete dataSystem;
	delete logicSystem;
}

