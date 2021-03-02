//
// Created by Viktor on 20.12.2020 г..
//
#include "GL/glew.h"
#include <cmath>
#include "include/viewport.h"

void Viewport::apply(bool centerCamera) const {
	glViewport(m_screenX, m_screenY, m_screenWidth, m_screenHeight);
	m_pCamera->m_viewportWidth = m_worldWidth;
	m_pCamera->m_viewportHeight = m_worldHeight;
	if (centerCamera) {
		m_pCamera->m_position.x = m_worldWidth / 2;
		m_pCamera->m_position.y = m_worldHeight / 2;
		m_pCamera->m_position.z = 0;
	}
	m_pCamera->update(true);
}

void Viewport::setCamera(Camera* camera) {
	this->m_pCamera = camera;
}

Camera* Viewport::getCamera() const {
	return m_pCamera;
}

float Viewport::getWorldWidth() const {
	return m_worldWidth;
}

void Viewport::setWorldWidth(float worldWidth) {
	Viewport::m_worldWidth = worldWidth;
}

float Viewport::getWorldHeight() const {
	return m_worldHeight;
}

void Viewport::setWorldHeight(float worldHeight) {
	Viewport::m_worldHeight = worldHeight;
}

void Viewport::setWorldSize(float& worldWidth, float& worldHeight) {
	this->m_worldWidth = worldWidth;
	this->m_worldHeight = worldHeight;
}

void Viewport::setScreenBounds(const int x, const int y, const int& width, const int& height) {
	m_screenX = x;
	m_screenY = y;
	m_screenWidth = width;
	m_screenHeight = height;
}






