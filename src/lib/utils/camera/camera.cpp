//
// Created by Viktor on 21.12.2020 г..
//

#include <cmath>
#include "include/camera.h"
#include "../geometry/include/vector3.h"
#include "../../include/lib.h"
#include "../math/include/math_utils.h"

Camera::Camera() : m_position({0, 0, 0}),
                   m_up({0.0, 1.0, 0.0}),
                   m_direction({0.0, 0.0, -1}) {
	m_viewportWidth = 0;
	m_viewportHeight = 0;
}


Camera::~Camera() {
}

void Camera::translate(float x, float y, float z) {
	m_position.x += x;
	m_position.y += y;
	m_position.z += z;
}


void Camera::rotateX(float degree) {
	float radians = MathUtils::toRadians(degree);
	Matrix4f rotationMatrix;
	rotationMatrix[A11] = std::cos(radians);
	rotationMatrix[A12] = -std::sin(radians);
	rotationMatrix[A21] = std::sin(radians);
	rotationMatrix[A22] = std::cos(radians);

}

void Camera::rotate(float deltaX, float deltaY) const {
//	*m_direction = m_direction->rotate(*m_up, deltaX).normalize();
//	Vector3f right = m_direction->cross(*m_up);
//	*m_direction = m_direction->rotate(right, deltaY).normalize();
}

void Camera::rotateY(float degree) {
	float radians = MathUtils::toRadians(degree);
	Matrix4f rotationMatrix;
	rotationMatrix[A00] = std::cos(radians);
	rotationMatrix[A02] = std::sin(radians);
	rotationMatrix[A20] = -std::sin(radians);
	rotationMatrix[A22] = std::cos(radians);

}

void Camera::rotateZ(float degree) {

}

void Camera::updateCombined() {

}


