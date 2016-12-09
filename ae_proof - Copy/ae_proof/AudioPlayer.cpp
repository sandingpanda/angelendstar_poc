#include "AudioPlayer.h"

AudioPlayer::AudioPlayer()
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
		printf("AudioPlayer()-> ERROR INITIALIZING MIX_OPENAUDIO\n");
	}

	for (int $i = 0; $i < _MAX_SONGS; $i++) {
		_music_used[$i] = false;
	}

	for (int $j = 0; $j < _MAX_AUDIO; $j++) {
		_audio_used[$j] = false;
	}

	Mix_Volume(-1, 32);
	Mix_VolumeMusic(16);
}

AudioPlayer::~AudioPlayer() 
{
	freeAudio();
}

//MUSIC
int AudioPlayer::loadMusicFile(char* $filename)
{
	int $i;

	for ($i = 0; $i < _MAX_SONGS; $i++) {
		if (_music_used[$i] == false) {
			_music_used[$i] = true;
			break;
		}

		if ($i == _MAX_SONGS - 1) {
			printf("AudioPlayer.loadMusicFile-> ERROR: NO SONG SLOTS LEFT");
		}
	}

	music_list[$i] = Mix_LoadMUS($filename);

	return $i;
}

//AUDIO SAMPLES
int AudioPlayer::loadAudioFile(char* $filename)
{
	int $i;

	for ($i = 0; $i < _MAX_AUDIO; $i++) {
		if (_audio_used[$i] == false) {
			_audio_used[$i] = true;
			break;
		}

		if ($i == _MAX_AUDIO - 1) {
			printf("AudioPlayer.loadAudioFile-> ERROR: NO AUDIO SLOTS LEFT");
		}
	}

	audio_list[$i] = Mix_LoadWAV($filename);

	return $i;
}

//PLAY MUSIC
void AudioPlayer::playMusic(int $index)
{
	Mix_PlayMusic(music_list[$index], -1);
}

void AudioPlayer::playAudio(int $index)
{
	int $channel = (Mix_PlayChannel(-1, audio_list[$index], 0));
}


void AudioPlayer::freeAudio()
{
	for (int $i = 0; $i < _MAX_SONGS; $i++) {
		if (music_list[$i] != NULL)
		{
			Mix_FreeMusic(music_list[$i]);
		}
	}

	for (int $j = 0; $j < _MAX_AUDIO; $j++) {
		if (audio_list[$j] != NULL)
		{
			Mix_FreeChunk(audio_list[$j]);
		}
	}
}