//
// Created by Viktor on 17.1.2021 г..
//

#ifndef MOD_EVENT_HANDLER_H
#define MOD_EVENT_HANDLER_H


#include <queue>
#include <vector>
#include "mod_logic.h"

class ModEventHandler : public ModLogic {
private:
	std::queue<Event*> events;
	void sendToModules(std::vector<ModLogic*>& modules, Event* e);
public:
	void update(std::vector<ModLogic*>& modules);
	void post(Event* e) override;
	void reinit() override;
};


#endif //MOD_EVENT_HANDLER_H
