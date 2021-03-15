#ifndef GRAPHICS
#define GRAPHICS

#include "configuration.h"
#include "SDL.h"
#include "SDL_image.h"
#include <SDL_ttf.h>


class Graphics {
	friend class Application;
private:
	Configuration* m_config;
	SDL_Window* m_window;
	SDL_GLContext m_context;
	SDL_Surface* m_screenSurface;
	SDL_Renderer* m_renderer;
	float m_lastTime = 0;
	float m_deltaTime = 0;
	uint16_t m_fps = 0;
	uint16_t m_frames = 0;
	uint64_t m_frameStart = 0;
	bool m_background;
	bool m_visible;
public:
	explicit Graphics(Configuration* config);
	Graphics();
	~Graphics();
	bool isBackground() const;
	void setBackground(const bool background);
	bool isVisible() const;
	void setVisible(const bool visible);
	void updateTime();
	void setWidth(const int width) const;
	void setHeight(const int height) const;
	int getWidth() const;
	int getHeight() const;
	float getDeltaTime() const;
	float getFps();
	void createWindow();
	void update();

	SDL_Renderer* getRenderer() const;

	SDL_Window* getWindow() const;

	SDL_Surface* getScreenSurface() const;
};

#endif