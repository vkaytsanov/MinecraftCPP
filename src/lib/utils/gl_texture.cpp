//
// Created by Viktor on 8.1.2021 г..
//

#include "include/gl_texture.h"
#include "../include/lib.h"

GLTexture::GLTexture(std::string path) {
    surface = SDL_LoadBMP(path.c_str());

    performChecks();

    glGenTextures(1, &textureBuffer);
    glBindTexture(GL_TEXTURE_2D, textureBuffer);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 colorCount,
                 surface->w,
                 surface->h,
                 0,
                 textureFormat,
                 GL_UNSIGNED_BYTE,
                 surface->pixels);
}

GLTexture::~GLTexture() {
    SDL_FreeSurface(surface);
    surface = nullptr;
    glDeleteBuffers(1, &textureBuffer);
}

void GLTexture::performChecks() {
    if (surface == nullptr) {
        Lib::app->error("TextureError", SDL_GetError());
        exit(-1);
    }
    if ((surface->w & (surface->w - 1)) != 0) {
        Lib::app->error("TextureError", "BMP's width is not a power of 2");
    }
    if ((surface->h & (surface->h - 1)) != 0) {
        Lib::app->error("TextureError", "BMP's height is not a power of 2");
    }
    colorCount = surface->format->BytesPerPixel;
    if (colorCount == 4){
        // contains alpha channel
        textureFormat = surface->format->Rmask == 0x000000ff ? GL_RGBA : GL_BGRA;
    }
    else if(colorCount == 3){
        textureFormat = surface->format->Rmask == 0x000000ff ? GL_RGB : GL_BGR;
    }
    else{
        Lib::app->error("TextureError", "Colors arent right");
        exit(-1);
    }

}

unsigned int GLTexture::getBuffer() {
    return textureBuffer;
}


