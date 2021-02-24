//
// Created by Viktor on 19.2.2021 г..
//

#ifndef PLAYER_H
#define PLAYER_H


#include "../generic/include/game_object.h"
#include "../../../../lib/utils/include/first_person_camera_controller.h"

class Player : public GameObject{
private:
	FirstPersonCameraController cameraController;
public:
	void update(float dt);

};


#endif //PLAYER_H
