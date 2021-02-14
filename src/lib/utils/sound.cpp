//
// Created by Viktor on 18.1.2021 г..
//

#include <SDL.h>
#include "include/sound.h"

Sound::Sound(const std::string& file_path) {
	rawSound = Mix_LoadWAV(file_path.c_str());
	if (rawSound == nullptr) {
		printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	}
}

void Sound::loadSound(const std::string& file_path) {
	rawSound = Mix_LoadWAV(file_path.c_str());
	if (rawSound == nullptr) {
		printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	}
}

void Sound::play(int channel, bool loopable) {
	Mix_PlayChannel(channel, rawSound, loopable ? -1 : 0);
}

Sound::~Sound() {
	Mix_FreeChunk(rawSound);
}

void Sound::stop(int channel) {
	Mix_HaltChannel(channel);
}


