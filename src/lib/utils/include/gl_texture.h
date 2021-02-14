//
// Created by Viktor on 8.1.2021 г..
//

#ifndef GL_TEXTURE_H
#define GL_TEXTURE_H

#include "GL/glew.h"
#include <SDL.h>
#include <string>

class GLTexture {
private:
    unsigned int textureBuffer;
    SDL_Surface* surface;
    GLenum textureFormat;
    int colorCount;
public:
    explicit GLTexture(std::string path);
    GLTexture() = default;
    ~GLTexture();
    void performChecks();
    unsigned int getBuffer();

};


#endif //GL_TEXTURE_H
