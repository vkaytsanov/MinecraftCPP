#ifndef CONFIGURATION
#define CONFIGURATION

#include <SDL.h>

/* Class for application configuration */
class Configuration {
public:
    const char* title			= nullptr;
    int x						= SDL_WINDOWPOS_CENTERED;
    int y						= SDL_WINDOWPOS_CENTERED;
    int width					= 640;
    int height					= 480;
    SDL_WindowFlags isVisible	= SDL_WINDOW_SHOWN;

    Configuration();
    Configuration(const char* title);
    Configuration(const char* title, const int width, const int height);
    Configuration(const int width, const int height);
};

#endif