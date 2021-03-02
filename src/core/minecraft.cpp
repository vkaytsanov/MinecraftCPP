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
	fprintf(stderr, "GL CALLBACK: %s m_type = 0x%x, severity = 0x%x, message = %s\n",
	        (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
	        type, severity, message);
}

void Minecraft::create() {
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);

	m_pDataSystem = new DataSystem();
	m_pGraphicsSystem = new GraphicsSystem(this);
	m_pLogicSystem = new LogicSystem(this);

	m_pGraphicsSystem->create();
	m_pLogicSystem->init();
}

void Minecraft::render() {
	m_pLogicSystem->update();
	m_pGraphicsSystem->render(Lib::graphics->getDeltaTime());
}

void Minecraft::pause() {

}

void Minecraft::resume() {

}

void Minecraft::resize(const int width, const int height) {
	m_pGraphicsSystem->resizeViewport(width, height);
}

Minecraft::~Minecraft() {
	delete m_pGraphicsSystem;
	delete m_pDataSystem;
	delete m_pLogicSystem;
}

