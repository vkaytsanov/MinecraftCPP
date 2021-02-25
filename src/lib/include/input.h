#ifndef INPUT
#define INPUT

#include "SDL.h"
#include "../utils/include/input_processor.h"
#include <memory>
#include <queue>

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
	InputProcessor* processor = nullptr;
	void updateKeyboard();
	void updateMouse();
public:
	std::queue<SDL_Event> keyEvents;
	std::queue<SDL_Event> touchEvents;
	Input(const float width, const float height);
	void update();
	void processEvents();
	void resetMouse();
	bool shouldQuit() const;
	void setProcessor(InputProcessor* processor);
	InputProcessor* getProcessor() const;
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