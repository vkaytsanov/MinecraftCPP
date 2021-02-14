//
// Created by Viktor on 18.1.2021 г..
//

#ifndef MUSIC_H
#define MUSIC_H


#include <SDL_mixer.h>
#include <string>

class Music {
private:
	Mix_Music* rawMusic;
public:
	Music(const std::string& file_path);
	~Music();
	void loadMusic(const std::string& file_path);
	void play(bool loopable);
	bool isPlaying();
};


#endif //MUSIC_H
