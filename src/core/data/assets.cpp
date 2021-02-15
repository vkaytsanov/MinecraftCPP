//
// Created by Viktor on 18.12.2020 г..
//

#include <stdexcept>
#include "include/assets.h"
#include "../../lib/include/lib.h"


Assets::Assets() {
	std::string spritePaths[] = {
			"spriteSheet.png"
	};

	int c = 0;
	for (std::string& path : spritePaths) {
		mapped_sprites[stripName(path)] = new Texture(ASSETS_LOCATION + path);
		c++;
	}

	Lib::app->log("Sprites Loaded", c);

}

Texture* Assets::getSprite(const std::string name) {
	if (mapped_sprites.find(name) == mapped_sprites.end()) {
		throw std::runtime_error("Sprite " + name + " doesn't exists");
	}
	return mapped_sprites[name];
}

Assets::~Assets() {
	for (const auto& it : mapped_sprites) {
		delete it.second;
	}
}

std::string Assets::stripName(std::string& name) {
	return name.substr(0, name.length() - 4);
}

