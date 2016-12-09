#include "SFXLibrary.h"

const char* SFXLibrary::PATH_SHOOT_ONE = "./audio/phasers3.wav";
const char* SFXLibrary::PATH_SHOOT_TWO = "";
const char* SFXLibrary::PATH_BLADE = "./audio/electriccurrent.wav";
const char* SFXLibrary::PATH_BLAST = "./audio/beam.wav";
const char* SFXLibrary::PATH_EXPLOSION = "./audio/explosion.wav";

int SFXLibrary::_index_list[5] = { 0, 0, 0, 0, 0 };

AudioPlayer* SFXLibrary::AUDIO_PLAYER = NULL;

SFXLibrary::SFXLibrary() {}

SFXLibrary::~SFXLibrary() {}

void SFXLibrary::loadSamples()
{
	if (SFXLibrary::AUDIO_PLAYER == NULL) {
		printf("SFXLibrary::loadSamples-> ERROR: UNDEFINED AUDIOPLAYER OBJECT");
	}

	SFXLibrary::_index_list[0] = SFXLibrary::AUDIO_PLAYER->loadAudioFile((char*)SFXLibrary::PATH_SHOOT_ONE);
	//SFXLibrary::_index_list[1] =  SFXLibrary::AUDIO_PLAYER->loadAudioFile((char*)SFXLibrary::PATH_SHOOT_TWO);
	SFXLibrary::_index_list[2] = SFXLibrary::AUDIO_PLAYER->loadAudioFile((char*)SFXLibrary::PATH_BLADE);
	SFXLibrary::_index_list[3] = SFXLibrary::AUDIO_PLAYER->loadAudioFile((char*)SFXLibrary::PATH_BLAST);
	SFXLibrary::_index_list[4] = SFXLibrary::AUDIO_PLAYER->loadAudioFile((char*)SFXLibrary::PATH_EXPLOSION);
}

void SFXLibrary::playSFX(SFXSample $sample)
{
	int $index = 0;

	switch ($sample) {
		case SFXSample::SHOOT_ONE:
			$index = 0;
			break;
		case SFXSample::SHOOT_TWO:
			//index = 1;
			break;
		case SFXSample::BLADE:
			$index = 2;
			break;
		case SFXSample::BLAST:
			$index = 3;
			break;
		case SFXSample::EXPLOSION:
			$index = 4;
			break;
	}
	
	SFXLibrary::AUDIO_PLAYER->playAudio(SFXLibrary::_index_list[$index]);
}