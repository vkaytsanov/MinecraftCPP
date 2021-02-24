//
// Created by Viktor on 16.2.2021 г..
//

#include "include/logic_system.h"
#include "../include/minecraft.h"

LogicSystem::LogicSystem(Minecraft* game) : game(game),
                                            modWorldGeneration(game) {
	modules.emplace_back(&modWorldGeneration);


}

void LogicSystem::init() {
	for (ModLogic* mod : modules) {
		mod->init();
	}
}

void LogicSystem::update() {
	if (game->gameStateManager->getCurrentState() == Playing) {
		eventHandler.update(modules);
		for (ModLogic* mod : modules) {
			mod->update();
		}
	}
}

void LogicSystem::post(Event& e) {
	eventHandler.post(&e);
}

void LogicSystem::reinit() {
	for (ModLogic* mod : modules) {
		mod->reinit();
	}
}

