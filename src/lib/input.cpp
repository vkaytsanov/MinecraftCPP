#include "include/input.h"
#include <iostream>
#include <exception>
#include "include/lib.h"

Input::Input(const float& width, const float& height) {
    std::memset(keys, false, sizeof keys);
    lastMousePosX = currMousePosX = width / 2;
    lastMousePosY = currMousePosY = height / 2;
}

void Input::update() {
    mouseMoved = false;
    mouseLeftClick = false;
    mouseRightClick = false;
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
            }
            catch (std::exception& e) {
                std::cout << e.what() << std::endl;
            }
        }
        //User releases a key
        else if(e.type == SDL_KEYUP){
            try {
                if (e.key.keysym.sym > 322)
                    throw std::exception("key is not registered");
                keys[e.key.keysym.sym] = false;
            }
            catch (std::exception& e) {
                std::cout << e.what() << std::endl;
            }
        }
        //User does action with the mouse
        else if(e.type == SDL_MOUSEMOTION){
            mouseMoved = true;
            lastMousePosX = currMousePosX;
            lastMousePosY = currMousePosY;
            currMousePosX = e.motion.x;
            currMousePosY = e.motion.y;
            if(e.button.button == SDL_BUTTON_LEFT){
                mouseLeftClick = true;
            }
            if(e.button.button == SDL_BUTTON(SDL_BUTTON_RIGHT)){
                mouseRightClick = true;
            }
        }
        else if(e.type == SDL_WINDOWEVENT){
            switch(e.window.event){
                case SDL_WINDOWEVENT_SHOWN:
                    Lib::graphics->setBackground(false);
                    SDL_Log("Window %d shown", e.window.windowID);
                    break;
                case SDL_WINDOWEVENT_HIDDEN:
                    Lib::graphics->setBackground(true);
                    SDL_Log("Window %d hidden", e.window.windowID);
                    break;
                case SDL_WINDOWEVENT_RESIZED:
                    Lib::graphics->setWidth(e.window.data1);
                    Lib::graphics->setHeight(e.window.data2);
                    SDL_Log("Window %d resized to %dx%d",
                            e.window.windowID, e.window.data1,
                            e.window.data2);
                    break;
                case SDL_WINDOWEVENT_MINIMIZED:
                    Lib::graphics->setVisible(false);
                    SDL_Log("Window %d minimized", e.window.windowID);
                    break;
                case SDL_WINDOWEVENT_RESTORED:
                    Lib::graphics->setVisible(true);
                    SDL_Log("Window %d restored", e.window.windowID);
                    break;
            }
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
    SDL_WarpMouseInWindow(Lib::graphics->getWindow(), Lib::graphics->getWidth()/2, Lib::graphics->getHeight()/2);

}


float Input::getMouseDeltaX() const {
    return  0.5f * (currMousePosX - (float) Lib::graphics->getWidth()/2);
}

float Input::getMouseDeltaY() const {
    return -0.5f * (currMousePosY - (float) Lib::graphics->getHeight()/2);
}

