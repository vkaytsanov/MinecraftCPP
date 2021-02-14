//
// Created by Viktor on 8.1.2021 г..
//

#ifndef OBJECT_H
#define OBJECT_H
#include "GL/glew.h"

class Object {
protected:
    unsigned int vertexBuffer;
    unsigned int shaderID;
public:
    Object() = default;
    virtual ~Object();
    virtual void draw() = 0;
    void setShader(unsigned int id);
    unsigned int getShader();
};


#endif //OBJECT_H
