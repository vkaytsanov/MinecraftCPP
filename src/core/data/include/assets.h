//
// Created by Viktor on 18.12.2020 г..
//

#ifndef MOD_ASSETS_H
#define MOD_ASSETS_H

#include <unordered_map>
#include "SDL.h"
#include "SDL_image.h"
#include "../../../lib/utils/include/texture.h"

// TODO Don't know how to use project path
static std::string ASSETS_LOCATION = __FILE__ "/../../../../assets/sprites/";

class Assets {
private:
    std::unordered_map<std::string, Texture*> mapped_sprites;
    static std::string stripName(std::string& name);
public:
    Assets();
    ~Assets();
	Texture* getSprite(std::string name);
};


#endif //MOD_ASSETS_H
