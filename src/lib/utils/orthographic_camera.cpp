//
// Created by Viktor on 21.12.2020 г..
//


#include "include/orthographic_camera.h"
#include "../include/lib.h"

OrthographicCamera::OrthographicCamera() {
	nearPlane = 0;

}

OrthographicCamera::OrthographicCamera(const float viewportWidth, const float viewportHeight) {
	this->viewportWidth = viewportWidth;
	this->viewportHeight = viewportHeight;
	nearPlane = 0;
	update();
}

void OrthographicCamera::update() {
	projection.setToOrthogonal(
			-viewportWidth / 2,
			viewportWidth / 2,
			-viewportHeight / 2,
			viewportHeight / 2,
			nearPlane,
			farPlane
	);
	view.setToLookAt(*position, *direction, *up);
	combined = projection * view;
}

void OrthographicCamera::translate(float x, float y) {
	Camera::translate(x, y, 0);
}


