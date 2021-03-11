//
// Created by Viktor on 11.3.2021 г..
//
#include "include/transform.h"

void Transform::translate(const float x, const float y, const float z) {
	position.x += x;
	position.y += y;
	position.z += z;

	hasChanged = true;
}

void Transform::translate(const Vector3f& vec) {
	position += vec;

	hasChanged = true;
}

void Transform::rotate(const float roll, const float pitch, const float yaw) {
	rotation.x += roll;
	rotation.y += pitch;
	rotation.z += yaw;

	hasChanged = true;
}

void Transform::rotate(const Vector3f& vec) {
	eulerAngles += vec;

	hasChanged = true;
}
