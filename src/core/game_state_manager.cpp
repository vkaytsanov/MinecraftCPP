//
// Created by Viktor on 16.2.2021 г..
//

#include "include/game_state_manager.h"

GameStateManager::GameStateManager() {
	currentState = new GameState(Playing);
}


GameState GameStateManager::getCurrentState() const {
	return *currentState;
}


void GameStateManager::changeState(const GameState nextState) {
	*currentState = nextState;
}

const char* GameStateManager::getCurrentStateName() const {
	switch ((*currentState)) {
		case Playing:
			return "Playing";
		default:
			return nullptr;
	}
}

GameStateManager::~GameStateManager() {
	delete currentState;
}




