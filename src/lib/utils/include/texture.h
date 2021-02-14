//
// Created by Viktor on 19.12.2020 г..
//

#ifndef DUCKHUNT_TEXTURE_H
#define DUCKHUNT_TEXTURE_H


#include <SDL.h>
#include <string>
#include "SDL_image.h"

class Texture {
private:
    SDL_Texture* rawTexture;
    SDL_Rect rect;
    int width;
    int height;
public:
    explicit Texture(const std::string& file_path);
    ~Texture();
    int getWidth() const;
    int getHeight() const;
    void draw() const;
    void draw(const int x, const int y);
    void draw(const int x, const int y, const int width, const int height);
};


#endif //DUCKHUNT_TEXTURE_H
