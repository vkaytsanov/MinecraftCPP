//
// Created by Viktor on 19.12.2020 г..
//

#ifndef TEXTURE_H
#define TEXTURE_H


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
	SDL_Texture* getRawTexture() const;
	const SDL_Rect& getRect() const;
	void draw() const;
    void draw(const int x, const int y);
    void draw(const int x, const int y, const int width, const int height);
};


#endif //TEXTURE_H
