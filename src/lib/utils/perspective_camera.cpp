//
// Created by Viktor on 5.1.2021 г..
//

#include "include/perspective_camera.h"


PerspectiveCamera::PerspectiveCamera() {
	fov = 60;
}

PerspectiveCamera::PerspectiveCamera(const float fieldOfView) {
	fov = fieldOfView;
}

PerspectiveCamera::PerspectiveCamera(const float fieldOfView, const float worldWidth, const float worldHeight) {
	fov = fieldOfView;
	this->viewportWidth = worldWidth;
	this->viewportHeight = worldHeight;
	update();
}

void PerspectiveCamera::update() {

	projection.setToProjection(fov,
	                           nearPlane,
	                           farPlane,
	                           viewportWidth / viewportHeight);
	Vector3f target = *position + *direction;
	view.setToLookAt(*position, target, *up);
	combined = projection * view;
//    combined.debug();
}
