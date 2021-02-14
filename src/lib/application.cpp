//
// Created by Viktor on 17.12.2020 г..
//

#include "include/application.h"
#include "include/lib.h"
#include <string>

#include <typeinfo>



Application::Application(Listener* listener) :
	Application(listener, new Configuration()){}

Application::Application(Listener* listener, Configuration* config) :
	Application(listener, config, new Graphics(config)){}

/* Initializing here the application */
Application::Application(Listener* listener, Configuration* config, Graphics* graphics) {

	// Our game
	this->listener = listener;
	// Our configuration file for the game
	this->config = config;
	// Our library for graphics
	this->graphics = graphics;
	// Logging, debugging and errors utility
	this->logger = new Logger();
	// Receive user input
	this->input = new Input(config->width, config->height);
	// if we dont have declared title, we will use the name of the class
	if (config->title == nullptr) config->title = typeid(listener).name();
	// creating the window
	graphics->createWindow();
	// creating the environment lib
	Lib::app = this;
	Lib::graphics = graphics;
	Lib::input = input;
    // creating the objects from the game
	listener->create();

	running = true;

	gameLoop();
}

void Application::gameLoop() {
    int lastWidth = graphics->getWidth();
    int lastHeight = graphics->getHeight();
    bool wasPaused = false;
	while (running) {
	    // fetching all the user input
		input->update();
		// user has clicked the top right "X" quit button
		if (input->shouldQuit()) break;
        bool isMinimized = !graphics->isVisible();
        bool isBackground = graphics->isBackground();
        bool isPaused = isMinimized || isBackground;
        if(!wasPaused && isPaused){
            // the game window just became not active on the user's end
            wasPaused = true;
            listener->pause();
        }
        if(wasPaused && !isPaused){
            // the game window just became active on the user's end
            wasPaused = false;
            listener->resume();
        }

        const int width = graphics->getWidth();
        const int height = graphics->getHeight();
        if(lastWidth != width || lastHeight != height){
            // we should have received any changes in the input->update()
            lastWidth = width;
            lastHeight = height;
            // sending to the listener that the user has resized
            // it should update the viewport if there is one
            listener->resize(width, height);
        }

        if(!isPaused) {
            graphics->updateTime();
            listener->render();
            SDL_GL_SwapWindow(graphics->getWindow());

            /* So we don't use 100% CPU */
            SDL_Delay(1);
        }
        else{
            SDL_Delay(1000);
        }
        int error;
        while((error = glGetError()) != GL_NO_ERROR){
            this->error("OpenGL Error", error);
        }
	}
}

void Application::exitApp() {
	running = false;
}

Application::~Application() {
    delete logger;
    delete listener;
    delete graphics;
    delete config;
}

void Application::log(const char *tag, const char *message) const {
    logger->log(tag, message);
}

void Application::log(const char *tag, int message) const {
    logger->log(tag, std::to_string(message).c_str());
}

void Application::error(const char *tag, const char *message) const {
    logger->error(tag, message);
}

void Application::error(const char *tag, int message) const {
    logger->error(tag, std::to_string(message).c_str());
}



