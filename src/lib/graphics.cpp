#include <GL/glew.h>
#include "include/graphics.h"
#include <chrono>


Graphics::Graphics() : Graphics(new Configuration()) {}

Graphics::Graphics(Configuration* config) {
	this->m_config = config;
	m_screenSurface = nullptr;
	m_window = nullptr;
	m_renderer = nullptr;
}

void Graphics::updateTime() {
	// calculating the delta time
	uint64_t time = SDL_GetTicks();
	m_deltaTime = (time - m_lastTime) / 1000.0f;
	m_lastTime = time;

	// calculating m_fps
	if (time - m_frameStart >= 1000) {
		m_fps = m_frames;
		m_frames = 0;
		m_frameStart = time;
	}
	m_frames++;
}

int Graphics::getWidth() const{
	return m_config->width;
}

int Graphics::getHeight() const {
	return m_config->height;
}

float Graphics::getDeltaTime() const {
	return m_deltaTime;
}

float Graphics::getFps() {
	return m_fps;
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


		//Create m_window
		m_window = SDL_CreateWindow(m_config->title,
		                            m_config->x,
		                            m_config->y,
		                            m_config->width,
		                            m_config->height,
		                          m_config->isVisible | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
		if (m_window == nullptr) {
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			exit(-1);
		}
		else {
			//Create the m_context for OpenGL
			m_context = SDL_GL_CreateContext(m_window);


			if (!m_context) {
				fprintf(stderr, "Couldn't create m_context: %s\n", SDL_GetError());
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

			//Get m_window surface
			m_screenSurface = SDL_GetWindowSurface(m_window);
			if (m_screenSurface == nullptr) {
				printf("ScreenSurface could not be created! SDL_Error: %s\n", SDL_GetError());
				exit(-1);
			}
			else {
				//Update the surface
				SDL_UpdateWindowSurface(m_window);
				//Create m_renderer
				m_renderer = SDL_CreateRenderer(m_window, -1, 0);
				if (m_renderer == nullptr) {
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
	SDL_UpdateWindowSurface(m_window);
}

Graphics::~Graphics() {
	//Destroy openGL m_context
	SDL_GL_DeleteContext(m_context);
	//Destroy surface
	SDL_FreeSurface(m_screenSurface);
	m_screenSurface = nullptr;
	//Destroy m_renderer
	SDL_DestroyRenderer(m_renderer);
	m_renderer = nullptr;
	//Destroy m_window
	SDL_DestroyWindow(m_window);
	m_window = nullptr;
	//Shutdown SDL_TTF
	TTF_Quit();
	//Shut down SDL_Image
	IMG_Quit();
	//Quit SDL subsystems
	SDL_Quit();
}

SDL_Renderer* Graphics::getRenderer() const {
	return m_renderer;
}

void Graphics::setWidth(const int width) const{
	m_config->width = width;
}

void Graphics::setHeight(const int height) const{
	m_config->height = height;
}

bool Graphics::isBackground() const {
	return m_background;
}

void Graphics::setBackground(const bool background) {
	this->m_background = background;
}

bool Graphics::isVisible() const {
	return m_visible;
}

void Graphics::setVisible(const bool visible) {
	this->m_visible = visible;
}

SDL_Window* Graphics::getWindow() const {
	return m_window;
}

SDL_Surface* Graphics::getScreenSurface() const {
	return m_screenSurface;
}





