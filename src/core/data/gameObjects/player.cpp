//
// Created by Viktor on 19.2.2021 г..
//

#include "include/player.h"

void Player::update(float dt) {
	cameraController.update(dt);
	setX(cameraController.getCamera()->position->x);
	setY(cameraController.getCamera()->position->y);
	setZ(cameraController.getCamera()->position->z);
}
