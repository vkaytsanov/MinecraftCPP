#ifndef APPLICATION
#define APPLICATION

#include "listener.h"
#include "logger.h"
#include "graphics.h"
#include "input.h"
#include "audio.h"


class Application{
private:
	bool running;
	Listener* listener;
    Input* input;
	Configuration* config;
    Graphics* graphics;
    Logger* logger;
    Audio* audio;
	void gameLoop();
	void exitApp();
public:
	explicit Application(Listener* listener);
	Application(Listener* listener, Configuration* config);
	Application(Listener* listener, Configuration* config, Graphics* graphics);
	~Application();
    void log(const char* tag, const char* message) const;
    void log(const char* tag, int message) const;
    void error(const char* tag, const char* message) const;
    void error(const char* tag, int message) const;
    void debug(const char *tag, const char *message) const;
};


#endif