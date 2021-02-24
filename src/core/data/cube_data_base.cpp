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

	std::vector<TextureData> mappedTextures(Air + 1);

	void init(Texture* texture){
		const int SPRITE_SIZE = 32;

		TextureRegion spriteSheet(texture);
		TextureRegion** regions = spriteSheet.split(SPRITE_SIZE, SPRITE_SIZE);

		mappedTextures[Gravel] = TextureData(regions[0][0]);
		mappedTextures[Grass] = TextureData(regions[1][0] + regions[2][0] + regions[3][0], 3);
		mappedTextures[Dirt] = TextureData(regions[3][0]);
		mappedTextures[WoodPlank] = TextureData(regions[4][0]);
		mappedTextures[StoneProcessed] = TextureData(regions[5][0] + regions[6][0]);
		mappedTextures[Brick] = TextureData(regions[7][0]);
		mappedTextures[TNT] = TextureData(regions[8][0] + regions[9][0] + regions[10][0], 3);
		mappedTextures[Web] = TextureData(regions[11][0]);
		mappedTextures[FlowerBlue] = TextureData(regions[12][0]);
		mappedTextures[FlowerYellow] = TextureData(regions[13][0]);
		mappedTextures[Treelet] = TextureData(regions[15][0]);
		mappedTextures[BrokenStone] = TextureData(regions[1][1]);
		mappedTextures[Bedrock] = TextureData(regions[2][1]);
		mappedTextures[Sand] = TextureData(regions[3][1]);
		mappedTextures[NetherGravel] = TextureData(regions[4][1]);
		mappedTextures[Wood] = TextureData(regions[5][1] + regions[6][1]);
		mappedTextures[IronProcessed] = TextureData(regions[7][1]);
		mappedTextures[GoldProcessed] = TextureData(regions[8][1]);
		mappedTextures[DiamondProcessed] = TextureData(regions[9][1]);
		mappedTextures[ChestSingle] = TextureData(regions[10][1] + regions[11][1] + regions[12][1], 3);
		mappedTextures[Gold] = TextureData(regions[0][2]);
		mappedTextures[Iron] = TextureData(regions[1][2]);
		mappedTextures[Coal] = TextureData(regions[2][2]);
		mappedTextures[Glass] = TextureData(regions[1][3]);
		mappedTextures[Diamond] = TextureData(regions[2][3]);
		mappedTextures[Stone] = TextureData(regions[12][13]);
		mappedTextures[Air] = TextureData();

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