//
// Created by Viktor on 18.12.2020 г..
//

#ifndef MOD_ASSETS_H
#define MOD_ASSETS_H

#include <unordered_map>
#include <array>
#include "SDL.h"
#include "SDL_image.h"
#include "../../../lib/utils/include/texture.h"
#include "../../../lib/utils/include/texture_region.h"
#include "../terrain/include/cube.h"

// TODO Don't know how to use project path
const std::string ASSETS_LOCATION = __FILE__ "/../../../../assets/sprites/";

struct TextureCubeData {
	float* uvs = nullptr;

	TextureCubeData(TextureRegion& region, int sides = 1);
	TextureCubeData() = default;
};

class AssetManager {
private:
	std::unordered_map<std::string, const Texture*> m_mappedSprites;
	std::array<TextureCubeData, 35> m_mappedCubeTextures;
	static std::string stripName(const std::string& name);
	void mapCubeTextures();
public:
	AssetManager();
	~AssetManager();
	const Texture* getSprite(std::string name) const;
	const float* getCubeUVs(CubeType type) const;
	static AssetManager& getInstance();
};


#endif //MOD_ASSETS_H
