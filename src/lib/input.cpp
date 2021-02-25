#include "include/input.h"
#include <iostream>
#include <exception>
#include "include/lib.h"
#include "utils/ui/include/user_interface.h"

Input::Input(const float width, const float height) {
	std::memset(keys, false, sizeof keys);
	lastMousePosX = currMousePosX = width / 2;
	lastMousePosY = currMousePosY = height / 2;
}

void Input::updateKeyboard() {

}

void Input::updateMouse() {

}

void Input::update() {
//    mouseMoved = false;
//    mouseLeftClick = false;
//    mouseRightClick = false;

	while (SDL_PollEvent(&e) != 0) {
		//User requests quit
		if (e.type == SDL_QUIT) {
			quit = true;
		}
			//User presses a key
		else if (e.type == SDL_KEYDOWN) {
			try {
				if (e.key.keysym.sym > 322)
					throw std::exception("key is not registered");
				keys[e.key.keysym.sym] = true;
				keyEvents.push(e);
			}
			catch (std::exception& e) {
				std::cout << e.what() << std::endl;
			}
		}
			//User releases a key
		else if (e.type == SDL_KEYUP) {
			try {
				if (e.key.keysym.sym > 322)
					throw std::exception("key is not registered");
				keys[e.key.keysym.sym] = false;
				keyEvents.push(e);
			}
			catch (std::exception& e) {
				std::cout << e.what() << std::endl;
			}
		}
			//User does action with the mouse
		else if (e.type == SDL_MOUSEMOTION) {
			mouseMoved = true;
			lastMousePosX = currMousePosX;
			lastMousePosY = currMousePosY;
			currMousePosX = e.motion.x;
			currMousePosY = e.motion.y;
			touchEvents.push(e);
		}
		else if (e.type == SDL_MOUSEBUTTONDOWN) {
			if (e.button.button == SDL_BUTTON_LEFT) {
				mouseLeftClick = true;
				lastMousePosX = currMousePosX;
				lastMousePosY = currMousePosY;
				currMousePosX = e.motion.x;
				currMousePosY = e.motion.y;
			}
			else if (e.button.button == SDL_BUTTON(SDL_BUTTON_RIGHT)) {
				mouseRightClick = true;
				lastMousePosX = currMousePosX;
				lastMousePosY = currMousePosY;
				currMousePosX = e.motion.x;
				currMousePosY = e.motion.y;
			}
			//Lib::app->log("MouseEvent", "pushed");
			touchEvents.push(e);
		}
		else if (e.type == SDL_MOUSEBUTTONUP) {
			if (e.button.button == SDL_BUTTON_LEFT) {
				mouseLeftClick = false;
				lastMousePosX = currMousePosX;
				lastMousePosY = currMousePosY;
				currMousePosX = e.motion.x;
				currMousePosY = e.motion.y;
			}
			else if (e.button.button == SDL_BUTTON(SDL_BUTTON_RIGHT)) {
				mouseRightClick = false;
				lastMousePosX = currMousePosX;
				lastMousePosY = currMousePosY;
				currMousePosX = e.motion.x;
				currMousePosY = e.motion.y;
			}
			touchEvents.push(e);
		}
		else if (e.type == SDL_WINDOWEVENT) {
			switch (e.window.event) {
				case SDL_WINDOWEVENT_SHOWN:
					Lib::graphics->setBackground(false);
					break;
				case SDL_WINDOWEVENT_HIDDEN:
					Lib::graphics->setBackground(true);
					break;
				case SDL_WINDOWEVENT_RESIZED:
					Lib::graphics->setWidth(e.window.data1);
					Lib::graphics->setHeight(e.window.data2);
					break;
				case SDL_WINDOWEVENT_MINIMIZED:
					Lib::graphics->setVisible(false);
					break;
				case SDL_WINDOWEVENT_RESTORED:
					Lib::graphics->setVisible(true);
					break;
			}
		}
	}
}

void Input::processEvents() {
	if (!processor) {
		// Get rid of the events that happened, else we will get bombarded
		// with events after a InputProcessor gets used
		while (!keyEvents.empty()) {
			keyEvents.pop();
		}
		while (!touchEvents.empty()) {
			touchEvents.pop();
		}
		return;
	}
	while (!keyEvents.empty()) {
		SDL_Event event = keyEvents.front();
		keyEvents.pop();
		switch (event.type) {
			case SDL_KEYDOWN:
				processor->keyDown(event, event.key.keysym.sym);
				break;
			case SDL_KEYUP:
				processor->keyUp(event, event.key.keysym.sym);
				break;

		}
	}
	while (!touchEvents.empty()) {
		SDL_Event event = touchEvents.front();
		touchEvents.pop();
		//Lib::app->log("MouseEvent", "popped");
		switch (event.type) {
			case SDL_MOUSEBUTTONDOWN:
				processor->touchDown(event, event.motion.x, event.motion.y);
				break;
			case SDL_MOUSEBUTTONUP:
				processor->touchUp(event, event.motion.x, event.motion.y);
				break;
			case SDL_MOUSEMOTION:
				break;
			default:
				Lib::app->debug("Input", "MouseEvent not registered.");
		}
	}
}


bool Input::shouldQuit() const {
	return quit;
}

bool Input::isKeyPressed(const char key) {
	return keys[key];
}

bool Input::isMouseMoved() const {
	return mouseMoved;
}

float Input::getLastMousePosX() const {
	return lastMousePosX;
}

float Input::getLastMousePosY() const {
	return lastMousePosY;
}

float Input::getCurrMousePosX() const {
	return currMousePosX;
}

float Input::getCurrMousePosY() const {
	return currMousePosY;
}


float Input::getMouseMoveX() const {
	return currMousePosX - lastMousePosX;
}

float Input::getMouseMoveY() const {
	return lastMousePosY - currMousePosY;
}

bool Input::isMouseLeftClick() const {
	return mouseLeftClick;
}

bool Input::isMouseRightClick() const {
	return mouseRightClick;
}

void Input::resetMouse() {
	SDL_WarpMouseInWindow(Lib::graphics->getWindow(), Lib::graphics->getWidth() / 2, Lib::graphics->getHeight() / 2);

}

float Input::getMouseDeltaX() const {
	return 0.5f * (currMousePosX - (float) Lib::graphics->getWidth() / 2);
}

float Input::getMouseDeltaY() const {
	return -0.5f * (currMousePosY - (float) Lib::graphics->getHeight() / 2);
}

void Input::setProcessor(InputProcessor* processor) {
	this->processor = processor;
}

InputProcessor* Input::getProcessor() const {
	return processor;
}



