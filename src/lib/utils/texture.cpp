//
// Created by Viktor on 19.12.2020 г..
//

#include "include/texture.h"
#include "../include/lib.h"


Texture::Texture(const std::string& file_path) {
    //Get the image
    SDL_Surface *surface = IMG_Load(file_path.c_str());
    if (surface) {
        //Creating texture from the image
        rawTexture = SDL_CreateTextureFromSurface(
                Lib::graphics->getRenderer(),
                surface
                );

        //Free the memory from the created surface
        SDL_FreeSurface(surface);

        //Getting the width and height of the texture
        SDL_QueryTexture(rawTexture, nullptr, nullptr, &width, &height);
        //Create drawing rectangle
        rect.x = 0;
        rect.y = 0;
        rect.w = width;
        rect.h = height;
    }
    else{
        Lib::app->error("Texture", "Couldn't find the image");
    }
}

Texture::~Texture() {
    SDL_DestroyTexture(rawTexture);
}

int Texture::getWidth() const {
    return width;
}

int Texture::getHeight() const {
    return height;
}

void Texture::draw() const {
    SDL_RenderCopy(Lib::graphics->getRenderer(), rawTexture, nullptr, &rect);
}

void Texture::draw(const int x, const int y) {
    rect.x = x;
    rect.y = y;
    SDL_RenderCopy(Lib::graphics->getRenderer(), rawTexture, nullptr, &rect);
}

void Texture::draw(const int x, const int y, const int w, const int h) {
    rect = {x, y, w, h};
    SDL_RenderCopy(Lib::graphics->getRenderer(), rawTexture, nullptr, &rect);

}

SDL_Texture* Texture::getRawTexture() const {
	return rawTexture;
}

const SDL_Rect& Texture::getRect() const {
	return rect;
}



