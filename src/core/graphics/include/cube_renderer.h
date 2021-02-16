//
// Created by Viktor on 16.2.2021 г..
//

#ifndef CUBE_RENDERER_H
#define CUBE_RENDERER_H

class Minecraft;

class CubeRenderer {
private:
	Minecraft* game;
public:
	CubeRenderer(Minecraft* game);
	void render();
};


#endif //CUBE_RENDERER_H
