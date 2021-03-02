//
// Created by Viktor on 16.2.2021 г..
//

#include "include/logic_system.h"
#include "../include/minecraft.h"

LogicSystem::LogicSystem(Minecraft* game) : m_pGame(game),
                                            m_modWorldGeneration(game) {
	m_modules.emplace_back(&m_modWorldGeneration);


}

void LogicSystem::init() {
	for (ModLogic* mod : m_modules) {
		mod->init();
	}
}

void LogicSystem::update() {
	if (m_pGame->m_gameStateManager.getCurrentState() == Playing) {
		m_eventHandler.update(m_modules);
		for (ModLogic* mod : m_modules) {
			mod->update();
		}
	}
}

void LogicSystem::post(Event& e) {
	m_eventHandler.post(&e);
}

void LogicSystem::reinit() {
	for (ModLogic* mod : m_modules) {
		mod->reinit();
	}
}

