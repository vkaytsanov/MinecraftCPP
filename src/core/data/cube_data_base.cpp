//
// Created by Viktor on 17.2.2021 г..
//

#include "include/cube_data_base.h"

namespace CubeDatabase {

	CubeDatabase::TextureData::TextureData(TextureRegion region, int sides) {
		this->region = region;
		uvs = region.getUVs();
		if (sides == 3) {
			for (int i = 0; i < 6 * 4 * 2; i++) {
				uvs[i] *= uvs3side[i];
			}
		}
	}

	std::vector<TextureData> mappedTextures(Air);

	void init(Texture* texture){
		const int SPRITE_SIZE = 32;

		TextureRegion spriteSheet(texture);
		TextureRegion** regions = spriteSheet.split(SPRITE_SIZE, SPRITE_SIZE);

		mappedTextures[Grass] = TextureData(regions[1][0] + regions[2][0] + regions[3][0], 3);
		mappedTextures[Dirt] = TextureData(regions[3][0]);

		const int regionsSize = spriteSheet.getTexture()->getWidth() / SPRITE_SIZE;
		for(int i = 0; i < regionsSize; i++){
			delete[] regions[i];
		}
		delete[] regions;
	}

	float* getUVs(CubeType type) {
		return mappedTextures[type].uvs;
	}

	void freeMemory() {
		for(auto& textureData : mappedTextures){
			delete[] textureData.uvs;
		}
	}
}