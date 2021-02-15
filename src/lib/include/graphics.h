#ifndef GRAPHICS
#define GRAPHICS

#include "configuration.h"
#include "SDL.h"
#include "SDL_image.h"
#include <SDL_ttf.h>


class Graphics {
private:
	Configuration* config;
	SDL_Window* window;
	SDL_GLContext context;
	SDL_Surface* screenSurface;
    SDL_Renderer* renderer;
	float lastTime = 0;
	float deltaTime = 0;
	uint16_t fps = 0;
	uint16_t frames = 0;
	uint64_t frameStart = 0;
    bool background;
    bool visible;
public:
	explicit Graphics(Configuration* config);
	Graphics();
	~Graphics();
    bool  isBackground() const;
    void  setBackground(bool background);
    bool  isVisible() const;
    void  setVisible(bool visible);
    void  updateTime();
	void  setWidth(const int& width);
	void  setHeight(const int& height);
	int	  getWidth();
	int   getHeight();
	float getDeltaTime() const;
	float getFps();
	void  createWindow();
	void  update();

    SDL_Renderer *getRenderer() const;

    SDL_Window *getWindow();

    SDL_Surface *getScreenSurface() const;
};

#endif