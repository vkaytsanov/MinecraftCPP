//
// Created by Viktor on 19.12.2020 г..
//

#ifndef DUCKHUNT_SPRITE_BATCH_H
#define DUCKHUNT_SPRITE_BATCH_H

#include "../geometry/include/matrix4.h"
#include "shaders.h"
#include "../../../core/objects/include/texture_object.h"
#include "../../../core/objects/include/color_object.h"

class SpriteBatch {
private:
    Matrix4f combined;
    Matrix4f projection;
    Matrix4f transform;
    Shaders* shaders;
    bool drawing;
    void setupMatrices();
public:
    SpriteBatch();
    ~SpriteBatch();
    void setProjectionMatrix(const Matrix4f& mat);
    void setTransformMatrix(const Matrix4f& mat);
    void begin();
    void draw(Object* object);
    void end();

};


#endif //DUCKHUNT_SPRITE_BATCH_H
