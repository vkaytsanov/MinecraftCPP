//
// Created by Viktor on 15.1.2021 г..
//

#include "include/texture_region.h"
#include "../include/lib.h"
#include <cmath>


TextureRegion::TextureRegion(Texture* texture) {
	this->texture = texture;
	regionWidth = texture->getWidth();
	regionHeight = texture->getHeight();
}

TextureRegion::TextureRegion(Texture* texture, int width, int height) {
	this->texture = texture;
	setRegionXY(0, 0, width, height);
}

TextureRegion::TextureRegion(Texture* texture, int x, int y, int width, int height) {
	this->texture = texture;
	setRegionXY(x, y, width, height);
}

void TextureRegion::setRegionXY(int x, int y, int width, int height) {
	float invWidth = 1.00f / (float) texture->getWidth();
	float invHeight = 1.00f / (float) texture->getHeight();

	setRegionUV((float) x * invWidth, (float) y * invHeight, (float) (x + width) * invWidth,
	            (float) (y + height) * invHeight);

	regionWidth = width;
	regionHeight = height;
}

void TextureRegion::setRegionUV(float u, float v, float u2, float v2) {

	this->u = u;
	this->v = v;
	this->u2 = u2;
	this->v2 = v2;
}

Texture* TextureRegion::getTexture() const {
	return texture;
}

float TextureRegion::getU() const {
	return u;
}

float TextureRegion::getV() const {
	return v;
}

float TextureRegion::getU2() const {
	return u2;
}

float TextureRegion::getV2() const {
	return v2;
}

TextureRegion** TextureRegion::split(int blockWidth, int blockHeight) {
	int rows = regionHeight / blockHeight;
	int cols = regionWidth / blockWidth;

	TextureRegion** blocks = new TextureRegion* [rows];
	for (int i = 0; i < rows; i++) {
		blocks[i] = new TextureRegion[cols];
	}


	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			blocks[i][j] = TextureRegion(texture, i * blockWidth, j * blockHeight, blockWidth, blockHeight);
		}
	}
	return blocks;
}


float* TextureRegion::getUVs() {
	return new float[6 * 4 * 2]{
			// front
			u, v2,
			u2, v2,
			u2, v,
			u, v,
			// back
			u2, v2,
			u2, v,
			u, v,
			u, v2,
			// top
//			u, u,
//			v, v,
//			v, v,
//			u, u,
			u, v2,
			u2, v2,
			u2, v,
			u, v,
			//bottom
			u, v2,
			u2, v2,
			u2, v,
			u, v,
			//left
			u, v2,
			u2, v2,
			u2, v,
			u, v,
			//right
			u2, v2,
			u2, v,
			u, v,
			u, v2,







	};


}

int TextureRegion::getRegionX() const {
	return (int) std::round(u * (float) texture->getWidth());
}

int TextureRegion::getRegionY() const {
	return (int) std::round(v * (float) texture->getHeight());
}

TextureRegion TextureRegion::operator+(const TextureRegion tR) {
	setRegionXY(std::min(getRegionX(), tR.getRegionX()), std::min(getRegionY(), tR.getRegionY()),
	            regionWidth + tR.regionWidth, regionHeight);
	return *this;
}




