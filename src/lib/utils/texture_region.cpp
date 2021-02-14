//
// Created by Viktor on 15.1.2021 г..
//

#include "include/texture_region.h"
#include "../include/lib.h"
#include <cmath>

TextureRegion::TextureRegion(Texture* texture, int width, int height) {
	this->texture = texture;
	this->x = 0;
	this->y = 0;
	this->regionWidth = width;
	this->regionHeight = height;
}

TextureRegion::TextureRegion(Texture* texture, int x, int y, int width, int height) {
	this->texture = texture;
	this->x = x;
	this->y = y;
	this->regionWidth = width;
	this->regionHeight = height;
}

void TextureRegion::draw() const {
}

void TextureRegion::draw(const int x, const int y) {
	SDL_Rect srcRect = {this->x, this->y, regionWidth, regionHeight};
	SDL_Rect dstRect = {x, y, regionWidth, regionHeight};
	SDL_RenderCopy(Lib::graphics->getRenderer(), texture->getRawTexture(), &srcRect, &dstRect);
}

void TextureRegion::draw(const int x, const int y, const int width, const int height) {
	SDL_Rect srcRect = {this->x, this->y, regionWidth, regionHeight};
	SDL_Rect dstRect = {x, y, width, height};
	SDL_RenderCopy(Lib::graphics->getRenderer(), texture->getRawTexture(), &srcRect, &dstRect);
}

void TextureRegion::draw(const int x, const int y, const int width, const int height, SDL_RendererFlip flip) {
	SDL_Rect srcRect = {this->x, this->y, regionWidth, regionHeight};
	SDL_Rect dstRect = {x, y, width, height};
	SDL_RenderCopyEx(Lib::graphics->getRenderer(), texture->getRawTexture(), &srcRect, &dstRect, 0, nullptr, flip);

}

void TextureRegion::set(Texture* texture, int x, int y, int width, int height) {
	this->texture = texture;
	this->x = x;
	this->y = y;
	this->regionWidth = width;
	this->regionHeight = height;
}
