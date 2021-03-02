//
// Created by Viktor on 1.3.2021 г..
//

#include "include/biome.h"


BiomeType getBiomeType(float temperature, float humidity) {
//	return Mountains;
	if (temperature > 0) {
		if (humidity < 0) return Desert;
		if (humidity > 0.5) return Ocean;
	}
	if (humidity < 0.5) return Plains;
	return Forest;
}

