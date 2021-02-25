//
// Created by Viktor on 20.12.2020 г..
//
#include "GL/glew.h"
#include <cmath>
#include "include/viewport.h"

void Viewport::apply(bool centerCamera) const {
	glViewport(screenX, screenY, screenWidth, screenHeight);
	camera->viewportWidth = worldWidth;
	camera->viewportHeight = worldHeight;
	if (centerCamera) {
		camera->position->x = worldWidth / 2;
		camera->position->y = worldHeight / 2;
		camera->position->z = 0;
	}
	camera->update();
}

void Viewport::setCamera(Camera* camera) {
	this->camera = camera;
}

Camera* Viewport::getCamera() const {
	return camera;
}

float Viewport::getWorldWidth() const {
	return worldWidth;
}

void Viewport::setWorldWidth(float worldWidth) {
	Viewport::worldWidth = worldWidth;
}

float Viewport::getWorldHeight() const {
	return worldHeight;
}

void Viewport::setWorldHeight(float worldHeight) {
	Viewport::worldHeight = worldHeight;
}

void Viewport::setWorldSize(float& worldWidth, float& worldHeight) {
	this->worldWidth = worldWidth;
	this->worldHeight = worldHeight;
}

void Viewport::setScreenBounds(const int x, const int y, const int& width, const int& height) {
	screenX = x;
	screenY = y;
	screenWidth = width;
	screenHeight = height;
}






