//
// Created by Viktor on 6.1.2021 г..
//

#include "include/first_person_camera_controller.h"
#include "../include/lib.h"

FirstPersonCameraController::FirstPersonCameraController(Camera *camera) {
    this->camera = camera;
}

void FirstPersonCameraController::handleButtonMovement(const float& dt) {
    Vector3f vec = *camera->direction;
    if(Lib::input->isKeyPressed(SDLK_a)){
        *camera->position -= (vec.cross(*camera->up).normalize() * dt * CHARACTER_MOVEMENT_INTENSITY);
    }
    if(Lib::input->isKeyPressed(SDLK_d)){
        *camera->position += (vec.cross(*camera->up).normalize() * dt * CHARACTER_MOVEMENT_INTENSITY);
    }
    if(Lib::input->isKeyPressed(SDLK_w)){
        *camera->position += (vec.normalize() * dt * CHARACTER_MOVEMENT_INTENSITY);
    }
    if(Lib::input->isKeyPressed(SDLK_s)){
        *camera->position -= (vec.normalize() * dt * CHARACTER_MOVEMENT_INTENSITY);
    }
//    std::cout << camera->position->z << "\n";
}

void FirstPersonCameraController::handleMouseMovement(const float& dt) {
    if(Lib::input->isMouseLeftClick()) {

        horizontalAngle += -(Lib::input->getMouseDeltaX()) * dt * CAMERA_MOVEMENT_INTENSITY;
        verticalAngle += (Lib::input->getMouseDeltaY()) * dt * CAMERA_MOVEMENT_INTENSITY;

        camera->direction->x = std::cos(verticalAngle) * std::sin(horizontalAngle);
        camera->direction->y = std::sin(verticalAngle);
        camera->direction->z = std::cos(verticalAngle) * std::cos(horizontalAngle);

        Lib::input->resetMouse();


    }
}

void FirstPersonCameraController::update(const float& dt) {
    handleButtonMovement(dt);
    handleMouseMovement(dt);
    camera->update();
}
