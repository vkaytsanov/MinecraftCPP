//
// Created by Viktor on 18.1.2021 г..
//

#ifndef SOUND_H
#define SOUND_H


#include <SDL_mixer.h>
#include <string>

class Sound {
private:
	Mix_Chunk* rawSound;
public:
	Sound(const std::string& file_path);
	~Sound();
	void loadSound(const std::string& file_path);
	void play(int channel = -1, bool loopable = false);
	void stop(int channel = -1);

};


#endif //SOUND_H
