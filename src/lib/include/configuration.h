#ifndef CONFIGURATION
#define CONFIGURATION

#include "SDL.h"

/* Class for application configuration */
class Configuration {
public:
	const char* title = nullptr;
	int x = SDL_WINDOWPOS_CENTERED;
	int y = SDL_WINDOWPOS_CENTERED;
	int width = 640;
	int height = 480;
	SDL_WindowFlags isVisible = SDL_WINDOW_SHOWN;

	Configuration();
	explicit Configuration(const char* title);
	Configuration(const char* title, int width, int height);
	Configuration(int width, int height);
};

#endif