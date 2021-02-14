//
// Created by Viktor on 8.1.2021 г..
//

#include "include/object.h"


Object::~Object() {
    glDeleteBuffers(1, &vertexBuffer);
}

void Object::setShader(unsigned int id) {
    shaderID = id;
}

unsigned int Object::getShader() {
    return shaderID;
}



