//
// Created by Viktor on 6.1.2021 г..
//

#ifndef FIRST_PERSON_CAMERA_CONTROLLER_H
#define FIRST_PERSON_CAMERA_CONTROLLER_H


#include "camera.h"

class FirstPersonCameraController {
private:
    Camera* camera;
    float horizontalAngle = 3.14f;
    float verticalAngle = 0;
    const float CHARACTER_MOVEMENT_INTENSITY = 5.f;
    const float CAMERA_MOVEMENT_INTENSITY = 0.5f;
    void handleButtonMovement(const float& dt);
    void handleMouseMovement(const float& dt);
public:
    explicit FirstPersonCameraController(Camera* camera);
    void update(const float& dt);
};


#endif //FIRST_PERSON_CAMERA_CONTROLLER_H
