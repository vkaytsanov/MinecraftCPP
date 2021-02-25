//
// Created by Viktor on 18.2.2021 г..
//

#include "include/cube.h"

bool Cube::isTransparent() const {
	return type >= Water && type <= Air;
}

bool Cube::isLiquid() const {
	return type >= Water && type <= Lava;
}

bool Cube::isEntity() const {
	return type >= FlowerBlue && type <= FlowerYellow;
}
