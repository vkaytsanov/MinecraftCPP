//
// Created by Viktor on 16.2.2021 г..
//

#ifndef GRAPHICS_SYSTEM_H
#define GRAPHICS_SYSTEM_H


#include "../screens/include/abstract_screen.h"
#include "../../../lib/utils/include/universal_viewport.h"


extern int GRAPHICS_WIDTH;
extern int GRAPHICS_HEIGHT;
extern float WORLD_WIDTH;
extern float WORLD_HEIGHT;

#define RENDER_DISTANCE 3 // 6

class Minecraft;

class GraphicsSystem {
private:
	Minecraft* game;
	UniversalViewport* viewport;
	AbstractScreen* screens[1];
public:
	explicit GraphicsSystem(Minecraft* game);
	~GraphicsSystem();
	void create();
	void render(const float dt);
	void resizeViewport(const int width, const int height);
	void start(int state);
	UniversalViewport* getViewport() const;
};


#endif //GRAPHICS_SYSTEM_H
