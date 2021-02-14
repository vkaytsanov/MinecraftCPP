#ifndef INPUT
#define INPUT

#include "SDL.h"
#include <memory>


class Input {
private:
	SDL_Event e;
	bool quit = false;
	/* check SDL_KeyCode, max elements = 322 */
	bool keys[322];
	bool mouseMoved = false;
	bool mouseLeftClick = false;
	bool mouseRightClick = false;
	float lastMousePosX = 0;
	float lastMousePosY = 0;
	float currMousePosX = 0;
	float currMousePosY = 0;
public:
    Input(const float& width, const float& height);
    void update();
    void resetMouse();
    bool shouldQuit() const;
	bool isKeyPressed(char key);
    bool isMouseMoved() const;
    float getLastMousePosX() const;
    float getLastMousePosY() const;
    float getCurrMousePosX() const;
    float getCurrMousePosY() const;
    float getMouseMoveX() const;
    float getMouseMoveY() const;
    float getMouseDeltaX() const;
    float getMouseDeltaY() const;
    bool isMouseLeftClick() const;
    bool isMouseRightClick() const;
};

#endif