#ifndef AE_AUDIO_PLAYER_
#define AE_AUDIO_PLAYER_

#include <stdio.h>
#include <SDL.h>
#include <SDL_mixer.h>

class AudioPlayer {
public:
	AudioPlayer();
	~AudioPlayer();

	int loadAudioFile(char* $filename);
	int loadMusicFile(char* $filename);
	void playAudio(int $index);
	void playMusic(int $index);
	void freeAudio();

private:
	static const int _MAX_SONGS = 4;
	static const int _MAX_AUDIO = 16;

	bool _music_used[_MAX_SONGS];
	bool _audio_used[_MAX_AUDIO];

	Mix_Music* music_list[_MAX_SONGS];
	Mix_Chunk* audio_list[_MAX_AUDIO];
};

#endif