//
// Created by Viktor on 14.2.2021 г..
//

#ifndef ATLAS_REGION_H
#define ATLAS_REGION_H


#include "texture_region.h"

class AtlasRegion : public TextureRegion{
private:
	std::string name;
	bool rotate;
	float originalWidth;
	float originalHeight;
	float offsetX;
	float offsetY;
	float packedWidth;
	float packedHeight;
public:
	AtlasRegion(Texture* texture);
};


#endif //ATLAS_REGION_H
