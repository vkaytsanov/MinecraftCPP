#include <GL/glew.h>
#include "include/graphics.h"
#include <chrono>


Graphics::Graphics() : Graphics(new Configuration()) {}

Graphics::Graphics(Configuration* config) {
	this->config = config;
	screenSurface = nullptr;
	window = nullptr;
	renderer = nullptr;
}

void Graphics::updateTime() {
	// calculating the delta time
	uint64_t time = SDL_GetTicks();
	deltaTime = (time - lastTime) / 1000.0f;
	lastTime = time;

	// calculating fps
	if (time - frameStart >= 1000) {
		fps = frames;
		frames = 0;
		frameStart = time;
	}
	frames++;
}

int Graphics::getWidth() {
	return config->width;
}

int Graphics::getHeight() {
	return config->height;
}

float Graphics::getDeltaTime() const {
	return deltaTime;
}

float Graphics::getFps() {
	return fps;
}

void Graphics::createWindow() {
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		exit(-1);
	}
	else {
		//Create Image Handling, but just PNG format
		if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
			printf("SDL_image could not initialize! SDL_image Error: %s\n",
			       IMG_GetError());
			exit(-1);
		}
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);


		//Create window
		window = SDL_CreateWindow(config->title,
		                          config->x,
		                          config->y,
		                          config->width,
		                          config->height,
		                          config->isVisible | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
		if (window == nullptr) {
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			exit(-1);
		}
		else {
			//Create the context for OpenGL
			context = SDL_GL_CreateContext(window);

			if (!context) {
				fprintf(stderr, "Couldn't create context: %s\n", SDL_GetError());
			}
			else {
				GLenum err = glewInit();
				if (GLEW_OK != err) {
					fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
					exit(-1);
				}

				printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
				// refresh rate synchronized to the monitor
				SDL_GL_SetSwapInterval(1);

			}

			//Get window surface
			screenSurface = SDL_GetWindowSurface(window);
			if (screenSurface == nullptr) {
				printf("ScreenSurface could not be created! SDL_Error: %s\n", SDL_GetError());
				exit(-1);
			}
			else {
				//Update the surface
				SDL_UpdateWindowSurface(window);
				//Create renderer
				renderer = SDL_CreateRenderer(window, -1, 0);
				if (renderer == nullptr) {
					printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
					exit(-1);
				}
			}
		}
		if (TTF_Init() == -1) {
			printf("SDL could not initialize! SDL_Error: %s\n", TTF_GetError());
			exit(-1);
		}

	}
}

void Graphics::update() {
	SDL_UpdateWindowSurface(window);
}

Graphics::~Graphics() {
	//Destroy openGL context
	SDL_GL_DeleteContext(context);
	//Destroy surface
	SDL_FreeSurface(screenSurface);
	screenSurface = nullptr;
	//Destroy renderer
	SDL_DestroyRenderer(renderer);
	renderer = nullptr;
	//Destroy window
	SDL_DestroyWindow(window);
	window = nullptr;
	//Shutdown SDL_TTF
	TTF_Quit();
	//Shut down SDL_Image
	IMG_Quit();
	//Quit SDL subsystems
	SDL_Quit();
}

SDL_Renderer* Graphics::getRenderer() const {
	return renderer;
}

void Graphics::setWidth(const int& width) {
	config->width = width;
}

void Graphics::setHeight(const int& height) {
	config->height = height;
}

bool Graphics::isBackground() const {
	return background;
}

void Graphics::setBackground(bool background) {
	Graphics::background = background;
}

bool Graphics::isVisible() const {
	return visible;
}

void Graphics::setVisible(bool visible) {
	Graphics::visible = visible;
}

SDL_Window* Graphics::getWindow() {
	return window;
}

SDL_Surface* Graphics::getScreenSurface() const {
	return screenSurface;
}





