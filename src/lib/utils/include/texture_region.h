//
// Created by Viktor on 15.1.2021 г..
//

#ifndef TEXTURE_REGION_H
#define TEXTURE_REGION_H


#include "texture.h"

class TextureRegion {
private:
	Texture* texture;
	int x;
	int y;
	int regionWidth;
	int regionHeight;
public:
	TextureRegion() = default;
	TextureRegion(Texture* texture, int width, int height);
	TextureRegion(Texture* texture, int x, int y, int width, int height);
	void set(Texture* texture, int x, int y, int width, int height);
	void draw() const;
	void draw(const int x, const int y);
	void draw(const int x, const int y, const int width, const int height);
	void draw(const int x, const int y, const int width, const int height, SDL_RendererFlip flip);


};


#endif //TEXTURE_REGION_H
