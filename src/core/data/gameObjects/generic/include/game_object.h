//
// Created by Viktor on 18.12.2020 г..
//

#ifndef DUCKHUNT_GAME_OBJECT_H
#define DUCKHUNT_GAME_OBJECT_H


#include <SDL.h>

static const float DEFAULT_MOVE_SPEED = 100.0f;

class GameObject {
private:
    SDL_FRect rect;
protected:
    float x;
    float y;
    float z;
	float dx = 0;
	float dy = 0;
    float width;
    float height;
    bool wantMove = false;
    float speed = DEFAULT_MOVE_SPEED;
    float modSpeed = 1.0f;
public:
    GameObject() = default;
    GameObject(float x, float y);
    float getX() const;
    float getY() const;
	float getZ() const;
	float getWidth() const;
    float getHeight() const;
    float getDX() const;
    float getDY() const;
    const SDL_FRect &getRect() const;
	void setDX(float dx);
	void setDY(float dy);
	void setX(float x);
    void setY(float y);
	void setZ(float z);
    void setWidth(float width);
    void setHeight(float height);
    void setWantToMove(bool wants);
    bool wantsToMove();
	float getSpeed() const;
	float getModSpeed() const;
	void setModSpeed(float modSpeed);
};


#endif //DUCKHUNT_GAME_OBJECT_H
