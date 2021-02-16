//
// Created by Viktor on 16.2.2021 г..
//

#ifndef ABSTRACT_SCREEN_H
#define ABSTRACT_SCREEN_H


class AbstractScreen {
public:
	AbstractScreen() = default;
	virtual ~AbstractScreen() = default;
	virtual void render(float dt) = 0;
	virtual void start();

};


#endif //ABSTRACT_SCREEN_H
