//
// Created by Viktor on 16.2.2021 г..
//

#ifndef PLAYING_SCREEN_H
#define PLAYING_SCREEN_H


#include "abstract_screen.h"
#include "../../../../lib/utils/include/first_person_camera_controller.h"
#include "../../include/world_renderer.h"

class Minecraft;

class PlayingScreen : public AbstractScreen{
private:
	Minecraft* game;
	FirstPersonCameraController* cameraController;
	WorldRenderer* worldRenderer;
	bool isWireframe = false;
public:
	explicit PlayingScreen(Minecraft* game);
	void render(float dt) override;
	~PlayingScreen() override;
	void start() override;
};


#endif //PLAYING_SCREEN_H
