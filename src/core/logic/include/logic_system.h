//
// Created by Viktor on 16.2.2021 г..
//

#ifndef LOGIC_SYSTEM_H
#define LOGIC_SYSTEM_H


#include <vector>
#include "mod_world_exploration.h"
#include "mod_event_handler.h"

class Minecraft;

class LogicSystem : public ModLogic {
private:
	Minecraft* m_pGame;
	std::vector<ModLogic*> m_modules;
	ModEventHandler m_eventHandler;
	ModWorldExploration m_modWorldGeneration;
public:
	explicit LogicSystem(Minecraft* game);
	void init() override;
	void update() override;
	void post(Event& e);
	void reinit() override;
};


#endif //LOGIC_SYSTEM_H
