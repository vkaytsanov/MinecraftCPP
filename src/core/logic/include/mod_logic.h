//
// Created by Viktor on 15.1.2021 г..
//

#ifndef MOD_LOGIC_H
#define MOD_LOGIC_H


#include "../events/include/event.h"

class Gamelib;

class ModLogic {
public:
	virtual void init();
	virtual void update();
	virtual void post(Event* e);
	virtual void reinit();
};


#endif //MOD_LOGIC_H
