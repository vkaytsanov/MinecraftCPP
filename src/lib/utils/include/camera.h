//
// Created by Viktor on 21.12.2020 г..
//

#ifndef CAMERA_H
#define CAMERA_H

#include "../geometry/include/matrix4.h"
#include "../geometry/include/vector3.h"

/**
 *  @pdf https://www.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=&ved=2ahUKEwjz_Y71-t7tAhVCPuwKHVgYCCoQFjACegQIARAC&url=https%3A%2F%2Fweb.cs.wpi.edu%2F~emmanuel%2Fcourses%2Fcs543%2Ff13%2Fslides%2Flecture04_p3.pdf&usg=AOvVaw3DhRKP2d1wamu2osZL4Ibp
 *  @link https://en.wikipedia.org/wiki/Viewing_frustum
 */


class Camera {
public:
    /** near clipping plane */
    float nearPlane = 0.001f;
    /** far clipping plane */
    float farPlane = 100.f;
    /** Camera position vector */
    Vector3f* position;
    /** Camera up vector */
    Vector3f* up;
    /** Camera's looking direction vector */
    Vector3f* direction;
    /** Camera view matrix */
    Matrix4f view;
    /** Camera projection matrix */
    Matrix4f projection;
    /** Camera's combined matrix */
    Matrix4f combined;

    float viewportWidth;
    float viewportHeight;
    Camera();
    ~Camera();
    virtual void update() = 0;
    void updateCombined();
    void translate(float x, float y, float z) const;
    void rotateX(float degree);
    void rotate(float deltaX, float deltaY) const;
    void rotateY(float degree);
    void rotateZ(float degree);

};



#endif //CAMERA_H
