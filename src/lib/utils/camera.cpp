//
// Created by Viktor on 21.12.2020 г..
//

#include <cmath>
#include "include/camera.h"
#include "geometry/include/vector3.h"
#include "../include/lib.h"

Camera::Camera() {
    position = new Vector3f(0,0,3);
    up = new Vector3f(0.0, 1.0, 0.0);
    direction = new Vector3f(0.0, 0.0, -1);

    viewportWidth = 0;
    viewportHeight = 0;
}


Camera::~Camera() {
    delete position;
    delete up;
}

void Camera::translate(float x, float y, float z) const {
    position->x += x;
    position->y += y;
    position->z += z;
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
    *direction = direction->rotate(*up, deltaX).normalize();
    Vector3f right = direction->cross(*up);
    *direction = direction->rotate(right, deltaY).normalize();
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


