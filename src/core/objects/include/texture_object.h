//
// Created by Viktor on 9.1.2021 г..
//

#ifndef TEXTURE_OBJECT_H
#define TEXTURE_OBJECT_H


#include "object.h"
#include "../../../lib/utils/include/gl_texture.h"

class TextureObject : public Object{
protected:
    unsigned int uvBuffer;
    unsigned int verticesSize;
    GLTexture* texture;
public:
    explicit TextureObject(const char* objFile);
    ~TextureObject() override;
    void draw() override;
};


#endif //TEXTURE_OBJECT_H
