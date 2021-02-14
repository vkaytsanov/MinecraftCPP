//
// Created by Viktor on 20.12.2020 г..
//

#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "SDL.h"
#include "camera.h"

class Viewport {
private:
    Camera* camera;
    float worldWidth;
    float worldHeight;
    int screenX;
    int screenY;
    int screenWidth;
    int screenHeight;
protected:
    void setScreenBounds(int x, int y, const int& width, const int& height);
public:
    virtual void update(int screenWidth, int screenHeight, bool centerCamera) = 0;
    void apply(bool centerCamera) const;
    void setCamera(Camera *camera);
    void setWorldWidth(float worldWidth);
    void setWorldHeight(float worldHeight);
    void setWorldSize(float& worldWidth, float& worldHeight);
    Camera *getCamera() const;
    float getWorldWidth() const;
    float getWorldHeight() const;
};


#endif //VIEWPORT_H
