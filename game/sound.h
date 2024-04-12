#ifndef SOUND_H
#define SOUND_H
#include <SDL.h>
#include<SDL_mixer.h>
#include<iostream>
#include<string>

class Sound
{
public :
	Sound(){}
	void audio(std::string s, int n)
	{
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
			std::cout << "fail to load mix_openaudio" << Mix_GetError();
			return;
		}
		Mix_Chunk* soundeffect = Mix_LoadWAV(s.c_str());
		if (!soundeffect)
		{
			std::cout << "fail to load soundeffect\n";
		}
		Mix_PlayChannel(-1, soundeffect, n);
	};
	void quit(Mix_Chunk* soundeffect)
	{
		Mix_FreeChunk(soundeffect);
		Mix_Quit();
	}

};

#endif