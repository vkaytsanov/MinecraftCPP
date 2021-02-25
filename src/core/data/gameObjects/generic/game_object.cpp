//
// Created by Viktor on 18.12.2020 г..
//

#include "include/game_object.h"

GameObject::GameObject(const float x, const float y) {
	this->x = x;
	this->y = y;
	rect.x = x;
	rect.y = y;

}

float GameObject::getX() const {
	return x;
}

float GameObject::getY() const {
	return y;
}

float GameObject::getWidth() const {
	return width;
}

float GameObject::getHeight() const {
	return height;
}

float GameObject::getDX() const {
	return dx;
}

float GameObject::getDY() const {
	return dy;
}

const SDL_FRect& GameObject::getRect() const {
	return rect;
}

void GameObject::setWidth(const float width) {
	this->width = width;
	rect.w = width;
}

void GameObject::setHeight(const float height) {
	this->height = height;
	rect.h = height;
}

void GameObject::setX(const float x) {
	this->x = x;
}

void GameObject::setY(const float y) {
	this->y = y;
}

bool GameObject::wantsToMove() {
	return wantMove;
}

float GameObject::getSpeed() const {
	return speed;
}

void GameObject::setDX(const float dx) {
	GameObject::dx = dx;

}

void GameObject::setDY(const float dy) {
	GameObject::dy = dy;
}

void GameObject::setWantToMove(const bool wants) {
	wantMove = wants;
}

float GameObject::getModSpeed() const {
	return modSpeed;
}

void GameObject::setModSpeed(const float modSpeed) {
	GameObject::modSpeed = modSpeed;
}

float GameObject::getZ() const {
	return z;
}

void GameObject::setZ(float z) {
	GameObject::z = z;
}




