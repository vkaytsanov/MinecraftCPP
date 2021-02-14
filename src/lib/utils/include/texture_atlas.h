//
// Created by Viktor on 14.2.2021 г..
//

#ifndef TEXTURE_ATLAS_H
#define TEXTURE_ATLAS_H


#include <string>
#include "gl_texture.h"
#include "texture_region.h"


class TextureAtlas {
private:
	char* fileName;
	float width;
	float height;
	char* format;
	TextureFilter minFilter;
	TextureFilter magFilter;
	TextureWrap wrap;
	void parseFileName(FILE* file);
	void parseSize(FILE* file);
	void parseFormat(FILE* file);
	void parseFilters(FILE* file);
	void parseWrap(FILE* file);
public:
	TextureAtlas(const char* path);
};


#endif //TEXTURE_ATLAS_H
