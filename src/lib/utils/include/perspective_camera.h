//
// Created by Viktor on 5.1.2021 г..
//

#ifndef PERSPECTIVE_CAMERA_H
#define PERSPECTIVE_CAMERA_H


#include "camera.h"

class PerspectiveCamera : public Camera{
private:
    float fov;
public:
    PerspectiveCamera();
    explicit PerspectiveCamera(float fieldOfView);
    PerspectiveCamera(float fieldOfView, float worldWidth, float worldHeight);
    void update() override;
};


#endif //PERSPECTIVE_CAMERA_H
