//
// Created by Viktor on 8.1.2021 г..
//

#ifndef GL_TEXTURE_H
#define GL_TEXTURE_H

#include "GL/glew.h"
#include <SDL.h>
#include <string>

enum TextureFilter{
	Nearest = GL_NEAREST,
	Linear = GL_LINEAR,
	MipMap = GL_MIPMAP,
	MipMapNearestNearest = GL_NEAREST_MIPMAP_NEAREST,
	MipMapLinearNearest = GL_LINEAR_MIPMAP_NEAREST,
	MipMapNearestLinear = GL_NEAREST_MIPMAP_LINEAR,
	MipMapLinearLinear = GL_LINEAR_MIPMAP_LINEAR,
};

enum TextureWrap{
	Repeat = GL_REPEAT,
	RepeatMirrored = GL_MIRRORED_REPEAT,
	ClampToEdge = GL_CLAMP_TO_EDGE,
};

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
