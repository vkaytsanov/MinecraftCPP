//
// Created by Viktor on 18.2.2021 г..
//

#include "include/cube.h"

bool Cube::isTransparent() const {
	return (m_type >= Leaves && m_type <= Air) || isModel();
}

bool Cube::isLiquid() const {
	return m_type >= Water && m_type <= Lava;
}

bool Cube::isModel() const {
	return m_type >= FlowerBlue && m_type <= FlowerYellow;
}

bool Cube::isOpaque() const {
	return !isTransparent();
}

bool Cube::isGround() const {
	return m_type == Grass || m_type == Sand;
}

