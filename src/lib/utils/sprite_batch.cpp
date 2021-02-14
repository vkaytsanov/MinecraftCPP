//
// Created by Viktor on 19.12.2020 г..
//

#include "include/sprite_batch.h"
#include "../include/lib.h"

SpriteBatch::SpriteBatch() {
    drawing = false;
    shaders = new Shaders();
}

void SpriteBatch::setupMatrices() {
    combined = (projection * transform);
    unsigned int matrixID = glGetUniformLocation(shaders->getProgram(), "proj");
    if(matrixID == -1){
        Lib::app->error("uniforms", "invalid location");
    }
    else{
        glUniformMatrix4fv(matrixID, 1, false, combined.a);
    }

}

void SpriteBatch::begin() {
    if(drawing) return;

    drawing = true;
}

void SpriteBatch::draw(Object *object) {
    glUseProgram(object->getShader());
    setupMatrices();

    object->draw();

    glUseProgram(0);
}



void SpriteBatch::end() {
    if(!drawing) return;

    drawing = false;
}

void SpriteBatch::setProjectionMatrix(const Matrix4f& mat) {
    projection = mat;
}

void SpriteBatch::setTransformMatrix(const Matrix4f& mat) {
    transform = mat;
}

SpriteBatch::~SpriteBatch() {
    delete shaders;
}






