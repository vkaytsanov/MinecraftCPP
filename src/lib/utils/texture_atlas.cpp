//
// Created by Viktor on 14.2.2021 г..
//

#include "include/texture_atlas.h"
#include "../include/lib.h"

TextureAtlas::TextureAtlas(const char* path) {
	FILE* file;
	errno_t err = fopen_s(&file, path, "r");
	if (err) {
		Lib::app->error("TextureAtlas", "Impossible to open the file !");
		exit(-1);
	}

	parseFileName(file);
	parseSize(file);

	while(true){
		char line[64];
		int res = fscanf_s(file, "%s", line, sizeof(line));
		if (res == EOF) break;
	}

}

void TextureAtlas::parseFileName(FILE* file) {
	fscanf_s(file, "%s", fileName, sizeof(fileName));
}

void TextureAtlas::parseSize(FILE* file) {
	fscanf_s(file, "%d", width, sizeof(width));
	fscanf_s(file, "%d", height, sizeof(height));
}

void TextureAtlas::parseFormat(FILE* file) {
	fscanf_s(file, "%s", format, 32);
}

void TextureAtlas::parseFilters(FILE* file) {
	fscanf_s(file, "%s", format, 32);
}

void TextureAtlas::parseWrap(FILE* file) {
	fscanf_s(file, "%s");
}
