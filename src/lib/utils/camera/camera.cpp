//
// Created by Viktor on 21.12.2020 г..
//

#include "include/camera.h"

Camera::Camera() {
	m_pTransform = new Transform();
	m_viewportWidth = 0;
	m_viewportHeight = 0;
}


Camera::~Camera() {
}

Vector3f Camera::getForwardVector() {
	return Vector3f(m_view[A02], m_view[A12], m_view[A22]);
}

Vector3f Camera::getRightVector() {
	return Vector3f(m_view[A00], m_view[A10], m_view[A20]);
}
