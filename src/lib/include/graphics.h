#ifndef GRAPHICS
#define GRAPHICS

#include "GL/glew.h"
#include "configuration.h"


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
    [[nodiscard]] bool  isBackground() const;
    [[nodiscard]] bool  isVisible() const;
    void  setBackground(bool background);
    void  setVisible(bool visible);
    void  updateTime();
	void  setWidth(const int& width);
	void  setHeight(const int& height);
	int	  getWidth();
	int   getHeight();
    [[nodiscard]] SDL_Window* getWindow();
    [[nodiscard]] SDL_Renderer *getRenderer() const;
	[[nodiscard]] float getDeltaTime() const;
	float getFps();
	void  createWindow();
	void  update();
    bool  rotateDevCamera = false;


};

#endif